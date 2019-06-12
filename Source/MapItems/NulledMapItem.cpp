#include "NulledMapItem.h"

namespace Sokoban {
;

NulledMapItem::NulledMapItem()
{}

NulledMapItem::~NulledMapItem()
{}

MapItemType NulledMapItem::itemType() const
{
    return MapItemType::Unknown;
}

void NulledMapItem::move(int dx, int dy)
{}

void NulledMapItem::show()
{
    throw std::exception("Not implemented");
}

void NulledMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool NulledMapItem::isVisible()
{
    return false;
}

} // end of namespace Sokoban
