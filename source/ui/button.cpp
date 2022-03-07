#include "button.h"
#include <iostream>

namespace awf::ui
{

namespace internal
{

constexpr static char const *button_style_lookup[9] = {"btn btn-primary", "btn btn-secondary", "btn btn-success",
                                                       "btn btn-danger",  "btn btn-warning",   "btn btn-info",
                                                       "btn btn-light",   "btn btn-dark",      "btn btn-link"};

}

button::button(std::string id, const button_style style)
    : object{std::move(id)}
{
    set_attribute("type", "button");
    set_attribute("class", internal::button_style_lookup[(int)style]);

    bind_onclick_event();
}

button::~button() = default;

void button::set_text(const std::string &text) noexcept
{
    element().set("innerHTML", text);
}

} // namespace awf::ui
