#pragma once
#include <ag/ui/Component.hpp>
#include <ag/ui/Label.hpp>
#include <string>

namespace agui {
class Button : public Component {
public:
    explicit Button(const std::u16string& text);
    void profile() override;
    void update(const std::shared_ptr<ag::Renderer>& r) override;

private:
    std::shared_ptr<Label> m_label;
};
}