#include <ag/native/osx/NSView.hpp>
#include <ag/native/osx/NSWindow.hpp>

namespace NS {
Window* Window::bridgingCast(const void* ptr)
{
    return Object::bridgingCast<Window*>(ptr);
}
View* Window::contentView() const
{
    return Object::sendMessage<View*>(this, _NS_PRIVATE_SEL(contentView_));
}
} // namespace NS