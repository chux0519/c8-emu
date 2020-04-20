#include "graphics.h"
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>

Graphics::Graphics(Painter *painter, uint8_t *pixels, QWidget *parent) :
    QOpenGLWidget(parent), painter(painter), pixels(pixels)
{
    setFixedSize(320, 160);
    setAutoFillBackground(false);
}

void Graphics::animate()
{
    update();
}


void Graphics::paintEvent(QPaintEvent *event)
{
    QPainter qpainter;
    qpainter.begin(this);
    qpainter.setRenderHint(QPainter::Antialiasing);
    painter->paint(&qpainter, event, pixels);
    qpainter.end();
}

// Painter

Painter::Painter()
{
    background = QBrush(QColor(0, 0, 0));
    rectangleBrush = QBrush(QColor(255,255,255));
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void Painter::paint(QPainter *painter, QPaintEvent *event, uint8_t* pixels)
{
    int scale = 5;
    for(int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            QRect rect = QRect(i * scale, j * scale, scale, scale);
            uint8_t pix = pixels[j * 64 + i];
            if(pix) {
                // draw white
                painter->fillRect(rect, rectangleBrush);
            } else {
                // draw bg color
                painter->fillRect(rect, background);
            }
        }
    }
    //painter->fillRect(event->rect(), background);

    //painter->translate(100, 100);
    //painter->setPen(textPen);
    //painter->setFont(textFont);
    //painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
}
