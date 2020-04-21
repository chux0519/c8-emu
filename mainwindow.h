#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics.h"
#include "chip8.h"
#include "memoryviewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenFile_triggered();
    void process();
    void ui_update();
    void ui_refresh();

    void on_startBtn_clicked();

    void on_stepBtn_clicked();

    void on_kbdSetting_triggered();

private:
    Ui::MainWindow *ui;
    Painter painter;
    Chip8 c8;
    bool start;
    MemoryViewer *memViewer;
    Graphics *gameStage;
    int elapsed;
};

#endif // MAINWINDOW_H
