#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Graphics *gameStage = new Graphics(&painter, this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, gameStage, &Graphics::animate);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Menu Example",
                                                      "/Users/chux0519");
}
