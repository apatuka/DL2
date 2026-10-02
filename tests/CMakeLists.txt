# The checks below stay active in Release/RelWithDebInfo (no C assert()).
add_executable(test_game test_game.cpp)
target_link_libraries(test_game PRIVATE dl2game)
add_test(NAME game_infrastructure COMMAND test_game)

add_executable(test_save_document test_save_document.cpp)
target_link_libraries(test_save_document PRIVATE dl2game)
add_test(NAME save_document COMMAND test_save_document)
set_tests_properties(save_document PROPERTIES TIMEOUT 60)

add_executable(test_save_files test_save_files.cpp)
target_link_libraries(test_save_files PRIVATE dl2game)
add_test(NAME save_files COMMAND test_save_files "${CMAKE_CURRENT_BINARY_DIR}")
set_tests_properties(save_files PROPERTIES TIMEOUT 30)

add_executable(test_world_view test_world_view.cpp)
target_link_libraries(test_world_view PRIVATE dl2game)
add_test(NAME world_view COMMAND test_world_view)

add_executable(test_tax_phase test_tax_phase.cpp)
target_link_libraries(test_tax_phase PRIVATE dl2game)
add_test(NAME tax_phase COMMAND test_tax_phase)

add_executable(test_resource_needs test_resource_needs.cpp)
target_link_libraries(test_resource_needs PRIVATE dl2game)
add_test(NAME resource_needs COMMAND test_resource_needs "${DL2_DATA_DIR}")
set_tests_properties(resource_needs PROPERTIES TIMEOUT 60)

add_executable(test_production_plan test_production_plan.cpp)
target_link_libraries(test_production_plan PRIVATE dl2game dl2engine)
add_test(NAME production_plan COMMAND test_production_plan "${DL2_DATA_DIR}")
set_tests_properties(production_plan PROPERTIES TIMEOUT 60)

add_executable(test_runtime_state test_runtime_state.cpp)
target_link_libraries(test_runtime_state PRIVATE dl2game)
add_test(NAME runtime_state COMMAND test_runtime_state "${DL2_DATA_DIR}")
set_tests_properties(runtime_state PROPERTIES TIMEOUT 60)

add_executable(test_labor_balance test_labor_balance.cpp)
target_link_libraries(test_labor_balance PRIVATE dl2game dl2engine)
add_test(NAME labor_balance COMMAND test_labor_balance "${DL2_DATA_DIR}")
set_tests_properties(labor_balance PROPERTIES TIMEOUT 60)

add_executable(test_runtime_entities test_runtime_entities.cpp)
target_link_libraries(test_runtime_entities PRIVATE dl2game dl2engine)
add_test(NAME runtime_entities COMMAND test_runtime_entities "${DL2_DATA_DIR}")
set_tests_properties(runtime_entities PROPERTIES TIMEOUT 60)

add_executable(test_entity_rules test_entity_rules.cpp)
target_link_libraries(test_entity_rules PRIVATE dl2game dl2engine)
add_test(NAME entity_rules COMMAND test_entity_rules "${DL2_DATA_DIR}")
set_tests_properties(entity_rules PROPERTIES TIMEOUT 60)

foreach(_module session_rng load_derived load_profile table_contracts runtime_load load_intelligence entity_creation load_session ai_session entity_lifecycle load_world_presentation construction_payment load_shrine_events construction_order construction_site building_progress unit_manufacturing manufacturing_runtime territory_production economic_logistics economic_consumption building_costs economic_upkeep economic_prefix population_growth colony_morale research_phase colony_unrest economic_phase)
    add_executable(test_${_module} test_${_module}.cpp)
    target_link_libraries(test_${_module} PRIVATE dl2game dl2engine)
    add_test(NAME ${_module} COMMAND test_${_module} "${DL2_DATA_DIR}")
    set_tests_properties(${_module} PROPERTIES TIMEOUT 60)
endforeach()

add_executable(test_inspector_session test_inspector_session.cpp)
target_link_libraries(test_inspector_session PRIVATE dl2viewer)
add_test(NAME inspector_session COMMAND test_inspector_session "${CMAKE_CURRENT_BINARY_DIR}")
set_tests_properties(inspector_session PROPERTIES TIMEOUT 30)

