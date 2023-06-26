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
//    QObject::connect();
    for (const auto &b : ui->rbs_mode->buttons()) {
        std::cout <<  (b->objectName()).toStdString() << std::endl;
        std::cout << ui->rbs_mode->id(b) << std::endl;
    }
    ui->rb_game->setChecked(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

