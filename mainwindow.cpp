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
    // don't know why I couldn't mek it work with buttonToggled
    // hey, I constulted with newer docs!
    // for 5.15 it contained the folling code to help compiler choose overload
    //    connect(buttonGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
    //    [=](QAbstractButton *button, bool checked){ /* ... */ });
    // replace with "nicer" version
    QObject::connect(ui->rbs_mode, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled), &f, [&](QAbstractButton *btn, bool state){
        if (btn == ui->rb_game) {
            f.set_mode(state);
        }
    });
    ui->rb_game->setChecked(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

