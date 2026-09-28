# Engine library: file formats + platform layer (game logic will be added as it is reconstructed)
add_library(dl2engine STATIC
    formats/hdx_archive.cpp
    formats/cam_package.cpp
    formats/palette.cpp
    formats/iff_pbm.cpp
    formats/wave.cpp
    formats/text_table.cpp
    platform/sdl_video.cpp
    platform/sdl_audio.cpp
    platform/sdl_input.cpp
    platform/timer.cpp
    engine/palette_table.cpp
    engine/offport.cpp
    engine/pixel.cpp
    engine/tile.cpp
    engine/imag.cpp
    engine/font.cpp
    engine/resources.cpp
    engine/input_queue.cpp
    engine/smenu.cpp
    engine/sound.cpp
    engine/cygame.cpp
)
target_include_directories(dl2engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dl2engine PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
if(MSVC)
    target_compile_options(dl2engine PUBLIC /W4 /utf-8)
    target_compile_definitions(dl2engine PUBLIC _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

add_subdirectory(sprites)
add_subdirectory(game)

add_library(dl2viewer STATIC app/inspector_session.cpp app/world_inspector.cpp app/inspector_main.cpp)
target_link_libraries(dl2viewer PUBLIC dl2engine dl2sprites dl2game)

# Read-only world inspector, plus the original resource demo via --demo.
add_executable(deadlock2 WIN32
    main.cpp
)
target_link_libraries(deadlock2 PRIVATE dl2viewer $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>)
if(NOT WIN32)
    set_target_properties(deadlock2 PROPERTIES WIN32_EXECUTABLE OFF)
endif()

if(DL2_BUILD_TOOLS)
    add_executable(dl2tool tools/dl2tool.cpp)
    target_link_libraries(dl2tool PRIVATE dl2engine dl2sprites)
    add_executable(dl2save tools/dl2save.cpp)
    target_link_libraries(dl2save PRIVATE dl2game)
    if(MSVC)
        target_compile_options(dl2save PRIVATE /W4 /utf-8)
    endif()
endif()
