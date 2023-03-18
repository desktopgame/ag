#pragma once
#include <memory>
#include <vector>

namespace ag {
class KeyCode;
using KeyTable = std::vector<KeyCode>;

class KeyCode {
private:
    static std::shared_ptr<KeyTable> s_table;

public:
    static const KeyCode unknown;
    static const KeyCode space;
    static const KeyCode apostrophe;
    static const KeyCode comma;
    static const KeyCode minus;
    static const KeyCode period;
    static const KeyCode slash;
    static const KeyCode number0;
    static const KeyCode number1;
    static const KeyCode number2;
    static const KeyCode number3;
    static const KeyCode number4;
    static const KeyCode number5;
    static const KeyCode number6;
    static const KeyCode number7;
    static const KeyCode number8;
    static const KeyCode number9;
    static const KeyCode semicolon;
    static const KeyCode equal;
    static const KeyCode a;
    static const KeyCode b;
    static const KeyCode c;
    static const KeyCode d;
    static const KeyCode e;
    static const KeyCode f;
    static const KeyCode g;
    static const KeyCode h;
    static const KeyCode i;
    static const KeyCode j;
    static const KeyCode k;
    static const KeyCode l;
    static const KeyCode m;
    static const KeyCode n;
    static const KeyCode o;
    static const KeyCode p;
    static const KeyCode q;
    static const KeyCode r;
    static const KeyCode s;
    static const KeyCode t;
    static const KeyCode u;
    static const KeyCode v;
    static const KeyCode w;
    static const KeyCode x;
    static const KeyCode y;
    static const KeyCode z;
    static const KeyCode leftBracket;
    static const KeyCode backSlash;
    static const KeyCode rightBracket;
    static const KeyCode graveAccent;
    static const KeyCode world1;
    static const KeyCode world2;
    static const KeyCode escape;
    static const KeyCode enter;
    static const KeyCode tab;
    static const KeyCode backspace;
    static const KeyCode insert;
    static const KeyCode delete_;
    static const KeyCode right;
    static const KeyCode left;
    static const KeyCode down;
    static const KeyCode up;
    static const KeyCode pageUp;
    static const KeyCode pageDown;
    static const KeyCode home;
    static const KeyCode end;
    static const KeyCode capsLock;
    static const KeyCode scrollLock;
    static const KeyCode numLock;
    static const KeyCode printScreen;
    static const KeyCode pause;
    static const KeyCode f1;
    static const KeyCode f2;
    static const KeyCode f3;
    static const KeyCode f4;
    static const KeyCode f5;
    static const KeyCode f6;
    static const KeyCode f7;
    static const KeyCode f8;
    static const KeyCode f9;
    static const KeyCode f10;
    static const KeyCode f11;
    static const KeyCode f12;
    static const KeyCode f13;
    static const KeyCode f14;
    static const KeyCode f15;
    static const KeyCode f16;
    static const KeyCode f17;
    static const KeyCode f18;
    static const KeyCode f19;
    static const KeyCode f20;
    static const KeyCode f21;
    static const KeyCode f22;
    static const KeyCode f23;
    static const KeyCode f24;
    static const KeyCode f25;
    static const KeyCode kp0;
    static const KeyCode kp1;
    static const KeyCode kp2;
    static const KeyCode kp3;
    static const KeyCode kp4;
    static const KeyCode kp5;
    static const KeyCode kp6;
    static const KeyCode kp7;
    static const KeyCode kp8;
    static const KeyCode kp9;
    static const KeyCode kpDecimal;
    static const KeyCode kpDivide;
    static const KeyCode kpMultiply;
    static const KeyCode kpSubtract;
    static const KeyCode kpAdd;
    static const KeyCode kpEnter;
    static const KeyCode kpEqual;
    static const KeyCode leftShift;
    static const KeyCode leftControl;
    static const KeyCode leftAlt;
    static const KeyCode leftSuper;
    static const KeyCode rightShift;
    static const KeyCode rightControl;
    static const KeyCode rightAlt;
    static const KeyCode rightSuper;
    static const KeyCode menu;
    static const KeyCode term;
    static const int maxKeyCodeValue;

    /**
     * create new key code, and add to global key table.
     * @param value
     */
    KeyCode(int value);
    /**
     * @return
     */
    int getValue() const;

    /**
     * returns the global key table.
     * @return
     */
    static KeyTable getKeys();

private:
    int m_value;
    static bool s_frozen;
};
}
