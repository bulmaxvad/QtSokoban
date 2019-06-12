#include "NoneMapItem.h"

namespace Sokoban {
;

NoneMapItem::NoneMapItem()
{}

MapItemType NoneMapItem::itemType() const
{
    return MapItemType::None;
}

void NoneMapItem::move(int dx, int dy)
{}

void NoneMapItem::show()
{
    throw std::exception("Not implemented");
}

void NoneMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool NoneMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

} // end of namespace Sokoban
