#ifndef STOCKMAPITEM_H
#define STOCKMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban {
;

class StockMapItem : public MapItemBase
{
public:
    StockMapItem();

// MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
};

} // end of namespace Sokoban

#endif // STOCKMAPITEM_H
