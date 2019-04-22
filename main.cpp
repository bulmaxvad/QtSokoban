#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>

#include "MapWidget.h"
#include "MapItemType.h"

//bool operator!(Sokoban::MapItemType mit)
//{
//    return mit == Sokoban::MapItemType::Unknown;
//}

void testMapItemType_operator()
{
    auto mit = Sokoban::MapItemType::Unknown;

    if (!mit)
        QMessageBox::information(nullptr, "Info", "mit eq Sokoban::MapItemType::Unknown");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MapWidget mw;

    //
    // TESTING
    //
    testMapItemType_operator();
    // END OF TESTING


    //mw.setParent(&w);
    mw.setParent(w.centralWidget());

    w.show();

    return a.exec();
}
