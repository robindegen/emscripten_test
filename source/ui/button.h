#pragma once

#include <ui/object.h>

namespace awf::ui
{

enum class button_style
{
    primary = 0,
    secondary,
    success,
    danger,
    warning,
    info,
    light,
    dark,
    link
};

class button : public object
{
public:
    button(std::string id, const button_style style = button_style::primary);
    ~button();

    button(const button &) noexcept = delete;
    auto operator=(const button &) noexcept -> button & = delete;

    button(button &&) noexcept = delete;
    auto operator=(button &&) noexcept -> button & = delete;

    void set_text(const std::string &text) noexcept;
};

} // namespace awf::ui
