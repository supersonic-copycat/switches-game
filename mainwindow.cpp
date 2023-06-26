#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , f(GameField())
{
    ui->setupUi(this);
    // my code goes here
    ui->tableView->setShowGrid(1);
    ui->tableView->setModel(static_cast<QAbstractTableModel*>(&f));
    QObject::connect(ui->tableView, &QTableView::clicked, &f, &GameField::switch_cell);
//    for (const auto &b : ui->rbs_mode->buttons()) {
//        std::cout << b->objectName().toStdString() << " (" << (void*) b << ", " << (void*) ui->rb_game << ")" << std::endl;
//    }
    QObject::connect(ui->rbs_mode, &QButtonGroup::idToggled, &f, [&](int id, bool state){
        if (ui->rbs_mode->button(id) == ui->rb_game) {
            f.set_mode(state);
        }
    });
    ui->rb_game->setChecked(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

