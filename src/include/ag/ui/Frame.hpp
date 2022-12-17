#pragma once
#include <ag/Window.hpp>
#include <ag/ui/BorderLayout.hpp>
#include <ag/ui/BorderLayoutParameter.hpp>
#include <ag/ui/Container.hpp>
#include <ag/ui/Panel.hpp>

namespace agui {
class Frame : public Container {
public:
    explicit Frame(const ag::Window::Instance& window);

private:
    ag::Window::Instance m_window;
};
}