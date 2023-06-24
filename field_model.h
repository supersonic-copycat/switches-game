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
    GameField(QObject *parent, size_t width, size_t height) : QAbstractTableModel(parent), width(width), height(height), field(std::vector<int>(width*height, 0)) {}
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
        if ((index.row() >= height) || (index.column() >= width) ) {
            return QVariant();
        } else {
            return field.at(index.row()*width + index.column());
        }
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

private:
    size_t switch_cell(size_t r, size_t c) {
        return field.at(r*width + c) ^ 1;
    }

    void switch_cells(size_t r, size_t c) {
        for (size_t i = std::clamp<size_t>(r - 1, 0, height); i <= std::clamp<size_t>(r+1, 0, height); ++i) {
            for (size_t j = std::clamp<size_t>(c - 1, 0, width); j <= std::clamp<size_t>(c+1, 0, width); ++j) {
                switch_cell(i, j);
            }
        }
    }

    size_t width, height;
    std::vector<int> field;
};

#endif // FIELD_MODEL_H
