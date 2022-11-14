#pragma once
#include <memory>
#include <vector>

namespace ag {
class Window;
class Looper {
public:
    explicit Looper();
    void run();
    bool isRunnable() const;

private:
};
}