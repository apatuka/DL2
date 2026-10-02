# dl2game: lógica de juego reconstruida desde DEADLOCK.EXE (sin dependencias de SDL ni del motor gráfico).
# Cada agente/módulo añade sus .cpp a la lista GAME_SOURCES entre las marcas BEGIN/END (una línea por archivo).
set(GAME_SOURCES
    globals.cpp
    hooks.cpp
    rtl_compat.cpp
    # BEGIN MODULE SOURCES
    data_tables.cpp
    economy_tables.cpp
    supplemental_tables.cpp
    gameflow.cpp
    queue_pool.cpp
    queues.cpp
    save_document.cpp
    save_validation.cpp
    save_files.cpp
    world_view.cpp
    runtime_state.cpp
    tax_phase.cpp
    resource_needs.cpp
    production_plan.cpp
    labor_balance.cpp
    entity_rules.cpp
    load_profile.cpp
    load_derived.cpp
    session_rng.cpp
    load_intelligence.cpp
    entity_creation.cpp
    event_portraits.cpp
    load_session.cpp
    load_startup.cpp
    ai_session.cpp
    entity_lifecycle.cpp
    load_world_presentation.cpp
    construction_payment.cpp
    load_shrine_events.cpp
    construction_site.cpp
    building_progress.cpp
    unit_manufacturing.cpp
    territory_production.cpp
    economic_logistics.cpp
    economic_consumption.cpp
    building_costs.cpp
    economic_upkeep.cpp
    economic_prefix.cpp
    # END MODULE SOURCES
)

add_library(dl2game STATIC ${GAME_SOURCES})
target_include_directories(dl2game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_features(dl2game PUBLIC cxx_std_20)
if(MSVC)
    target_compile_options(dl2game PRIVATE /W4 /utf-8 /wd4100 /wd4201)
    target_compile_definitions(dl2game PUBLIC _CRT_SECURE_NO_WARNINGS NOMINMAX)
endif()

# Tests de la lógica (ejecutables de consola que cargan partidas reales y comprueban invariantes).
# BEGIN MODULE TESTS
# END MODULE TESTS
