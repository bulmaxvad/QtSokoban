#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAPWIDGET_H
