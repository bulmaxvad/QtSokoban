#ifndef FLOORMAPITEM_H
#define FLOORMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban {
;

class FloorMapItem : public MapItemBase
{
public:
    FloorMapItem();
    FloorMapItem(Map* map, const QPoint& newPosition);

// MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
};

} // end of namespace Sokoban

#endif // FLOORMAPITEM_H
