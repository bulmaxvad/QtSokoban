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
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
};

} // end of namespace Sokoban

#endif // NULLEDMAPITEM_H
