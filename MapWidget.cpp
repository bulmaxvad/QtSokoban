#include "MapWidget.h"
#include <QPaintEvent>
#include <QPainter>

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(0,0, 100,100);
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.drawText(0,0, "Hello");
}
