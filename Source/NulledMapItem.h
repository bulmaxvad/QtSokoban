#ifndef NULLEDMAPITEM_H
#define NULLEDMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban {
;


class NulledMapItem : public MapItemBase
{
public:
    NulledMapItem();
    ~NulledMapItem() override;

    // MapItemBase interface
public:
    MapItemType  itemType() const override;
    const Map    *map() const override;
    void         setMap(Map *newMap) override;
    const QPoint position() const override;
    void         setPosition(int x, int y) override;
    void         setPosition(QPoint newPosition) override;
    void         move(int dx, int dy) override;
    bool         isMoveable() const override;
    void         show() override;
    void         hide() override;
    bool         isVisible() override;
    void         draw(QPainter * const painter) const override;
};

} // end of namespace Sokoban

#endif // NULLEDMAPITEM_H
