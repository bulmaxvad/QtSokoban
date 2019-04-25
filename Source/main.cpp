#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>

#include "Map/MapWidget.h"
#include "MapItems/MapItemType.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MapWidget mw;

    //mw.setParent(&w);
    mw.setParent(w.centralWidget());

    w.show();

    return a.exec();
}
