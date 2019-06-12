#include "StockMapItem.h"

namespace Sokoban {
;

StockMapItem::StockMapItem()
{}

MapItemType StockMapItem::itemType() const
{
    return MapItemType::Stock;
}

void StockMapItem::move(int dx, int dy)
{}

void StockMapItem::show()
{
    throw std::exception("Not implemented");
}

void StockMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool StockMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

} // end of namespace Sokoban
