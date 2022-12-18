#pragma once
#include <ag/ui/Component.hpp>

namespace agui {
class TextField : public Component {
public:
    static inline constexpr int k_edgeThickness = 3;
    static inline constexpr int k_additionalSize = 9;
    static inline constexpr int k_blinkOnLength = 30;
    static inline constexpr int k_blinkOffLength = 10;
    explicit TextField();
    void profile() override;
    void update(const std::shared_ptr<ag::Renderer>& r) override;

protected:
    void processMouseEvent(const std::shared_ptr<MouseEvent>& e) override;
    void processKeyEvent(const std::shared_ptr<KeyEvent>& e) override;

private:
    bool m_focusOn;
    std::u16string m_text;
    int m_blinkOnWait;
    int m_blinkOffWait;
    int m_caretPosition;
};
}