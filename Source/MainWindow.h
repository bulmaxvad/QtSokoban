#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include "Singleton.h"

//#include "Map/Map.h"
namespace Sokoban {
class Map;
class MapWidget;
class MapManger;
class Game;
}

#include "MapItems/MapItemType.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //?? -- читать в книге
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

public:
    Sokoban::Game& game() const;
//?? -- читать в книге
public slots:
    void mnuFile_LoadLevels__clicked(bool checked);
    void mnuFile_NextLevel__clicked(bool checked);

private:
    Ui::MainWindow*          ui;
    Singleton<Sokoban::Game> m_game;

};

#endif // MAINWINDOW_H
