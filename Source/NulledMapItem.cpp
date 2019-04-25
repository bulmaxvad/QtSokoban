#include "NulledMapItem.h"

namespace Sokoban {
;

NulledMapItem::NulledMapItem()
{

}

NulledMapItem::~NulledMapItem()
{
}

MapItemType NulledMapItem::itemType() const
{
    return MapItemType::Unknown;
}

const QPoint NulledMapItem::position() const
{
    return MapItemBase::invalidPoint();
}

void NulledMapItem::draw(Sokoban::QPainter * const painter) const
{
    Q_UNUSED(painter);
}

} // end of namespace Sokoban
