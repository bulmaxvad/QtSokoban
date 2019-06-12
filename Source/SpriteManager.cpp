#include "SpriteManager.h"

#include <QDir>


namespace Sokoban {
;

SpriteManager::SpriteManager()
{
    //! TEST ONLY!
}

void SpriteManager::loadMapItemPixmaps(const QString& pixmapPath)
{
    QDir path(pixmapPath);

    if (!path.exists(pixmapPath))
        throw std::exception(QString("SpriteManager::loadMapItemPixmaps: '%1' ").arg(pixmapPath).toLatin1());

    m_mapItemTypePixmaps.clear();

    using namespace Sokoban;
    const QHash<MapItemType,QString> pixmapFileNames =
    {
        { MapItemType::None,         "Item_None_128@24.png"         },
        { MapItemType::Floor,        "Item_Floor_128@24.png"        },
        { MapItemType::Box,          "Item_Box_128@24.png"          },
        { MapItemType::Wall,         "Item_Wall_128@24.png"         },
        { MapItemType::Stock,        "Item_Stock2_128@24.png"       },
        { MapItemType::Player_up,    "Item_Player_up_128@24.png"    },
        { MapItemType::Player_right, "Item_Player_right_128@24.png" },
        { MapItemType::Player_down,  "Item_Player_down_128@24.png"  },
        { MapItemType::Player_left,  "Item_Player_left_128@24.png"  }
    };

    QHash<MapItemType,QString>::const_iterator it;
    for (it = pixmapFileNames.cbegin(); it != pixmapFileNames.cend(); ++it)
    {
        QString fullPath = path.path() + "/" + it.value();
        m_mapItemTypePixmaps[it.key()] = QPixmap(fullPath);
    }

}

QPixmap& SpriteManager::pixmap(const MapItemType mapItemType)
{
    return m_mapItemTypePixmaps[mapItemType];
}

} // end of namespace Sokoban
