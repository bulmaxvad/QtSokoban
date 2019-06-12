#ifndef MAPLEVELLIST_H
#define MAPLEVELLIST_H

#include <QVector>

#include "Map.h"

namespace Sokoban {
;

using MapList = QHash<int,Map>;

//class MapList : public QVector<Map>
//{
//public:
//    using QVector<Map>::QVector;
//    //MapList();

//protected:

//};

} // end of namespace Sokoban
#endif // MAPLEVELLIST_H
