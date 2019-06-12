#ifndef MAPLEVEL_H
#define MAPLEVEL_H

#include <QList>
#include <QVector>
#include <QChar>

#include "MapItems/MapItemType.h"


#include "../Array2D.h"

namespace Sokoban {
;

class MapItemBase;
class BoxMapItem;
class StockMapItem;
class PlayerMapItem;
class TextMap;
class Game;
class MapManager;

class Map
{
public:
    using DataLine = QVector<MapItemBase*>;
    using Data     = Array2D<MapItemBase*>;

public:
    Map();
    Map(const QSize& levelSize, int levelNumber =0);
    Map(const Map& other);
    explicit Map(const TextMap* textMap);
protected:
    void init(const QSize& levelSize, int levelNumber =0);
    void clear();

public:
    MapManager* mapManager() const;
    void setMapManager(MapManager* newMapManager);

    Game* game() const;

    bool  isEmpty() const;
    QSize size() const;

    MapItemBase* staticItem(int column, int line, bool checkBound =false) const;
    MapItemBase* staticItem(const QPoint& position, bool checkBound =false) const;

    PlayerMapItem*          player() const;
    BoxMapItem*             boxItem(const QPoint& position) const;
    StockMapItem*           stockItem(const QPoint& position) const;
    QVector<BoxMapItem*>&   boxes();
    QVector<StockMapItem*>& stocks();

    void boxHasChangedPosition(BoxMapItem* boxItem, const QPoint& oldPosition);


    int  number() const;
    void setNumber(int newNumber);

    void initMapItemsPositions();

public:
    explicit operator bool() const;
    Map& operator = (const Map& other);

public:
    static MapItemType  charToMapItemType(const char   ch);
    static MapItemType  charToMapItemType(const QChar& ch);
    static MapItemBase* mapItemTypeToMapItem(MapItemType mit);

protected:
    MapItemBase*            charToMapItem(const char ch);
    //~PlayerMapItem*          findPlayer(QPoint* playerPos =nullptr) const;
    PlayerMapItem*          makePlayer();
    QVector<BoxMapItem*>&   makeBoxes();
    QVector<StockMapItem*>& makeStocks();
    void                    clearBoxes();
    void                    clearStocks();

    PlayerMapItem*          copyPlayer(const Map* other);
    QVector<BoxMapItem*>&   copyBoxes(const Map* other);
    QVector<StockMapItem*>& copyStocks(const Map* other);

    void                    setStaticItem(const QPoint& itemPos, MapItemBase* mapItem);
    void                    setStaticItem(int column, int line,  MapItemBase* mapItem);
protected:
    //bool setData(const Data& newData);
    inline const Data& data() const { return m_data; }
    inline Data&      rdata()       { return m_data; }

    void assignMapItemsToThis();

private:
    friend class MapManager;

protected:
    bool                   m_isBoxesMakes  = false;
    bool                   m_isPlayerMakes = false;
    bool                   m_isStocksMakes = false;
    Data                   m_data;
    int                    m_number;
    PlayerMapItem*         m_player = nullptr;
    QVector<BoxMapItem*>   m_boxes;
    QVector<StockMapItem*> m_stocks;
    MapManager*            m_mapManager = nullptr;
};

/* FOR DELETE
bool Map::isLineCountConst(const Map& map);
bool Map::isLineCountConst(const Map::Data& mapData);
*/


} // end of namespace Sokoban

#endif // MAPLEVEL_H
