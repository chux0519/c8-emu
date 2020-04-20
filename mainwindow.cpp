#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include <QFileDialog>
#include <QTimer>
#include <QDebug>

#define FREQUENCY 500

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stepBtn->setEnabled(false);

    // setup graphics
    gameStage = new Graphics(&painter, c8.pixels.data(), ui->gWidget);

    // chip8 cpu timer: $FREQUENCY herz
    QTimer *processTimer = new QTimer(this);
    connect(processTimer, &QTimer::timeout, this, &MainWindow::process);
    processTimer->start(1000 / FREQUENCY);

    // setup mem viewer
    memViewer = new MemoryViewer(ui->memView, c8.memory.data());

    // game state
    start = false;

    // graphics timer, 50fps
    elapsed = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::ui_update);
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose ROM", "");
    if(!filename.isEmpty()) {
        // load it into chip8 memory
        if (c8.load_rom(filename.toLatin1().data())) {
            memViewer->reload(c8.memory.data());
        }
    }
}

void MainWindow::process() {
    if (start) {
        c8.step();
    }
}

void MainWindow::ui_update() {
    gameStage->animate();
    int interval = qobject_cast<QTimer*>(sender())->interval();
    elapsed += interval;
    if(elapsed > 50) {
        elapsed -= 50;
        // 20fps
        memViewer->display(c8.PC());
    }
}

void MainWindow::on_startBtn_clicked()
{
    start = !start;
    if (start) {
        this->ui->stepBtn->setEnabled(false);
    } else {
        this->ui->stepBtn->setEnabled(true);
        memViewer->display(c8.PC());
    }
}

void MainWindow::on_stepBtn_clicked()
{
    c8.step();
    memViewer->display(c8.PC());
}
