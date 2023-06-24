#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

