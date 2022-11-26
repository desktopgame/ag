// include all implementations.
#include <ag/native/osx/MetalOne.hpp>
// expand all macro.
#include <ag/native/osx/CAMetalLayer.hpp>
#include <ag/native/osx/NSView.hpp>
#include <ag/native/osx/NSWindow.hpp>

#ifdef AG_METAL
namespace CA {
// CAMetalLayer
MetalLayer* MetalLayer::alloc()
{
    return NS::Object::alloc<MetalLayer>(_CA_PRIVATE_CLS(CAMetalLayer));
}

MetalLayer* MetalLayer::init() { return NS::Object::init<MetalLayer>(); }
void MetalLayer::setDevice(const MTL::Device* device)
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setDevice_), device);
}
void MetalLayer::setOpaque(bool yes)
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setOpaque_), yes);
}
CA::MetalDrawable* MetalLayer::nextDrawable()
{
    return Object::sendMessage<CA::MetalDrawable*>(
        this, _CA_PRIVATE_SEL(nextDrawable_));
}
} // namespace CA

namespace NS {
// NSView
void View::setLayer(const CA::MetalLayer* layer)
{
    Object::sendMessage<void>(this, _NS_PRIVATE_SEL(setLayer_), layer);
}
void View::setWantsLayer(bool yes)
{
    Object::sendMessage<void>(this, _NS_PRIVATE_SEL(setWantsLayer_), yes);
}
// NSWindow
Window* Window::bridgingCast(const void* ptr)
{
    return Object::bridgingCast<Window*>(ptr);
}
View* Window::contentView() const
{
    return Object::sendMessage<View*>(this, _NS_PRIVATE_SEL(contentView_));
}
} // namespace NS
#endif