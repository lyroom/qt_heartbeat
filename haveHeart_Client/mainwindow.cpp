#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Client *client=new Client(this);
    client->Toconnect("127.0.0.1",66666);
}

MainWindow::~MainWindow()
{
    delete ui;
}
