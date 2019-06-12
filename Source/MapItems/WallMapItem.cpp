#include "WallMapItem.h"

namespace Sokoban {
;

WallMapItem::WallMapItem()
{}

MapItemType WallMapItem::itemType() const
{
    return MapItemType::Wall;
}

void WallMapItem::move(int dx, int dy)
{}

void WallMapItem::show()
{
    throw std::exception("Not implemented");
}

void WallMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool WallMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

} // end of namespace Sokoban
