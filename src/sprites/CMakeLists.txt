# Sprite layer: SPRITENW.DAT tables (generated from DEADLOCK.EXE), palette, blitting and the ANIM system.
add_library(dl2sprites STATIC
    sprite_tables.cpp
    sprite_palette.cpp
    sprite_bank.cpp
    sprite_draw.cpp
    anim.cpp
)
target_include_directories(dl2sprites PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(dl2sprites PUBLIC dl2engine)
