#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QVector>

#include "MapItems/MapItemType.h"

namespace Sokoban {
;

//*********************************************************
// Forward declaration
//*********************************************************
class Map;
class MapManager;
class MapItemBase;
class Game;

//*********************************************************
// Implements
//*********************************************************

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(Game* game, QWidget *parent = nullptr);
    virtual ~MapWidget() override;

signals:

public slots:
    void drawStaticMapItems(const Map* map, QPainter& painter, MapItemType drawMapItemType) const;
    void drawBoxMapItems(Map* map, QPainter& painter) const;
    void drawStockMapItems(Map* map, QPainter& painter) const;
    void drawMap(Map* map, QPainter& painter) const;
    void forceUpdate();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    // Utils:
    QSize  calcItemSize() const;
    QPoint calcTopLeftForDrawMap() const;
    //void   drawNonStaticMapItems(Map* map, QPainter& painter, MapItemBase* mapItems, int mapItemCount) const;

public:
    // Getters:
    QSize    itemSize() const;
    Game*    game() const;
protected:
    QPixmap& itemTypePixmap(const MapItemType mapItemType) const;

protected:
    QSize  m_itemSize;
    QPoint m_drawOffset;
    Game*  m_game;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent* event) override;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent* event) override;
};

} // end of namespace Sokoban

#endif // MAPWIDGET_H
