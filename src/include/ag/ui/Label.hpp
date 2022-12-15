#pragma once
#include <ag/ui/Component.hpp>
#include <string>

namespace agui {
class Label : public Component {
public:
    explicit Label(const std::u16string& text);
    void update(const std::shared_ptr<ag::Renderer>& r) override;

private:
    std::u16string m_text;
};
}