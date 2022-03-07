#include <ui/button.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/bind.h>
#include <iostream>

class application
{
public:
    application()
        : primary_button_{"testbtn", awf::ui::button_style::success}
    {
        primary_button_.set_text("Test Button");
        primary_button_.connect_on_click_event([this](int timestamp) { testbtn_onclick(timestamp); });
    }

    ~application()
    {
    }

    void testbtn_onclick(const int timestamp)
    {
        std::cout << "Test button clicked at " << timestamp << '\n';
    }

private:
    awf::ui::button primary_button_;
};

EMSCRIPTEN_BINDINGS(EMTest)
{
    emscripten::class_<application>("Application").constructor();
}

int main()
{
    EM_ASM(webassembly_onload());

    return 0;
}
