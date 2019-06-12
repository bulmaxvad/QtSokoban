#include "BoxMapItem.h"

#include "Map/Map.h"

namespace Sokoban {
;


BoxMapItem::BoxMapItem()
{}

/*virtual*/ MapItemType BoxMapItem::itemType() const
{
    return MapItemType::Box;
}

void BoxMapItem::move(int dx, int dy)
{
    if (nullptr == map())
        return;

    int x_pos = position().x() +dx;
    int y_pos = position().y() +dy;

    // [0..*..width()] && // [0..*..height()]
    if (0 > x_pos || map()->size().width() <= x_pos)
        return;
    if (0 > y_pos || map()->size().height() <= y_pos)
        return;

    QPoint oldPosition;
    m_position = QPoint(x_pos, y_pos);
    map()->boxHasChangedPosition(this, oldPosition);

    return;
}

void BoxMapItem::move(const QPoint& newPosition)
{
    move(newPosition.x(), newPosition.y());
}

void BoxMapItem::show()
{
    throw std::exception("Not implemented");
}

void BoxMapItem::hide()
{
    throw std::exception("Not implemented");
}

bool BoxMapItem::isVisible()
{
    throw std::exception("Not implemented");
}

bool BoxMapItem::isStocked()
{
    return false;
}

} // end of namespace Sokoban

