#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <QHash>
#include <QString>
#include <QPixmap>

#include "MapItems/MapItemType.h"

namespace Sokoban {
;

class SpriteManager
{
public:
    SpriteManager();

public:
    void     loadMapItemPixmaps(const QString& pixmapPath);
    QPixmap& pixmap(const MapItemType mapItemType);

protected:
    QHash<MapItemType,QPixmap> m_mapItemTypePixmaps;
};

} // end of namespace Sokoban

#endif // SPRITEMANAGER_H
