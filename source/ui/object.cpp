#include "object.h"
#include <emscripten/bind.h>
#include <emscripten.h>
#include <cassert>
#include <iostream>
#include <map>

#include "button.h"

namespace awf::ui
{

ui_object_id last_available_id = 0u;
std::map<ui_object_id, object *> objects;

namespace internal
{

void internal_onclick_wrapper(emscripten::val e)
{
    auto self = e["target"]["self"];
    auto id = self.as<std::uint32_t>();

    auto result = objects.find(id);

    if (result == std::end(objects)) // Log a warning?
        return;

    auto timestamp = e["timeStamp"];
    result->second->on_click(timestamp.as<int>());
}

static const auto &document()
{
    static const auto d = emscripten::val::global("document");
    return d;
}

static auto get_element_by_id(const std::string &id)
{
    return document().call<emscripten::val>("getElementById", id);
}

} // namespace internal

object::object(std::string html_id)
    : id_{++last_available_id}
    , html_id_{std::move(html_id)}
    , element_{internal::get_element_by_id(html_id_)}
{
    assert(!element_.isUndefined());

    // Register globally and inject this into the self property
    objects[id_] = this;
    element_.set("self", id_);
}

object::~object()
{
    objects.erase(id_);
}

auto object::html_id() const noexcept -> const std::string &
{
    return html_id_;
}

auto object::element() const noexcept -> emscripten::val
{
    return element_;
}

void object::set_attribute(const std::string &attribute, const std::string &value) noexcept
{
    element_.call<void>("setAttribute", attribute, value);
}

void object::on_click(const int timestamp) noexcept
{
    if (on_click_handler_)
        on_click_handler_(timestamp);
}

void object::connect_on_click_event(std::function<void(int)> event) noexcept
{
    on_click_handler_ = std::move(event);
}

void object::bind_onclick_event()
{
    element_.call<void>("addEventListener", std::string("click"),
                        emscripten::val::module_property("internal_onclick_wrapper"));
}

} // namespace awf::ui

EMSCRIPTEN_BINDINGS(events)
{
    emscripten::function("internal_onclick_wrapper", &awf::ui::internal::internal_onclick_wrapper);
}
