
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>

#include "MapLoader.h"
#include "MapItemBase.h"

namespace Sokoban {
;

MapLoader::MapLoader()
    : MapLoader(QString())
{

}

MapLoader::MapLoader(const QString& mapFileName)
    : m_mapFleName(mapFileName)
    , m_map(nullptr)
{

}

Error MapLoader::load(const QString &mapFileName)
{
    Error result;

    if (QFile::exists(mapFileName))
        return Error::FileNotFound;

    return result;
}

inline Map *MapLoader::map() const
{
    return m_map;
}


static const QString c_version_magic_string = "sokoban_game_map";





MapItemBase* mapItemTypeToMapItem(MapItemType mit)
{
    switch (mit)
    {
    case MapItemType::Box:    return new BoxMapItem();    break;
    case MapItemType::Floor:  return new FloorMapItem();  break;
    case MapItemType::Wall:   return new WallMapItem();   break;
    case MapItemType::Stock:  return new StockMapItem();  break;
    case MapItemType::Player: return new PlayerMapItem(); break;
    case MapItemType::None:   return new NoneMapItem();   break;
    }

    return new NulledMapItem;
}

MapItemType charToMapItemType(const char ch)
{
    switch (ch)
    {
    case ' ': return MapItemType::Floor;    break;
    case '#': return MapItemType::Wall;     break;
    case '-': return MapItemType::Stock;    break;
    case '.': return MapItemType::None;     break;
    case '+': return MapItemType::Box;      break;
    case '@': return MapItemType::Player;   break;
    }


    return MapItemType::Unknown;
}



QVector<MapItemBase*> charsToMapItems(const char* str, int length =-1)
{
    if (nullptr == str)
        return QVector<MapItemBase*>();

    length = (length == -1 ? static_cast<int>(strlen(str)) : length);

    for (int i=0; i < length; ++i)
    {

    }

}








Error MapLoader::checkMapFileStructure(const QString &mapFileName)
{
    Error result;

    QFile file(mapFileName);
    if (!file.open(QIODevice::ReadOnly))
        return Error::FileNotFound; // file.error();

    QTextStream ts(&file);

    QStringList versionLine = ts.readLine().split(":",  QString::SkipEmptyParts);

    // Check for number of occurences
    if (versionLine.count() < 2)
        return Error::InvalidMapFileStructure;

    // Check for magic string
    if (c_version_magic_string != versionLine[0])
        return Error::InvalidMapFileStructure;

    // Check for length of version
    if (versionLine[1].length() < 2)
        return Error::InvalidMapFileStructure;

    // Check for empty stream line
    if (0 != ts.readLine().length())
        return Error::InvalidMapFileStructure;

    // образец для считывания одного уровня:
    bool isParsed;
    int levelNo = ts.readLine().toInt(&isParsed);
    if (!isParsed)
        return Error::InvalidMapFileStructure;

    QStringList sizes = ts.readLine().split("*");
    if (sizes.count() < 2)
        return Error::InvalidMapFileStructure;


    while (!ts.atEnd())
    {
        QVector<MapItemBase*> mapLine = //mapItemTypeToMapItem(..);
    }

    return result;
}

} // end of namespace Sokoban
