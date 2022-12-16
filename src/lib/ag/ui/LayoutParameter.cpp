#include <ag/ui/LayoutParameter.hpp>

namespace agui {
LayoutParameter::Instance LayoutParameter::empty()
{
    return std::make_shared<LayoutParameter>();
}
}