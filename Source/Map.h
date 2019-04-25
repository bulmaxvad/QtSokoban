#ifndef MAP_H
#define MAP_H

#include <QPoint>
#include <QSize>
#include <QVector>

namespace Sokoban {
;

class MapItemBase;

class Map
{
public:
    Map();
    Map(int width, int height);
    ~Map();

public:

/* Initializatiopn methods */
    //
    // Initialize size of level
    //
    void init(int width, int height);

    //
    // Clear the level
    //
    void clear();

public:

/* Map's methods */
    //
    // return number of level
    //
    int  number() const;

    //
    // Check whether map is initialized
    //
    bool isInitialized() const;

public:
/* Item manipulation's methods */
    //
    // Return type of item at x y position
    //
    MapItemBase* itemAt(int x, int y) const;

    //
    // Return type of item at QPoint position
    //
    MapItemBase* itemAt(const QPoint& position) const;

    //
    // Check whether item can move at x y position
    //
    bool itemCanMove(int newX, int newY, MapItemBase* item) const;

    //
    // Set new item at x y position
    //
    void setItem(const MapItemBase* newItem, int x, int y);

    //
    // Set new item at QPoint position
    //
    void setItem(const MapItemBase* newItem, QPoint position);

    //
    // Remove item at x y position
    //
    void removeItemAt(int x, int y);

    //
    // Remove item at QPoint position
    //
    void removeItemAt(const QPoint& position);

    //
    // Delete item at x y position
    //
    void deleteItemAt(int x, int y);

    //
    // Delete item at QPoint position
    //
    void deleteItemAt(const QPoint& position);

public:
/* Map size manupulation's methods */
    //
    // Return size of the map
    //
    QSize size() const;

    //
    // Set size of the map
    //
    QSize setSize();


protected:
    QVector< QVector<MapItemBase*> > m_items;
    volatile bool m_isInitializating;
    bool m_isInitialized;

};

} // end of namespace Sokoban
#endif // MAP_H
