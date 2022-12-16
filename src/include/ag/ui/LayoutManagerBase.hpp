#include <ag/ui/Component.hpp>
#include <ag/ui/ILayoutManager.hpp>
#include <ag/ui/LayoutParameter.hpp>
#include <unordered_map>

namespace agui {
class LayoutManagerBase : public ILayoutManager {
public:
    explicit LayoutManagerBase();
    void addLayoutComponent(const std::shared_ptr<Component>& c, const std::shared_ptr<LayoutParameter>& param) override;
    void removeLayoutComponent(const std::shared_ptr<Component>& c) override;

protected:
    std::unordered_map<Component::Instance, LayoutParameter::Instance> m_paramMap;
};
}