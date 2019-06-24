#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>

#include "Map/MapWidget.h"
#include "MapItems/MapItemType.h"

#include "Array2D.h"

//int foo(Array2D<int>* a1, Array2D<int>* a2)
//{
//    Array2D<int>& f1 = *a1;
//    Array2D<int>& f2 = *a2;

//    ...

//    a1 = a2;
//}


int main(int argc, char *argv[])
{
    using namespace Sokoban;

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
