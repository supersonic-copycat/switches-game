#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , f(GameField())
{
    ui->setupUi(this);
    // my code goes here
    ui->tableView->setShowGrid(0);
    ui->tableView->setModel(static_cast<QAbstractTableModel*>(&f));
}

MainWindow::~MainWindow()
{
    delete ui;
}

