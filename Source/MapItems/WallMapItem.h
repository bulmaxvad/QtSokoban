#ifndef WALLMAPITEM_H
#define WALLMAPITEM_H

#include <QWidget>
#include "MapItemBase.h"

namespace Sokoban {
;

class WallMapItem : public MapItemBase
{
public:
    WallMapItem();

// MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
};


} // end of namespace Sokoban
#endif // WALLMAPITEM_H
