#ifndef FIELD_MODEL_H
#define FIELD_MODEL_H

#include "qabstractitemmodel.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>

struct GameField : public QAbstractTableModel {
        Q_OBJECT
public:
        GameField(QObject *parent, size_t width, size_t height) : QAbstractTableModel(parent), width(width), height(height), isPlaying(1), field(std::vector<int>(width*height, 0)) {}
    GameField() : GameField(nullptr, 3, 3) {};
    size_t set(size_t r, size_t c, size_t val) {
        assert((val == 1) || (val == 0) );
        field.at(r*this->width + c) = val;
        return 0;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return height;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return width;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if ((index.row() >= height) || (index.column() >= width) || (role != Qt::DisplayRole) ) {
            return QVariant();
        } else {
            return field.at(index.row()*width + index.column());
        }
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
public slots:
    void switch_cell(const QModelIndex &idx) {
        beginResetModel();
        if (isPlaying) {
            _switch_cells(idx.row(), idx.column());
        } else {
            _switch_cell(idx.row(), idx.column());
        }
        endResetModel();
    }
private:
    void _switch_cell(size_t r, size_t c) {
        field.at(r*width + c) ^= 1;
    }

    void _switch_cells(size_t r, size_t c) {
        _switch_cell(r, c);
        if (r > 0) {
            _switch_cell(r-1, c);
        }
        if (r < height -1) {
            _switch_cell(r+1, c);
        }
        if (c > 0) {
            _switch_cell(r, c-1);
        }
        if (c < height -1) {
            _switch_cell(r, c+1);
        }
    }

    size_t width, height;
    std::vector<int> field;
    bool isPlaying;
};

#endif // FIELD_MODEL_H
