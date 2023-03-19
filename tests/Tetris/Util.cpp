#include "Util.hpp"

namespace util {
int getPieceWidth(const PieceTable& t) { return t.at(0).size(); }
int getPieceHeight(const PieceTable& t) { return t.size(); }
}