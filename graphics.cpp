#include "graphics.h"
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>

Graphics::Graphics(Painter *painter, QWidget *parent) : QOpenGLWidget(parent), painter(painter)
{
    elapsed = 0;
    setFixedSize(320, 160);
    setAutoFillBackground(false);
}

void Graphics::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}


void Graphics::paintEvent(QPaintEvent *event)
{
    QPainter qpainter;
    qpainter.begin(this);
    qpainter.setRenderHint(QPainter::Antialiasing);
    painter->paint(&qpainter, event, elapsed);
    qpainter.end();
}

// Painter

Painter::Painter()
{
    background = QBrush(QColor(64, 32, 64));
    rectangleBrush = QBrush(QColor(255,255,255));
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void Painter::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
}
