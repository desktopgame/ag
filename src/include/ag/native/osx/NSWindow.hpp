#pragma once
#include <ag/native/osx/MetalOne.hpp>

namespace NS::Private::Class {
_NS_PRIVATE_DEF_CLS(NSWindow);
} // namespace NS::Private::Class

namespace NS::Private::Selector {
_NS_PRIVATE_DEF_SEL(contentView_, "contentView");
} // namespace NS::Private::Selector

namespace NS {
class View;
class Window : public Referencing<Window> {
public:
    static Window* bridgingCast(const void* ptr);
    class View* contentView() const;
};
} // namespace NS