#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten.h>
#include <iostream>


class native_application
{
public:
    native_application()
    {
#ifdef __EMSCRIPTEN__
        std::cout << "ctor\n";
#endif
    }

    void update_div()
    {
        std::cout << "update_div\n";
        auto document = emscripten::val::global("document");
        auto testid = document.call<emscripten::val>("getElementById", std::string("testid"));
        testid.set("innerHTML", "Hello from web assembly!");
    }
};

EMSCRIPTEN_BINDINGS(EMTest) {
    emscripten::class_<native_application>("NativeApplication")
        .constructor()
        .function("UpdateDiv", &native_application::update_div);
}

int main()
{
    EM_ASM(
        webassembly_onload()
    );

    return 0;
}
