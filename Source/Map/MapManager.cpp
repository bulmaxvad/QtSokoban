#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDir>

#include "MapItems/NulledMapItem.h"

#include "MapManager.h"
#include "MapItems/MapItemBase.h"

#include "../Singleton.h"
#include "../Game.h"

namespace Sokoban {
;

static const QString c_version_magic_string = "sokoban_game_map";

MapManager::MapManager()
    : MapManager(nullptr)
{}

MapManager::MapManager(Game* game)
    : m_game(game)
{
    m_maps = new MapList();

    // adding an empty Map object:
    m_maps->insert(0, Map());
    m_emptyMap = &m_maps->operator[](0);
}

MapManager::~MapManager()
{
    delete m_maps;
}

TextMap MapManager::readNextMap(QTextStream& stream) const
{
    TextMap result;
    QString line;

    // ищем пустую строку:
    while (stream.readLineInto(&line) && line.isEmpty())
    {}

    if (stream.atEnd())
        return result;

    // считываем уровень:
    result.readLevel(stream);

    return result;
}

Error MapManager::loadMaps(const QString& mapFileName)
{
    QFile mapFile(mapFileName);

    if (!mapFile.exists())
        return Error::FileNotFound;

    mapFile.open(QIODevice::ReadOnly);

    QTextStream mapFileStream(&mapFile);
    if (Error::NoError != isMapFile(mapFileStream))
        return Error::InvalidMapFileStructure;

    int mapCounter = 0;
    while (!mapFileStream.atEnd())
    {
        QString line;
        mapFileStream.readLineInto(&line);
        if (!line.isEmpty())
            continue;

        TextMap textMap;
        textMap.readLevel(mapFileStream);
        if (!textMap.isEmpty())
            addMap(textMap);
        ++mapCounter;
    }

    return Error::NoError;
}

Map* MapManager::mapByNumber(int levelNumber, bool isFailGetNext /*=true*/) const
{
    if (!m_maps->contains(levelNumber) && !isFailGetNext)
        return nullptr;

    QHash<int,Map>::iterator it;
    for (it = m_maps->begin(); it != m_maps->end(); ++it)
    {
        if (it->number() == levelNumber +1)
            return &it.value();
    }

    return &(*m_maps)[levelNumber];
}

Map* MapManager::mapByOrder(int orderNumber) const
{
    if (orderNumber >= m_maps->count() || orderNumber < 0)
        return nullptr;

    MapList::iterator mapIt = m_maps->begin()+orderNumber;
    Map* map = &mapIt.value();
    if (emptyMap() != map)
        return map; // return if mapIt is not emptyMap;

    // case #1: [21659.]
    if (m_maps->end()-1 == mapIt)
        return nullptr;

    // case #2: [.21659]
    if (m_maps->begin() == mapIt)
        return &(++mapIt).value();

    // case #3: [216.59]
    return &(++mapIt).value();
}

Map* MapManager::addMap(Map* newMap)
{
    if (nullptr == newMap)
        return nullptr;
    if (0 >= newMap->number())
        return emptyMap();

    newMap->setMapManager(this);

    int levelNumber = newMap->number();
    if (m_maps->contains(levelNumber))
        (*m_maps)[levelNumber] = *newMap;
    else
        m_maps->insert(levelNumber, *newMap);

    // !!!
    m_emptyMap = &(*m_maps)[0];

    return &(*m_maps)[newMap->number()];
}

Map* MapManager::addMap(const TextMap& newMap)
{
    if (newMap.isEmpty())
        return nullptr;

    Map* result = new Map(&newMap);
    return addMap(result);
}

Map* MapManager::emptyMap() const
{
    return m_emptyMap; // equal for: &m_levels->operator[](0);
}

int MapManager::mapCount() const
{
    return m_maps->count();
}

Game* MapManager::game() const
{
    return m_game;
}

void MapManager::setGame(Game* otherGame)
{
    m_game = otherGame;
}

/*static*/ Error MapManager::isMapFile(const QString& mapFileName)
{
    QFile mapFile(mapFileName);
    if (!mapFile.exists())
        return Error::FileNotFound;
    if (!mapFile.open(QIODevice::ReadOnly))
        return Error::FileError; // file.error();

    QTextStream ts(&mapFile);
    return isMapFile(ts);
}

/*static*/ Error MapManager::isMapFile(QTextStream& mapFileStream, bool saveStreamPosition /*=true*/)
{
    qint64 prevStreamPosition = mapFileStream.pos();
    QString str = mapFileStream.readLine();

    QStringList versionLine = str.split(":",  QString::SkipEmptyParts);

    // Check for number of occurences
    if (versionLine.count() < 2)
    {
        if (saveStreamPosition)
            mapFileStream.seek(prevStreamPosition);
        return Error::InvalidMapFileStructure;
    }

    // Check for magic string
    if (c_version_magic_string != versionLine[0])
    {
        if (saveStreamPosition)
            mapFileStream.seek(prevStreamPosition);
        return Error::InvalidMapFileStructure;
    }

    // Check for length of version
    if (versionLine[1].length() < 2)
    {
        if (saveStreamPosition)
            mapFileStream.seek(prevStreamPosition);
        return Error::InvalidMapFileStructure;
    }

    // Check for empty stream line
    if (0 != mapFileStream.readLine().length())
    {
        if (saveStreamPosition)
            mapFileStream.seek(prevStreamPosition);
        return Error::InvalidMapFileStructure;
    }

    if (saveStreamPosition)
        mapFileStream.seek(prevStreamPosition);

    return Error::NoError;
}

} // end of namespace Sokoban
