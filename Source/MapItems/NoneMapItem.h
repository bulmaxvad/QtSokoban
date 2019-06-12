#ifndef NONEMAPITEM_H
#define NONEMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban{
;

class NoneMapItem : public MapItemBase
{
public:
    NoneMapItem();

    // MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
};

} // end of namespace Sokoban
#endif // NONEMAPITEM_H
