#include "TextMap.h"
#include "Map.h"
#include "MapItems/MapItemBase.h"

namespace Sokoban {
;

TextMap::TextMap()
    : TextMap(QSize(), 0)
{}

TextMap::TextMap(const QSize& levelSize, int levelNumber)
{
    init(levelSize, levelNumber);
}

TextMap::TextMap(const TextMap& otherLevel)
{
    this->operator=(otherLevel);
}

TextMap::TextMap(const TextMap&& otherLevel)
{
    this->operator=(std::move(otherLevel));
}

TextMap::TextMap(const Map* map)
{
    if (nullptr == map)
        throw std::exception("TextMap::TextMap: map is NULL.");

    if (map->isEmpty())
    {
        init(QSize(), 0);
        return;
    }

    init(map->size(), map->number());

    for (int map_y = 0; map_y < map->size().height(); ++map_y)
    {
        QString line;
        for (int map_x = 0; map_x < map->size().width(); ++map_x)
        {
            MapItemBase* mapItem = map->staticItem(map_x, map_y);
            QChar ch = mapItemToQChar(mapItem);
            line.append(ch);
        }
        appendLine(line);
    }
}

void TextMap::init(const QSize& levelSize, int levelNumber)
{
    clear();

    m_size   = levelSize.isValid() ? levelSize : QSize(0, 0);
    m_number = levelNumber;

    const QString templateStr{'.', m_size.width()};
    for (int i = 0; i < m_size.height(); ++i)
        appendLine(templateStr);
}

void TextMap::clear()
{
    m_lines.clear();
    m_size = QSize(0,0);
}

bool TextMap::isEmpty() const
{
    return 0 == m_lines.length()
           || m_size.isEmpty();
}

QChar TextMap::item(int line, int column) const
{
    if (line < 0 || line >= m_size.width())
        return NullChar;
    if (column < 0 || column >= m_size.height())
        return NullChar;

    return m_lines.at(line).at(column);
}

QString TextMap::line(int line) const
{
    if (line < 0 || line >= m_lines.length())
        return QString();

    return m_lines[line];
}

QSize TextMap::readLevel(QTextStream& stream, bool normalize /*=true*/, bool skipEmptyLines /*=true*/)
{
    clear();

    QString line;

    while (stream.readLineInto(&line))
    {
        if (skipEmptyLines && line.isEmpty())
            continue;
        if (line.length() >= 2 && line[0] == '/' && line[1] == '/')
            continue;

        break;
    }
    if (stream.atEnd())
        return QSize(0,0);

    m_number = getLevelNumberFrom(line);

    stream.readLineInto(&line);
    m_size = getMapSizeFrom(line);

    int lineCount     = 0;
    int maxLineLength = 0;
    qint64 lastStreamPosition = stream.pos();
    while (stream.readLineInto(&line) && !line.isEmpty())
    {
        maxLineLength = std::max(line.length(), maxLineLength);
        ++lineCount;
        appendLine(line);
    }
    if (!stream.atEnd())
        stream.seek(lastStreamPosition);

    m_size = QSize(maxLineLength, lineCount);

    if (normalize)
        this->normalize();

    return m_size;
}

QSize TextMap::size() const
{
    return m_size;
}

int TextMap::number() const
{
    return m_number;
}

void TextMap::setNumber(int newNumber)
{
    m_number = newNumber;
}

bool TextMap::appendLine(const QString& line)
{
    if (m_size.width() != line.length())
        return false;

    m_lines.append(line);
    return true;
}

TextMap& TextMap::normalize()
{
    if (isEmpty())
        return *this;

    int maxLenght = m_lines[0].length();
    for (Lines::const_iterator it = m_lines.cbegin() + 1; it != m_lines.cend(); ++it)
        maxLenght = std::max(maxLenght, it->length());

    for (Lines::iterator it = m_lines.begin(); it != m_lines.cend(); ++it)
        *it = padRight(*it, maxLenght, '.');

    return *this;
}

TextMap TextMap::normalized() const
{
    return TextMap(*this).normalize();
}

TextMap& TextMap::operator =(const TextMap& other)
{
    m_lines  = other.m_lines;
    m_number = other.m_number;
    m_size   = other.m_size;

    return *this;
}

TextMap& TextMap::operator =(const TextMap&& other)
{
    m_lines  = other.m_lines;
    m_number = other.m_number;
    m_size   = other.m_size;

    return *this;
}

QString TextMap::toString() const
{
    QString result;
    Lines::const_iterator it;
    for (it = m_lines.cbegin(); it != m_lines.cend(); ++it)
        result += *it + "\n";

    result.remove(result.length() -1, 1);

    return result;
}

bool TextMap::isLinesLengthConst(const Sokoban::TextMap& txtLevel)
{
    if (txtLevel.isEmpty())
        return false;

    int currLength = txtLevel.m_lines.at(0).length();
    Lines::const_iterator it = txtLevel.m_lines.cbegin();
    ++it;
    for (; it != txtLevel.m_lines.cend(); ++it)
    {
        if (it->length() != currLength)
            return false;
    }

    return true;
}

/*static*/ int TextMap::getLevelNumberFrom(const QString& str)
{
    QStringList list = str.split(":");

    if (list.count() != 2)
        return 0;
    if (list[0] != "level")
        return 0;

    bool ok;
    int result = list[1].toInt(&ok);
    if (!ok)
        return 0;

    return result;
}

/*static*/ QSize TextMap::getMapSizeFrom(const QString& str)
{
    QStringList list = str.split(":");

    if (list.count() != 2)
        return QSize();
    if (list[0] != "size")
        return QSize();

    list = list[1].split("*");
    if (list.count() != 2)
        return QSize();

    bool ok;
    QSize mapSize;
    mapSize.rwidth() = list[0].toInt(&ok);
    if (!ok)
        return QSize();
    mapSize.rheight() = list[1].toInt(&ok);
    if (!ok)
        return QSize();

    return mapSize;
}

/*static*/ QString TextMap::padRight(const QString& inStr, int totalLength, const char padChar)
{
    // "abc" => "abc" + {padChar * normalLength - "abc".length}
    // inStr = "abc", normalLength = 8, padChar = "+":
    // result => "abc+++++"

    if (totalLength <= inStr.length())
        return inStr;

    QString result(totalLength, padChar);
    for (int i = 0; i < inStr.length(); ++i)
        result[i] = inStr[i];

    return result;
}

/*static*/ QChar TextMap::mapItemToQChar(const MapItemBase* mapItem)
{
    if (nullptr == mapItem)
        return TextMap::NullChar;

    MapItemType mit = mapItem->itemType();
    switch (mit)
    {
    case MapItemType::Box:    return '+';
    case MapItemType::Floor:  return ' ';
    case MapItemType::None:   return '.';
    case MapItemType::Player: return '@';
    case MapItemType::Stock:  return '-';
    case MapItemType::Wall:   return '#';
    default:                  return TextMap::NullChar;
    }
}

} // end of namespace Sokoban
