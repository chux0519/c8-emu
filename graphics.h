#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QOpenGLWidget>


class Painter;

class Graphics: public QOpenGLWidget
{
    Q_OBJECT
public:
    Graphics(Painter *painter, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Painter *painter;
    int elapsed;
};

// Painter class

class Painter
{
public:
    Painter();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush rectangleBrush;
    QFont textFont;
    QPen textPen;
};

#endif // GRAPHICS_H