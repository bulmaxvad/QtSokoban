#include "Game.h"

#include "Map/MapWidget.h"
#include "SpriteManager.h"
#include "MapItems/PlayerMapItem.h"
#include "MapItems/BoxMapItem.h"
#include "MapItems/StockMapItem.h"

#include <QDir>
#include <QApplication>
#include <QMessageBox>

namespace Sokoban {
;

Game::Game(const QString& gameDir /*=QString()*/)
    : Game(nullptr, gameDir)
{}

Game::Game(QWidget* parentWidget, const QString& gameDir /*=QString()*/)
    : m_mapWidget(new MapWidget(this, parentWidget))
{
    m_gameDir = gameDir.isEmpty()
        ? QApplication::applicationDirPath()+"/GameDir/"
        : gameDir;

    mapManager().setGame(this);

    m_currentMap        = mapManager().mapByOrder(0);
    m_spritesFolderName = "Sprites/";

    loadSprites();
}

Game::~Game()
{}

QString Game::gameDir() const
{
    return m_gameDir;
}

void Game::setGameDir(const QString& newGameDir)
{
    if (newGameDir == m_gameDir) // Это быстрее чем делать лишнее присваивание
        return;

    m_gameDir = newGameDir;
    // TODO: makes notifications
    // ...
}

MapWidget* Game::mapWidget() const
{
    return m_mapWidget;
}

void Game::updateMapWidget()
{
    mapWidget()->forceUpdate();
}

Map* Game::currentMap() const
{
    return m_currentMap;
}

int Game::mapCount() const
{
    return m_mapManager.mapCount();
}

QPixmap& Game::itemTypePixmap(const MapItemType mapItemType)
{
    return m_spriteManager.pixmap(mapItemType);
}

bool Game::start()
{
    m_state = Started;
    return true;
}

bool Game::playNexLevel()
{
    Map* map = mapManager().mapByNumber(currentLevelNumber() +1);
    if (nullptr == map || 0 == map->number())
        return false;

    m_currentMap = map;
    return true;
}

bool Game::isPositionIntoBoard(const QPoint& itemPos) const
{
    if (0 > itemPos.x() || itemPos.x() >= currentMap()->size().width())
        return false;
    if (0 > itemPos.y() || itemPos.y() >= currentMap()->size().height())
        return false;

    return true;
}

int Game::currentLevelNumber() const
{
    if (nullptr == m_currentMap)
        return 0;

    return m_currentMap->number();
}

void Game::checkForEndGame()
{
    if (!isPlayerWins())
        return;
    if (End == state())
        return;

    QMessageBox::information(mapWidget()->parentWidget(), "Information", c_winLevelMessage);
    if (!playNexLevel())
    {
        m_state = End;
        QMessageBox::information(mapWidget()->parentWidget(), "Information", c_winGameMessage);
    }
    updateMapWidget();
}

bool Game::isPlayerWins() const
{
    Map* map = currentMap();
    if (nullptr == map)
        return false;
    if (map->boxes().length() != map->stocks().length())
        return false;

    int boxInStockCounter = 0;

    for (int bi = 0; bi < map->boxes().length(); ++bi)
        for (int si = 0; si < map->stocks().length(); ++si)
            if (map->boxes().at(bi)->position() == map->stocks().at(si)->position())
                ++boxInStockCounter;

    return  boxInStockCounter == map->stocks().length();
}

Game::State Game::state() const
{
    return m_state;
}

Error Game::loadSprites(const QString& spritesDir /*=QString()*/)
{
    if (spritesDir.isEmpty())
        m_spriteManager.loadMapItemPixmaps(m_gameDir + m_spritesFolderName);
    else
        m_spriteManager.loadMapItemPixmaps(spritesDir + m_spritesFolderName);

    return Error::NoError;
}

Error Game::loadMaps(const QString& levelsDir)
{
    Error result;

    if (levelsDir.isEmpty())
        result = m_mapManager.loadMaps(m_gameDir);
    else
        result = m_mapManager.loadMaps(levelsDir);

    if (mapCount() < 2)
        result = Error::NoMapsFound;

    m_currentMap = m_mapManager.mapByOrder(1);

    return result;
}

bool Game::movePlayerUp()
{
    return movePlayer(QPoint{0,-1});
}

bool Game::movePlayerRight()
{
    return movePlayer(QPoint{1,0});
}

bool Game::movePlayerDown()
{
    return movePlayer(QPoint{0,1});
}

bool Game::movePlayerLeft()
{
    return movePlayer(QPoint{-1,0});
}


bool Game::movePlayer(const QPoint& posOffset)
{
    if (!canPlayerMove(posOffset))
        return false;

    QPoint playerPosition = player()->position();

    MapItemBase* boxItem = currentMap()->boxItem(playerPosition+posOffset);
    if (nullptr != boxItem)
    {
        if (!canBoxMove(boxItem, posOffset))
            return false;

        static_cast<BoxMapItem*>(boxItem)->move(posOffset);
    }

    currentMap()->player()->move(posOffset);

    updateMapWidget();
    checkForEndGame();
    return true;
}

bool Game::canPlayerMove(const QPoint& posOffset) const
{
    return canPlayerMove(posOffset.x(), posOffset.y());
}

bool Game::canPlayerMove(int dx, int dy) const
{
    if (nullptr == currentMap() || nullptr == player())
        return false;
    if (0 == dx && 0 == dy)
        return false;

    QPoint offset{dx,dy};
    QPoint currPlayerPos = currentMap()->player()->position();
    QPoint newPlayerPos  = currPlayerPos+offset;

    if (!isPositionIntoBoard(newPlayerPos))
        return false;

    // Check for static map items:
    MapItemBase* miNext = currentMap()->staticItem(newPlayerPos);
    if (nullptr == miNext || miNext->unknownType() || miNext->isStatic())
        return false;

    //-------------------

    MapItemType nextItemType = miNext->itemType();

        if (MapItemType::Wall == nextItemType
       || MapItemType::Unknown == nextItemType)
    {
        return false;
    }
    if (MapItemType::Box == nextItemType)
    {
        QPoint nextNextPos { newPlayerPos+offset };
        MapItemBase* miNextNext = currentMap()->staticItem(nextNextPos);
        if (nullptr == miNextNext)
            return false;
        if (MapItemType::Box == miNextNext->itemType()
           || MapItemType::Wall == miNextNext->itemType())
        {
            return false;
        }
    }

    return true;
}

PlayerMapItem* Game::player() const
{
    if (nullptr == currentMap())
        return nullptr;

    return currentMap()->player();
}

bool Game::canBoxMove(MapItemBase* boxMapItem, const QPoint& posOffset) const
{
    if (nullptr == currentMap() || nullptr == boxMapItem)
        return false;
    if (posOffset.isNull())
        return false;

    QPoint newBoxPos  = boxMapItem->position()+posOffset;

    if (!isPositionIntoBoard(newBoxPos))
        return false;

    MapItemBase* nextMapItem = currentMap()->staticItem(newBoxPos);
    if (nullptr == nextMapItem)
        return false;

    // checks for forward static item
    if (nextMapItem->isStatic())
        return false;

    if (MapItemType::Box == nextMapItem->itemType())
        return false;

    return true;
}

QWidget* Game::parentOfMapWidget() const
{
    return mapWidget()->parentWidget();
}

MapManager& Game::mapManager()
{
    return m_mapManager;
}

SpriteManager& Game::spriteManager()
{
    return m_spriteManager;
}

void Game::updateMapWidget() const
{
    mapWidget()->update();
}

} // end of namespace Sokoban
