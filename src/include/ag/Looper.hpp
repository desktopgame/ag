#pragma once
#include <memory>
#include <vector>

namespace ag {
class Window;
class Looper {
public:
    explicit Looper();
    [[nodiscard]] std::shared_ptr<Window> acquire();
    void release();

    bool nextLoop();
    bool nextWindow();
    float deltaTime() const;

private:
    std::vector<std::shared_ptr<Window>> m_windows;
    std::shared_ptr<Window> m_cursor;
    bool m_use;
    int m_at;
    double m_timeNow;
    double m_timeLast;
};
}