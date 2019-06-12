#ifndef MAPITEM_H
#define MAPITEM_H

#include <QPoint>
#include <QRect>
#include "MapItemType.h"

// Forward declaration
class QPainter;
class QPixmap;

namespace Sokoban {
;

// Forward declaration
class Game;
class Map;
class MapWidget;
class MapManager;
// end of forward declaration


class MapItemBase
{
protected:
    MapItemBase() = default;
public:
    virtual ~MapItemBase() = default;
    virtual void baseInit(Map* map, const QPoint& newPosition);
public:
    static QPoint invalidPoint();

public:
/* Map's items kinds methods */

    //
    // Return type of map item
    //
    virtual MapItemType itemType() const;

    //
    // Return none type
    //
    bool unknownType() const;

/* Map's methods */
    //
    // Return the parent map level
    //
    virtual Map* map() const;

    //
    // Select map
    //
    virtual void setMap(Map* newMap);

/* Position's methods */
    //
    // Return position throught QPoint
    //
    virtual QPoint position() const;

    //
    // Set position by x and y coordinates
    //
    void setPosition(int x, int y);
    //
    // Set position by QPoint
    //
    virtual void setPosition(const QPoint& newPosition);

    //
    //  Move Item to required position
    //
    virtual void move(int dx, int dy) = 0;

/* Move check's methods */
    //
    // Check whether the item is moveable on Player layer
    //
    virtual bool isStatic() const;
    //? virtual bool canMove(int newX, int newY) const = 0;

/* Visible's methods */
    //
    // Make item visible
    //
    virtual void show() = 0;

    //
    // Make item invisible
    //
    virtual void hide() = 0;

    //
    // Check whether the item is visible
    //
    virtual bool isVisible() = 0;

/* Paint's methods */
    //
    // Draw level items
    //
    virtual void draw(QPainter* const painter) const;
    void         drawSpriteAs(QPainter* const painter, const MapItemType mapItemType) const;
    QRect        calcDrawRect() const;

protected:
    Game*       game()       const;
    MapWidget*  mapWidget()  const;
    MapManager* mapManager() const;

/* Fields */
protected:
    QPoint m_position;
    Map*   m_map;

};

} // end of namespace Sokoban
#endif // MAPITEM_H
