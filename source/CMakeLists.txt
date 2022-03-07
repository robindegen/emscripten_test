add_executable(client
    main.cpp
    ui/object.cpp
    ui/object.h
    ui/button.cpp
    ui/button.h
)

set_target_properties(client PROPERTIES LINK_FLAGS "-s WASM_BIGINT -s DEMANGLE_SUPPORT=1 --bind --profiling")

target_include_directories(client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
