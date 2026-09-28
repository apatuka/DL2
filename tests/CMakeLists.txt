# The checks below stay active in Release/RelWithDebInfo (no C assert()).
add_executable(test_game test_game.cpp)
target_link_libraries(test_game PRIVATE dl2game)
add_test(NAME game_infrastructure COMMAND test_game)

add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine PRIVATE dl2engine)
add_test(NAME engine COMMAND test_engine)

add_executable(test_resources test_resources.cpp)
target_link_libraries(test_resources PRIVATE dl2engine)
add_test(NAME resources COMMAND test_resources "${DL2_DATA_DIR}")
set_tests_properties(resources PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 60)

find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
    foreach(_mode saves tables)
        add_test(NAME original_${_mode}
            COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_CURRENT_SOURCE_DIR}/test_game_data.py"
                ${_mode} "${DL2_DATA_DIR}")
        set_tests_properties(original_${_mode} PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 60)
    endforeach()
else()
    message(STATUS "Python3 not found: original saves/tables checks will not be registered")
endif()

if(EXISTS "${DL2_DATA_DIR}/deadcyb.cam" AND EXISTS "${DL2_DATA_DIR}/deadtext.cam")
    add_test(NAME application_smoke COMMAND deadlock2 "${DL2_DATA_DIR}" --smoke-frames 3)
    set_tests_properties(application_smoke PROPERTIES
        ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_AUDIODRIVER=dummy;SDL_RENDER_DRIVER=software"
        TIMEOUT 20)
endif()

# Keep SDL2 next to the test executables when using the dynamic Windows target.
if(WIN32 AND TARGET SDL2::SDL2)
    get_target_property(_dl2_sdl_type SDL2::SDL2 TYPE)
    if(_dl2_sdl_type STREQUAL "SHARED_LIBRARY")
        foreach(_target test_engine test_resources)
            add_custom_command(TARGET ${_target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:${_target}>)
        endforeach()
    endif()
endif()
