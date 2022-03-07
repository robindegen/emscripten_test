#pragma once

#include <emscripten/val.h>
#include <string>
#include <cstdint>
#include <functional>

namespace awf::ui
{

using ui_object_id = std::uint32_t;

class object
{
public:
    object(std::string html_id);
    ~object();

    object(const object &) noexcept = delete;
    auto operator=(const object &) noexcept -> object & = delete;

    object(object &&) noexcept = delete;
    auto operator=(object &&) noexcept -> object & = delete;

    [[nodiscard]] auto html_id() const noexcept -> const std::string &;
    [[nodiscard]] auto element() const noexcept -> emscripten::val;

    void set_attribute(const std::string &attribute, const std::string &value) noexcept;

    virtual void on_click(const int timestamp) noexcept;
    void connect_on_click_event(std::function<void(int)> event) noexcept;

protected:
    void bind_onclick_event();

private:
    ui_object_id id_;
    std::string html_id_;
    emscripten::val element_;

    std::function<void(int)> on_click_handler_;
};

} // namespace awf::ui
