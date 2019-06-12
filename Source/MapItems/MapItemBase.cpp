#include "MapItemBase.h"

#include <QPainter>
#include <QPixmap>

#include "../Map/Map.h"
#include "../Map/MapManager.h"
#include "../Map/MapWidget.h"
#include "../Game.h"

namespace Sokoban {
;

/*virtual*/ void MapItemBase::baseInit(Map* map, const QPoint& newPosition)
{
    m_map      = map;
    m_position = newPosition;
}

QPoint MapItemBase::invalidPoint()
{
    return QPoint(-1,-1);
}

/*virtual*/ MapItemType MapItemBase::itemType() const
{
    return MapItemType::Unknown;
}

bool MapItemBase::unknownType() const
{
    return itemType() == MapItemType::Unknown;
}

/*virtual*/ Map* MapItemBase::map() const
{
    return m_map;
}

/*virtual*/ void MapItemBase::setMap(Map* newMap)
{
    if (newMap == m_map)
        return;

    m_map = newMap;
}

/*virtual*/ QPoint MapItemBase::position() const
{
    return m_position;
}

void MapItemBase::setPosition(int x, int y)
{
    setPosition(QPoint(x, y));
}

/*virtual*/ void MapItemBase::setPosition(const QPoint& newPosition)
{
    if (newPosition == m_position)
        return;

    int new_x = newPosition.x();
    int new_y = newPosition.y();

    if (nullptr != map())
    {
        if (new_x >= map()->size().width())
            return;
        if (new_y >= map()->size().height())
            return;
    }

    m_position = newPosition;
}

/*virtual*/ bool MapItemBase::isStatic() const
{
    return MapItemType::None    == itemType() ||
           MapItemType::Wall    == itemType() ||
           MapItemType::Unknown == itemType();
}

void MapItemBase::draw(QPainter* const painter) const
{
    if (nullptr == painter)
        return;

    QPixmap& pixmap = game()->itemTypePixmap(itemType());
    QRect itemRect = calcDrawRect();
    painter->drawPixmap(itemRect, pixmap);
}

void MapItemBase::drawSpriteAs(QPainter* const painter, const MapItemType mapItemType) const
{
    if (nullptr == painter)
        return;

    QPixmap& pixmap   = game()->itemTypePixmap(mapItemType);
    QRect    itemRect = calcDrawRect();
    painter->drawPixmap(itemRect, pixmap);
}

QRect MapItemBase::calcDrawRect() const
{
    if (nullptr == mapWidget())
        return QRect();

    QSize itemSize = mapWidget()->itemSize();
    QPoint pos = position();
    pos.rx() *= itemSize.width();
    pos.ry() *= itemSize.height();

    QPoint bottomPos { game()->mapWidget()->itemSize().width(), game()->mapWidget()->itemSize().height() };
    return QRect { pos, pos+bottomPos };
}

Game* MapItemBase::game() const
{
    if (nullptr == mapManager())
        return nullptr;

    return mapManager()->game();
}

MapWidget* MapItemBase::mapWidget() const
{
    if (nullptr == game())
        return nullptr;

    return  game()->mapWidget();
}

MapManager* MapItemBase::mapManager() const
{
    if (nullptr == map())
        return nullptr;

    return map()->mapManager();
}

} // end of namespace Sokoban
