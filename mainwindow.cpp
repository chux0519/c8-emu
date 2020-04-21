#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kbdsettingdialog.h"
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
    this->ui->stepBtn->setEnabled(!start);

    // graphics timer, 50fps
    elapsed = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::ui_update);
    timer->start(20);

    // key mapping
    keymapping = {
        Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4,
        Qt::Key_Q, Qt::Key_W, Qt::Key_E, Qt::Key_R,
        Qt::Key_A, Qt::Key_S, Qt::Key_D, Qt::Key_F,
        Qt::Key_Z, Qt::Key_X, Qt::Key_C, Qt::Key_V,
    };
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
        ui_refresh();
    }
}

void MainWindow::ui_refresh() {
    // memory viewer
    memViewer->display(c8.PC());
    // pc and op code viewer
    QString pcLabel = "PC: 0x";
    pcLabel += QString::number(this->c8.PC(), 16).toUpper();
    QString opLabel = "OP: 0x";
    opLabel += QString::number(this->c8.OP(), 16).toUpper();
    opLabel += "(" + QString::fromStdString(this->c8.get_asm(this->c8.OP())).toUpper() + ")";
    this->ui->pcLabel->setText(pcLabel);
    this->ui->opLabel->setText(opLabel);
}

void MainWindow::on_startBtn_clicked()
{
    start = !start;
    if (start) {
        this->ui->stepBtn->setEnabled(false);
        this->ui->startBtn->setText("Pause");
    } else {
        this->ui->stepBtn->setEnabled(true);
        this->ui->startBtn->setText("Resume");
        ui_refresh();
    }
}

void MainWindow::on_stepBtn_clicked()
{
    memViewer->display(c8.PC());
    c8.step();
}

void MainWindow::on_kbdSetting_triggered()
{
    qDebug() << "should open keyboard settings";
    KbdSettingDialog kbdSettingDialog;
    kbdSettingDialog.setModal(true);
    kbdSettingDialog.exec();
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        for(int i = 0; i < keymapping.size(); i++) {
            Qt::Key k = keymapping[i];
            if (keyEvent->key() == k) {
                // qDebug() << "key " << (event->type() == QEvent::KeyPress ? "down " : "up") << keyEvent->key() << "from" << obj;
                c8.keyboard[i] = event->type() == QEvent::KeyPress ? 1 : 0;
                return true;
            }
        }
    }
    return false;
}
