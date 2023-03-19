#pragma once
#include <vector>

enum class PieceColor {
    None = 0,
    Cyan,
    Yellow,
    Green,
    Red,
    Blue,
    Orange,
    Purple
};

using PieceLine = std::vector<PieceColor>;
using PieceTable = std::vector<PieceLine>;
