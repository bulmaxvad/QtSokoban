#include "MapWidget.h"
#include <QPaintEvent>
#include <QPainter>

//#include "MapManager.h"
#include "MapItems/MapItemBase.h"
#include "MapItems/BoxMapItem.h"
#include "MapItems/StockMapItem.h"
#include "MapItems/PlayerMapItem.h"
#include "Game.h"


namespace Sokoban {
;

MapWidget::MapWidget(Game* game, QWidget *parent /*=nullptr*/)
    : QWidget(parent)
{
    m_game       = game;
    m_itemSize   = QSize (0,0);
    m_drawOffset = QPoint(0,0);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

MapWidget::~MapWidget()
{
// DON'T run this code because m_game was created by external
//    if (nullptr != m_game)
    //        delete m_game;
}

QPixmap& MapWidget::itemTypePixmap(const MapItemType mapItemType) const
{
    return game()->itemTypePixmap(mapItemType);
}

void MapWidget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            game()->movePlayerUp();
            event->accept();
            break;
        case Qt::Key_Right:
            game()->movePlayerRight();
            event->accept();
            break;
        case Qt::Key_Down:
            game()->movePlayerDown();
            event->accept();
            break;
        case Qt::Key_Left:
            game()->movePlayerLeft();
            event->accept();
            break;
        default:
            QWidget::keyPressEvent(event);
    }

    game()->checkForEndGame();
}

void MapWidget::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);

    if (nullptr == game())
        return;
    if (nullptr == game()->currentMap())
        return;

    m_itemSize = calcItemSize();
    m_drawOffset = calcTopLeftForDrawMap();
}

void MapWidget::drawStaticMapItems(const Map* map, QPainter& painter, MapItemType drawMapItemType) const
{
    if (nullptr == map || map->isEmpty())
        return;

    for (int y = 0; y < map->size().height(); ++y)
    {
        for (int x = 0; x < map->size().width(); ++x)
        {
            MapItemBase* mapItem = map->staticItem(x,y); //?!
            if (nullptr == mapItem)
                continue;

            if (drawMapItemType == mapItem->itemType())
                mapItem->draw(&painter);
        }
    }
}

void MapWidget::drawBoxMapItems(Map* map, QPainter& painter) const
{
    if (nullptr == map)
        return;

    for (int i = 0; i < map->boxes().length(); ++i)
        map->boxes().at(i)->draw(&painter);
}

void MapWidget::drawStockMapItems(Map* map, QPainter& painter) const
{
    if (nullptr == map)
        return;

    for (int i = 0; i < map->stocks().length(); ++i)
        map->stocks().at(i)->draw(&painter);
}

void MapWidget::drawMap(Map* map, QPainter& painter) const
{
    if (nullptr == map)
        return;

    painter.save();
    painter.translate(m_drawOffset);

    // paint Nones:
    drawStaticMapItems(map, painter, MapItemType::None);
    // paint Walls:
    drawStaticMapItems(map, painter, MapItemType::Wall);
    // paint Floors:
    drawStaticMapItems(map, painter, MapItemType::Floor);

    // paint Boxes:
    drawBoxMapItems(map, painter);

    // paint Stocks:
    drawStockMapItems(map, painter);

    // paint Player
    if (nullptr != map->player())
        map->player()->draw(&painter);

    painter.restore();
}

void MapWidget::forceUpdate()
{
    m_itemSize   = calcItemSize();
    m_drawOffset = calcTopLeftForDrawMap();
    repaint();
    //updateGeometry();
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    Sokoban::Map* map = game()->currentMap();
    if (nullptr == map)
        return;

    drawMap(map, painter);
}

QSize MapWidget::calcItemSize() const
{
    if (nullptr == game())
        return QSize(64,64);
    if (nullptr == game()->currentMap())
        return QSize(64,64);

    int minWidgetSizeValue = std::min( size().width(), size().height() );

    int mapItemsHeightCount = minWidgetSizeValue / game()->currentMap()->size().height();
    int mapItemsWidthCount  = minWidgetSizeValue / game()->currentMap()->size().width();
    int maxMapItemSizeValue = std::max( mapItemsWidthCount, mapItemsHeightCount );

    return QSize(maxMapItemSizeValue, maxMapItemSizeValue);
}

QPoint MapWidget::calcTopLeftForDrawMap() const
{
    int mapWidth  = m_itemSize.width()  * game()->currentMap()->size().width();
    int mapHeight = m_itemSize.height() * game()->currentMap()->size().height();
    return QPoint((size().width() -mapWidth) /2, (size().height() -mapHeight) /2);
}

//void MapWidget::drawNonStaticMapItems(Map* map, QPainter& painter, const MapItemBase* mapItems, int mapItemCount) const
//{}

QSize MapWidget::itemSize() const
{
    return m_itemSize;
}

Game* MapWidget::game() const
{
    return m_game;
}

} // end of namespace Sokoban
