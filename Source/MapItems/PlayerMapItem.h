#ifndef PLAYERMAPITEM_H
#define PLAYERMAPITEM_H

#include "MapItemBase.h"

namespace Sokoban {
;

class PlayerMapItem : public MapItemBase
{
public:
    PlayerMapItem();
    PlayerMapItem(Map* map, const QPoint& newPosition);

public:
    enum Direction
    {
        Up = static_cast<int>(MapItemType::Player_up),
        Right,
        Down,
        Left
    };
// MapItemBase interface
public:
    virtual MapItemType itemType() const override;
    virtual void        move(int dx, int dy) override;
    void                move(const QPoint& posOffset);
    virtual void        show() override;
    virtual void        hide() override;
    virtual bool        isVisible() override;
    virtual void        draw(QPainter* const painter) const override;

protected:
    Direction m_direction = Up;
};

} // end of namespace Sokoban
#endif // PLAYERMAPITEM_H
