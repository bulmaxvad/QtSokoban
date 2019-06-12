#ifndef GAME_H
#define GAME_H

#include <QPoint>

#include "Map/MapManager.h"
#include "SpriteManager.h"

class QWidget;

namespace Sokoban {
;

class Map;
class MapWidget;
class MapManager;

class Game
{
public:
    Game(const QString& gameDir =QString());
    Game(QWidget* parentOfMapWidget, const QString& gameDir =QString());
    virtual ~Game();

public:
    enum State
    {
        Unknown = 0,
        Started,
        Paused,
        Stopped,
        Serviced
    };

public:
    QString gameDir() const;
    void    setGameDir(const QString& newGameDir);

    MapWidget* mapWidget() const;
    void       updateMapWidget();

    Map* currentMap() const;
    int  mapCount() const;

    QPixmap& itemTypePixmap(const MapItemType mapItemType);

public:
    bool start();
    bool startFrom(int levelNumber);
    bool pause();
    bool stop();

    bool playNexLevel();


    int  currentLevelNumber() const;

    void checkForEndGame();
    bool isPlayerWins() const;
    State state() const;

public:
    Error loadSprites(const QString& spritesDir =QString());
    Error loadMaps(const QString& levelsDir =QString());

    QPoint playerPos() const;
    void   setPlayerPos(const QPoint& newPos);

    bool   movePlayerUp();
    bool   movePlayerRight();
    bool   movePlayerDown();
    bool   movePlayerLeft();

    bool   movePlayerBy(int dx, int dy);

protected:
    bool movePlayer(const QPoint& posOffset);
    bool canPlayerMove(const QPoint& posOffset) const;
    bool canPlayerMove(int dx, int dy) const;

    PlayerMapItem* player() const;

    bool canBoxMove(MapItemBase* boxMapItem, const QPoint& posOffset) const;


    MapWidget* setMapWidget(MapWidget* newMapWidget);
    QWidget*   parentOfMapWidget() const;

    MapManager&    mapManager();
    SpriteManager& spriteManager();

    //? void setState(State newState);

protected:
    //??
    void updateMapWidget() const;

protected:
    // Game widget:
    MapWidget*    m_mapWidget;

    // States of Game:
    QString       m_gameDir;
    QString       m_spritesFolderName;
    State         m_state;

    // Some currents variables:
    Map*          m_currentMap;

    // Built-in managers:
    MapManager    m_mapManager;
    SpriteManager m_spriteManager;
};

} // end of namespace Sokoban

#endif // GAME_H
