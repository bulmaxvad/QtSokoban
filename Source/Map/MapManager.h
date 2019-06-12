#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QPixmap>
#include <QString>
#include <QTextStream>
#include <QHash>

#include "Error.h"
#include "Map.h"
#include "MapList.h"
#include "Map/TextMap.h"


namespace Sokoban{
;

class MapManager
{
public:
    MapManager();
    MapManager(Game* game);
    virtual ~MapManager();

public:
    Error loadMaps(const QString& mapFileName);

    Map*  mapByNumber(int levelNumber, bool isFailGetNext =true) const;
    Map*  mapByOrder (int orderNumber) const;
    Map*  addMap(Map* newMap);
    Map*  addMap(const TextMap& newMap);
    Map*  emptyMap() const;
    int   mapCount() const;

    Game* game() const;
    void  setGame(Game* otherGame);
public:
    static Error isMapFile(const QString& mapFileName);
    static Error isMapFile(QTextStream&   mapFileStream, bool saveStreamPosition =true);

protected:
    TextMap readNextMap(QTextStream& stream) const;

protected:
    Game*    m_game;
    QString  m_mapFileName;
    MapList* m_maps;
    Map*     m_emptyMap;
};


} // end of namespace Sokoban

#endif // MAPLOADER_H
