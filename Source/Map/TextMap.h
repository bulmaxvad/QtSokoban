#ifndef TEXTMAPLEVEL_H
#define TEXTMAPLEVEL_H

// SEE bottom file

#include <QVector>
#include <QString>
#include <QSize>
#include <QTextStream>

#include "MapItems/MapItemType.h"

namespace Sokoban {
;

class Map;
class MapItemBase;

class TextMap
{
public:
    using Lines = QVector<QString>;

public:
    static const char NullChar = '\0';

public:
    TextMap();
    TextMap(const QSize& levelSize, int levelNumber);
    TextMap(const TextMap& otherLevel);
    TextMap(const TextMap&& otherLevel);
    TextMap(const Map* map);
protected:
    void init(const QSize& levelSize, int levelNumber);
    void clear();

public:
    bool  isEmpty() const;
    QSize size() const;

    int  number() const;
    void setNumber(int newNumber);

    QChar   item(int line, int column) const;
    QString line(int line) const;

public:
    QSize readLevel(QTextStream& stream, bool normalize =true, bool skipEmptyLines =true);
    bool  appendLine(const QString& line);

    TextMap& normalize();
    TextMap  normalized() const;

    TextMap& operator = (const TextMap& other);
    TextMap& operator = (const TextMap&& other);

    QString toString() const;
public:
    static bool    isLinesLengthConst(const TextMap& txtLevel);
    static int     getLevelNumberFrom(const QString& str);
    static QSize   getMapSizeFrom(const QString& str);
    static QString padRight(const QString& inStr, int totalLength, const char padChar);

    static QChar   mapItemToQChar(const MapItemBase* mapItem);


protected:
    Lines m_lines;
    QSize m_size;
    int   m_number;
};

} // namespace Sokoban



// Comments
// ~~~~~~~~
//
//  0  1  2  3  4  5  6 -- ширина уровня
// [.][.][.][.][.][.][.][.]
// [.][.][.][.][.][.][.]
// [.][.][.][.][.]
// [.][.][.][.][.][.][.][.][.]
// [.][.][.][.][.]
// [.][.][.][.][.]
// [.][.][.][.][.][.][.][.]




#endif // TEXTMAPLEVEL_H
