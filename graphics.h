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
    Graphics(Painter *painter, uint8_t *pixels, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Painter *painter;
    uint8_t *pixels;
};

// Painter class

class Painter
{
public:
    Painter();

public:
    void paint(QPainter *painter, QPaintEvent *event, uint8_t* pixels);

private:
    QBrush background;
    QBrush rectangleBrush;
    QFont textFont;
    QPen textPen;
};

#endif // GRAPHICS_H
