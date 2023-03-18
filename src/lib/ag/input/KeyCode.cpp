#include <ag/input/KeyCode.hpp>

namespace ag {
std::shared_ptr<KeyTable> KeyCode::s_table;
const KeyCode KeyCode::unknown = -1;
const KeyCode KeyCode::space = 32;
const KeyCode KeyCode::apostrophe = 39 /* ' */;
const KeyCode KeyCode::comma = 44 /* , */;
const KeyCode KeyCode::minus = 45 /* - */;
const KeyCode KeyCode::period = 46 /* . */;
const KeyCode KeyCode::slash = 47 /* / */;
const KeyCode KeyCode::number0 = 48;
const KeyCode KeyCode::number1 = 49;
const KeyCode KeyCode::number2 = 50;
const KeyCode KeyCode::number3 = 51;
const KeyCode KeyCode::number4 = 52;
const KeyCode KeyCode::number5 = 53;
const KeyCode KeyCode::number6 = 54;
const KeyCode KeyCode::number7 = 55;
const KeyCode KeyCode::number8 = 56;
const KeyCode KeyCode::number9 = 57;
const KeyCode KeyCode::semicolon = 59 /* ; */;
const KeyCode KeyCode::equal = 61 /* = */;
const KeyCode KeyCode::a = 65;
const KeyCode KeyCode::b = 66;
const KeyCode KeyCode::c = 67;
const KeyCode KeyCode::d = 68;
const KeyCode KeyCode::e = 69;
const KeyCode KeyCode::f = 70;
const KeyCode KeyCode::g = 71;
const KeyCode KeyCode::h = 72;
const KeyCode KeyCode::i = 73;
const KeyCode KeyCode::j = 74;
const KeyCode KeyCode::k = 75;
const KeyCode KeyCode::l = 76;
const KeyCode KeyCode::m = 77;
const KeyCode KeyCode::n = 78;
const KeyCode KeyCode::o = 79;
const KeyCode KeyCode::p = 80;
const KeyCode KeyCode::q = 81;
const KeyCode KeyCode::r = 82;
const KeyCode KeyCode::s = 83;
const KeyCode KeyCode::t = 84;
const KeyCode KeyCode::u = 85;
const KeyCode KeyCode::v = 86;
const KeyCode KeyCode::w = 87;
const KeyCode KeyCode::x = 88;
const KeyCode KeyCode::y = 89;
const KeyCode KeyCode::z = 90;
const KeyCode KeyCode::leftBracket = 91 /* [ */;
const KeyCode KeyCode::backSlash = 92 /* \ */;
const KeyCode KeyCode::rightBracket = 93 /* ] */;
const KeyCode KeyCode::graveAccent = 96 /* ` */;
const KeyCode KeyCode::world1 = 161 /* non-US #1 */;
const KeyCode KeyCode::world2 = 162 /* non-US #2 */;
const KeyCode KeyCode::escape = 256;
const KeyCode KeyCode::enter = 257;
const KeyCode KeyCode::tab = 258;
const KeyCode KeyCode::backspace = 259;
const KeyCode KeyCode::insert = 260;
const KeyCode KeyCode::delete_ = 261;
const KeyCode KeyCode::right = 262;
const KeyCode KeyCode::left = 263;
const KeyCode KeyCode::down = 264;
const KeyCode KeyCode::up = 265;
const KeyCode KeyCode::pageUp = 266;
const KeyCode KeyCode::pageDown = 267;
const KeyCode KeyCode::home = 268;
const KeyCode KeyCode::end = 269;
const KeyCode KeyCode::capsLock = 280;
const KeyCode KeyCode::scrollLock = 281;
const KeyCode KeyCode::numLock = 282;
const KeyCode KeyCode::printScreen = 283;
const KeyCode KeyCode::pause = 284;
const KeyCode KeyCode::f1 = 290;
const KeyCode KeyCode::f2 = 291;
const KeyCode KeyCode::f3 = 292;
const KeyCode KeyCode::f4 = 293;
const KeyCode KeyCode::f5 = 294;
const KeyCode KeyCode::f6 = 295;
const KeyCode KeyCode::f7 = 296;
const KeyCode KeyCode::f8 = 297;
const KeyCode KeyCode::f9 = 298;
const KeyCode KeyCode::f10 = 299;
const KeyCode KeyCode::f11 = 300;
const KeyCode KeyCode::f12 = 301;
const KeyCode KeyCode::f13 = 302;
const KeyCode KeyCode::f14 = 303;
const KeyCode KeyCode::f15 = 304;
const KeyCode KeyCode::f16 = 305;
const KeyCode KeyCode::f17 = 306;
const KeyCode KeyCode::f18 = 307;
const KeyCode KeyCode::f19 = 308;
const KeyCode KeyCode::f20 = 309;
const KeyCode KeyCode::f21 = 310;
const KeyCode KeyCode::f22 = 311;
const KeyCode KeyCode::f23 = 312;
const KeyCode KeyCode::f24 = 313;
const KeyCode KeyCode::f25 = 314;
const KeyCode KeyCode::kp0 = 320;
const KeyCode KeyCode::kp1 = 321;
const KeyCode KeyCode::kp2 = 322;
const KeyCode KeyCode::kp3 = 323;
const KeyCode KeyCode::kp4 = 324;
const KeyCode KeyCode::kp5 = 325;
const KeyCode KeyCode::kp6 = 326;
const KeyCode KeyCode::kp7 = 327;
const KeyCode KeyCode::kp8 = 328;
const KeyCode KeyCode::kp9 = 329;
const KeyCode KeyCode::kpDecimal = 330;
const KeyCode KeyCode::kpDivide = 331;
const KeyCode KeyCode::kpMultiply = 332;
const KeyCode KeyCode::kpSubtract = 333;
const KeyCode KeyCode::kpAdd = 334;
const KeyCode KeyCode::kpEnter = 335;
const KeyCode KeyCode::kpEqual = 336;
const KeyCode KeyCode::leftShift = 340;
const KeyCode KeyCode::leftControl = 341;
const KeyCode KeyCode::leftAlt = 342;
const KeyCode KeyCode::leftSuper = 343;
const KeyCode KeyCode::rightShift = 344;
const KeyCode KeyCode::rightControl = 345;
const KeyCode KeyCode::rightAlt = 346;
const KeyCode KeyCode::rightSuper = 347;
const KeyCode KeyCode::menu = 348;
const KeyCode KeyCode::term = 999;
const int KeyCode::maxKeyCodeValue = 512;
bool KeyCode::s_frozen = false;

KeyCode::KeyCode(int value)
    : m_value(value)
{
    if (!s_table) {
        s_table = std::make_shared<KeyTable>();
    }
    if (!s_frozen) {
        s_table->emplace_back(*this);
    }
    if (value == 999) {
        s_frozen = true;
    }
}
int KeyCode::getValue() const
{
    return m_value;
}
KeyTable KeyCode::getKeys()
{
    return *s_table;
}
}
