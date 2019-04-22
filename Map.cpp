#include "Map.h"

#include "MapItemBase.h"
#include <QDebug>

namespace Sokoban {
;

Map::Map()
{
    init(0,0);
}

Map::Map(int width, int height)
{
    init(width, height);
}

Map::~Map()
{
    clear();
}

void Map::init(int width, int height)
{
    if (m_isInitializating)
        return;

    clear();
    m_isInitializating = true;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {

        }
    }

    m_isInitializating = false;
}

void Map::clear()
{
    bool prevInitializatingState = m_isInitializating;
    m_isInitializating = true;

    //~ int lineCount = m_items.size();
    //~ for (int y = 0; y < lineCount; ++y)
    for (QVector<MapItemBase*>& line : m_items)
    {
        //~ QVector<LevelItem*> line = m_items.takeLast();
        int itemCount = line.size();
        for (int x = 0; x < itemCount; ++x)
        {
            MapItemBase* mapItem = line.takeLast();
            if (nullptr != mapItem)
                mapItem->~MapItemBase();
        }

#ifdef _DEBUG
        if (line.size() > 0) qDebug() << "\n**ERROR**: 'line' after all taken is not empty\n";
#endif
        line.clear();
    }

    m_items.clear();

    m_isInitializating = prevInitializatingState;
}


} // end of namespace Sokoban
