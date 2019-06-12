#pragma once
#ifndef MAPITEMTYPE_H
#define MAPITEMTYPE_H

#include <QHash>

namespace Sokoban {
;


enum class MapItemType
{
    Unknown = 0,

    //
    // Пустое пространство уровня.
    //
    None,

    //
    // Кирпич стены.
    //
    Wall,

    //
    // Перемещаемый ящик.
    //
    Box,

    //
    // Элемент пола -- "плитка".
    //
    Floor,

    //
    // Место, куда должен быть перемещён ящик.
    //
    Stock,

    //
    // Игрок.
    //
    Player,
    Player_up = Player,
    Player_right,
    Player_down,
    Player_left,
};

inline uint qHash(const MapItemType& mit, uint seed)
{
    return ::qHash(static_cast<int>(mit), seed);
}

inline bool operator!(MapItemType mit)
{
    return mit == MapItemType::Unknown;
}



} // end of namespace Sokoban
#endif // MAPITEMTYPE_H
