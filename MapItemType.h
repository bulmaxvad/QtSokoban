#pragma once
#ifndef MAPITEMTYPE_H
#define MAPITEMTYPE_H

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
};

inline bool operator!(Sokoban::MapItemType mit)
{
    return mit == Sokoban::MapItemType::Unknown;
}



} // end of namespace Sokoban
#endif // MAPITEMTYPE_H
