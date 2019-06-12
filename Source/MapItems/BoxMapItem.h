#ifndef BOXMAPITEM_H
#define BOXMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban {
;

class BoxMapItem : public MapItemBase
{
public:
    BoxMapItem();

    // MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    void                move(const QPoint& newPosition);
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
    bool                isStocked();
};

} // end of namespace Sokoban
#endif // BOXMAPITEM_H