add_executable(test_input test_input.cpp)
target_link_libraries(test_input PRIVATE dl2engine)
add_test(NAME input COMMAND test_input)

add_executable(test_world_inspector test_world_inspector.cpp)
target_link_libraries(test_world_inspector PRIVATE dl2viewer)
add_test(NAME world_inspector COMMAND test_world_inspector "${DL2_DATA_DIR}")
set_tests_properties(world_inspector PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 60)

add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine PRIVATE dl2engine)
add_test(NAME engine COMMAND test_engine)

add_executable(test_resources test_resources.cpp)
target_link_libraries(test_resources PRIVATE dl2engine)
add_test(NAME resources COMMAND test_resources "${DL2_DATA_DIR}")
set_tests_properties(resources PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 60)

find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
    if(TARGET dl2sim)
        add_test(NAME simulation_cli COMMAND "${Python3_EXECUTABLE}" -B
            "${CMAKE_CURRENT_SOURCE_DIR}/test_sim_cli.py" $<TARGET_FILE:dl2sim>
            "${DL2_DATA_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
        set_tests_properties(simulation_cli PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 60)
    endif()
    if(TARGET dl2save)
        add_test(NAME save_corpus COMMAND "${Python3_EXECUTABLE}" -B
            "${CMAKE_CURRENT_SOURCE_DIR}/test_save_corpus.py" $<TARGET_FILE:dl2save>
            "${DL2_DATA_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
        set_tests_properties(save_corpus PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 180)
    endif()
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
    add_test(NAME application_smoke COMMAND deadlock2 "${DL2_DATA_DIR}" --demo --smoke-frames 3)
    set_tests_properties(application_smoke PROPERTIES
        ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_AUDIODRIVER=dummy;SDL_RENDER_DRIVER=software"
        TIMEOUT 20)
endif()
if(EXISTS "${DL2_DATA_DIR}/deadtext.cam" AND EXISTS "${DL2_DATA_DIR}/SPRITENW.DAT")
    if(EXISTS "${DL2_DATA_DIR}/TUTORIAL.SAV")
        add_test(NAME inspector_smoke COMMAND deadlock2 "${DL2_DATA_DIR}" --smoke-frames 3)
        set_tests_properties(inspector_smoke PROPERTIES
            ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_RENDER_DRIVER=software" TIMEOUT 20)
    endif()
    if(EXISTS "${DL2_DATA_DIR}/LEVELS.HDX" AND EXISTS "${DL2_DATA_DIR}/LEVELS.HDD")
        add_test(NAME inspector_scenario_smoke COMMAND deadlock2 "${DL2_DATA_DIR}" --scenario CHCHT1 --smoke-frames 3)
        set_tests_properties(inspector_scenario_smoke PROPERTIES
            ENVIRONMENT "SDL_VIDEODRIVER=dummy;SDL_RENDER_DRIVER=software" TIMEOUT 20)
    endif()
endif()

# Keep SDL2 next to the test executables when using the dynamic Windows target.
if(WIN32 AND TARGET SDL2::SDL2)
    get_target_property(_dl2_sdl_type SDL2::SDL2 TYPE)
    if(_dl2_sdl_type STREQUAL "SHARED_LIBRARY")
        foreach(_target test_engine test_resources test_input test_inspector_session test_world_inspector test_production_plan test_labor_balance test_runtime_entities test_entity_rules test_session_rng test_load_derived test_load_profile test_table_contracts test_runtime_load test_load_intelligence test_entity_creation test_load_session test_ai_session test_entity_lifecycle test_load_world_presentation test_construction_payment test_load_shrine_events test_construction_order test_construction_site test_building_progress test_unit_manufacturing test_manufacturing_runtime test_territory_production test_economic_logistics test_economic_consumption test_building_costs test_economic_upkeep test_economic_prefix test_population_growth test_colony_morale test_research_phase test_colony_unrest test_economic_phase)
            add_custom_command(TARGET ${_target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:${_target}>)
        endforeach()
    endif()
endif()
