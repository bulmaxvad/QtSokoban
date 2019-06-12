#include "FloorMapItem.h"


namespace Sokoban {
;

FloorMapItem::FloorMapItem()
{}

FloorMapItem::FloorMapItem(Map* map, const QPoint& newPosition)
{
    baseInit(map, newPosition);
}

MapItemType FloorMapItem::itemType() const
{
    return MapItemType::Floor;
}

void FloorMapItem::move(int dx, int dy)
{}

void FloorMapItem::show()
{
    throw std::exception("Not implemented");
}

void FloorMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool FloorMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

} // end of namespace Sokoban
