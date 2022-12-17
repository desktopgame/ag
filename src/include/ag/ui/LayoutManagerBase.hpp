#pragma once
#include <ag/ui/Component.hpp>
#include <ag/ui/ILayoutManager.hpp>
#include <ag/ui/LayoutElement.hpp>
#include <ag/ui/LayoutParameter.hpp>
#include <unordered_map>

namespace agui {
class LayoutManagerBase : public ILayoutManager {
public:
    explicit LayoutManagerBase();
    void addLayoutComponent(const std::shared_ptr<Component>& c, const std::shared_ptr<LayoutParameter>& param) override;
    void removeLayoutComponent(const std::shared_ptr<Component>& c) override;

protected:
    template <typename T>
    inline std::shared_ptr<T> getParameter(int i) const
    {
        return std::static_pointer_cast<T>(m_elements.at(i).param);
    }

    Component::Instance getComponent(int i) const;
    int getElementCount() const;

private:
    std::vector<LayoutElement> m_elements;
};
}