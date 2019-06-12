#include "Map.h"
#include "TextMap.h"
#include "MapItems/MapItemBase.h"
#include "MapItems/BoxMapItem.h"
#include "MapItems/FloorMapItem.h"
#include "MapItems/NoneMapItem.h"
#include "MapItems/NulledMapItem.h"
#include "MapItems/PlayerMapItem.h"
#include "MapItems/StockMapItem.h"
#include "MapItems/WallMapItem.h"
#include "MapManager.h"

namespace Sokoban {
;

Map::Map()
    : Map(QSize())
{}

Map::Map(const QSize& levelSize, int levelNumber /*=0*/)
{
    init(levelSize, levelNumber);
}

Map::Map(const Map& other)
{
    this->operator=(other);
}

Map::Map(const TextMap* textMap)
{
    if (nullptr == textMap)
        throw std::exception("Map::Map: textMap is NULL.");

    if (textMap->isEmpty())
    {
        init(QSize());
        return;
    }

    init(textMap->size(), textMap->number());

    TextMap tml{ textMap->normalized() };

    int y = 0;
    for (int txt_y = 0; txt_y < tml.size().height(); ++txt_y)
    {
        QString line = tml.line(txt_y);
        int x = 0;
        for (int txt_x = 0; txt_x < tml.size().width(); ++txt_x)
        {
            QChar txt_item = line[txt_x];
            MapItemBase* mi = charToMapItem(txt_item.toLatin1());
            mi->baseInit(this, QPoint(x,y)); //~ mi->setMap(this);
            m_data.at(y,x) = mi;
            ++x;
        }
        ++y;
    }

    //~ initMapItemsPositions();
}

void Map::init(const QSize& mapSize, int levelNumber /*=0*/)
{
    m_mapManager = nullptr;
    m_player     = nullptr;

    clear();
    m_data.resize( mapSize.isValid() ? mapSize : QSize(0,0) );
    m_number = levelNumber;
    m_data.setValues(nullptr);
}

void Map::clear()
{
    m_number = 0;
    m_data.clear();
    clearBoxes();
    clearStocks();
    if (nullptr != m_player)
    {
        delete m_player;
        m_player = nullptr;
    }
}

MapManager* Map::mapManager() const
{
    return m_mapManager;
}

void Map::setMapManager(MapManager* newMapManager)
{
    if (newMapManager == m_mapManager)
        return;

    m_mapManager = newMapManager;
}

Game* Map::game() const
{
    if (nullptr == mapManager())
        return nullptr;

    return mapManager()->game();
}

bool Map::isEmpty() const
{
    return m_data.isEmpty();
}

QSize Map::size() const
{
    return m_data.size();
}

MapItemBase* Map::staticItem(int column, int line, bool checkBound /*=false*/) const
{
    if (!checkBound)
        return m_data.at(line, column);

    if (0 > line || size().height() <= line)
        return nullptr;
    if (0 > column || size().width() <= column)
        return nullptr;

    return m_data.at(line, column);
}

MapItemBase* Map::staticItem(const QPoint& position, bool checkBound /*=false*/) const
{
    return staticItem(position.x(), position.y(), checkBound); //?!
}

PlayerMapItem* Map::player() const
{
    return m_player;
}

BoxMapItem* Map::boxItem(const QPoint& position) const
{
    BoxMapItem* result = nullptr;
    for (int i = 0; i < m_boxes.length(); ++i)
    {
        result = m_boxes.at(i);
        if (nullptr == result)
            continue;
        if (result->position() == position)
            return result;
    }

    return nullptr;
}

StockMapItem* Map::stockItem(const QPoint& position) const
{
    StockMapItem* result = nullptr;
    for (int i = 0; i < m_stocks.length(); ++i)
    {
        result = m_stocks.at(i);
        if (nullptr == result)
            continue;
        if (result->position() == position)
            return result;
    }

    return nullptr;
}

QVector<BoxMapItem*>& Map::boxes()
{
    return m_boxes;
}

QVector<StockMapItem*>& Map::stocks()
{
    return m_stocks;
}

void Map::boxHasChangedPosition(BoxMapItem* boxItem, const QPoint& oldPosition)
{}

int Map::number() const
{
    return m_number;
}

void Map::setNumber(int newNumber)
{
    m_number = newNumber;
}

void Map::initMapItemsPositions()
{
    for (int y = 0; y < size().height(); ++y)
        for (int x = 0; x < size().width(); ++x)
        {
            MapItemBase* mapItem = staticItem(x,y);
            if (nullptr == mapItem || mapItem->unknownType())
                continue;
            mapItem->setPosition(x,y);
        }
}

Map::operator bool() const
{
    return isEmpty();
}

Map& Map::operator =(const Map& other)
{
    if (&other == this)
        return *this;

    clear();

    m_mapManager = other.m_mapManager;
    m_number     = other.m_number;
    m_data       = other.m_data;

    // m_player = other.m_player;
    if (other.m_isPlayerMakes)
        copyPlayer(&other);
    else
        makePlayer();

    // m_boxes = other.m_boxes;
    if (other.m_isBoxesMakes)
        copyBoxes(&other);
    else
        makeBoxes();

    //m_stocks = other.m_stocks;
    if (other.m_isStocksMakes)
        copyStocks(&other);
    else
        makeStocks();

    initMapItemsPositions();
    return *this;
}

/*static*/ MapItemType Map::charToMapItemType(const QChar& ch)
{
    return Map::charToMapItemType(ch.toLatin1());
}

/*static*/ MapItemType Map::charToMapItemType(const char ch)
{
    switch (ch)
    {
    case '+': return MapItemType::Box;
    case ' ': return MapItemType::Floor;
    case '.': return MapItemType::None;
    case '@': return MapItemType::Player;
    case '-': return MapItemType::Stock;
    case '#': return MapItemType::Wall;
    default:  return MapItemType::Unknown;
    }
}

/*static*/ MapItemBase* Map::mapItemTypeToMapItem(MapItemType mit)
{
    switch (mit)
    {
    case MapItemType::Box:    return new BoxMapItem();
    case MapItemType::Floor:  return new FloorMapItem();
    case MapItemType::None:   return new NoneMapItem();
    case MapItemType::Player: return new PlayerMapItem();
    case MapItemType::Stock:  return new StockMapItem();
    case MapItemType::Wall:   return new WallMapItem();
    default:                  return new NulledMapItem;
    }
}

MapItemBase* Map::charToMapItem(const char ch)
{
    return mapItemTypeToMapItem( charToMapItemType(ch) );
}

PlayerMapItem* Map::makePlayer()
{
    if (nullptr != m_player)
        delete m_player;

    for (int y = 0; y < size().height(); ++y)
        for (int x = 0; x < size().width(); ++x)
        {
            if (MapItemType::Player == staticItem(x,y)->itemType())
            {
                PlayerMapItem* newPlayer = new PlayerMapItem { *static_cast<PlayerMapItem*>(staticItem(x,y)) };
                FloorMapItem*  newFloor  = new FloorMapItem  { this, newPlayer->position()                   };
                setStaticItem(newPlayer->position(), newFloor);

                m_player = newPlayer;
                m_isPlayerMakes = true;
                return m_player;
            }
        }

    m_isPlayerMakes = false;
    return nullptr;
}

QVector<BoxMapItem*>& Map::makeBoxes()
{
    clearBoxes();

    for (int y = 0; y < size().height(); ++y)
        for (int x = 0; x < size().width(); ++x)
        {
            if (MapItemType::Box == staticItem(x,y)->itemType())
            {
                BoxMapItem*   newBox   = new BoxMapItem   { *static_cast<BoxMapItem*>(staticItem(x, y)) };
                FloorMapItem* newFloor = new FloorMapItem { this, newBox->position()                    };
                setStaticItem(newBox->position(), newFloor);

                m_boxes.append(newBox);
            }

        }

    m_isBoxesMakes = true;
    return m_boxes;
}

QVector<StockMapItem*>& Map::makeStocks()
{
    clearStocks();

    for (int y = 0; y < size().height(); ++y)
        for (int x = 0; x < size().width(); ++x)
        {
            if (MapItemType::Stock == staticItem(x, y)->itemType())
            {
                StockMapItem* newStock = new StockMapItem{ *static_cast<StockMapItem*>(staticItem(x, y)) };
                FloorMapItem* newFloor = new FloorMapItem{ this, newStock->position()                    };
                setStaticItem(newStock->position(), newFloor);

                m_stocks.append(newStock);
            }

        }

    m_isBoxesMakes = true;
    return m_stocks;
}

void Map::clearBoxes()
{
    qDeleteAll(m_boxes.begin(), m_boxes.end());
    m_boxes.clear();
    m_isBoxesMakes = false;
}

void Map::clearStocks()
{
    qDeleteAll(m_stocks.begin(), m_stocks.end());
    m_stocks.clear();
    m_isStocksMakes = false;
}

PlayerMapItem* Map::copyPlayer(const Map* other)
{
    if (nullptr == other)
        return m_player;

    if (nullptr == m_player)
        delete m_player;

    m_player = new PlayerMapItem;
    m_player->baseInit(this, other->player()->position());

    m_isPlayerMakes = true;
    return m_player;
}

QVector<BoxMapItem*>& Map::copyBoxes(const Map* other)
{
    if (nullptr == other)
        return boxes();

    clearBoxes();

    for (int i = 0; i < other->m_boxes.length(); ++i)
    {
        BoxMapItem* box = new BoxMapItem;
        box->baseInit(this, other->m_boxes.at(i)->position());
        m_boxes.append(box);
    }

    m_isBoxesMakes = true;
    return boxes();
}

QVector<StockMapItem*>& Map::copyStocks(const Map* other)
{
    if (nullptr == other)
        return stocks();

    clearStocks();

    for (int i = 0; i < other->m_stocks.length(); ++i)
    {
        StockMapItem* stock = new StockMapItem;
        stock->baseInit(this, other->m_stocks.at(i)->position());
        m_stocks.append(stock);
    }

    m_isStocksMakes = true;
    return stocks();
}

void Map::setStaticItem(const QPoint& itemPos, MapItemBase* mapItem)
{
    setStaticItem(itemPos.x(), itemPos.y(), mapItem);
}

void Map::setStaticItem(int column, int line, MapItemBase* mapItem)
{
    if (m_data.isEmpty())
        return;

    m_data.at(line, column) = mapItem;
    return;
}

//bool Map::setData(const Map::Data& newData)
//{
//    if (&newData == &m_data)
//        return false;

//    clear();
//    m_data = newData;

//    if (nullptr != m_player)
//    {
//        delete m_player;
//        m_player = nullptr;
//    }

//    makePlayer();
//    makeBoxes();
//    makeStocks();

//    return true;
//}

void Map::assignMapItemsToThis()
{
    for (int y = 0; y < size().height(); ++y)
        for (int x = 0; x < size().width(); ++x)
            if (nullptr != staticItem(x, y))
                staticItem(x, y)->setMap(this);
}

} // end of namespace Sokoban



//   +----- columns ------+
//   |                    |
//   0  1  2  3  4  5  6  7
//0 [•][•][•][•][•][•][•][•] --+
//1 [•][•][•][•][•][•][•][•]   |
//2 [•][•][•][•][•][•][•][•]   |
//3 [•][•][•][•][•][•][•][•] lines
//4 [•][•][•][•][•][•][•][•]   |
//5 [•][•][•][•][•][•][•][•]   |
//6 [•][•][•][•][•][•][•][•]   |
//7 [•][•][•][•][•][•][•][•] --+
