#include "PlayerMapItem.h"

#include "../Map/Map.h"

namespace Sokoban {
;

PlayerMapItem::PlayerMapItem()
{}

PlayerMapItem::PlayerMapItem(Map* map, const QPoint& newPosition)
{
    baseInit(map, newPosition);
}

MapItemType PlayerMapItem::itemType() const
{
    return MapItemType::Player;
}

void PlayerMapItem::move(int dx, int dy)
{
    if (nullptr == map())
        return;

    if (dy > 0)
        m_direction = PlayerMapItem::Down;
    else if (dy < 0)
        m_direction = PlayerMapItem::Up;
    else if (dx > 0)
        m_direction = PlayerMapItem::Right;
    else if (dx < 0)
        m_direction = PlayerMapItem::Left;

    int x_pos = position().x() +dx;
    int y_pos = position().y() +dy;

    // [0..*..width()]
    if (0 > x_pos || map()->size().width() <= x_pos)
        return;
    if (0 > y_pos || map()->size().height() <= y_pos)
        return;

    m_position = QPoint(x_pos, y_pos);

    return;
}

void PlayerMapItem::move(const QPoint& posOffset)
{
    move(posOffset.x(), posOffset.y());
}

void PlayerMapItem::show()
{
    throw std::exception("Not implemented");
}

void PlayerMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool PlayerMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

void PlayerMapItem::draw(QPainter* const painter) const
{
    MapItemBase::drawSpriteAs(painter, static_cast<MapItemType>(m_direction));
}

} // end of namespace Sokoban
