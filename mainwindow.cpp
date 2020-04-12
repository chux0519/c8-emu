#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include <QFileDialog>
#include <QTimer>

#define FREQUENCY 500

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Graphics *gameStage = new Graphics(&painter, c8.pixels.data(), ui->gWidget);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, gameStage, &Graphics::animate);
    timer->start(20);

    QTimer *processTimer = new QTimer(this);
    connect(processTimer, &QTimer::timeout, this, &MainWindow::process);
    processTimer->start(1000 / FREQUENCY);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose ROM", "");
    if(!filename.isEmpty()) {
        // open this file
        // check this file size
        // load it into chip8 memory
        c8.load_rom(filename.toLatin1().data());
    }
}

void MainWindow::process() {
    c8.step();
}
