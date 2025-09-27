# 包含头文件搜索路径（可选，但推荐）
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/block
    ${CMAKE_CURRENT_SOURCE_DIR}/factory
    ${CMAKE_CURRENT_SOURCE_DIR}/system
)

# 收集源文件
set(BLOCK_SOURCES
    block/CircleBlock.cpp
    block/SquareBlock.cpp
)

set(FACTORY_SOURCES
    factory/CircleBlockFactory.cpp
    factory/SquareBlockFactory.cpp
)

set(SYSTEM_SOURCES
    system/BlockFactorySystem.cpp
)

set(SOURCES
    main.cpp
    ${BLOCK_SOURCES}
    ${FACTORY_SOURCES}
    ${SYSTEM_SOURCES}
)

# 添加可执行文件
add_executable(factory_pattern_demo ${SOURCES})

add_executable(factory_registration_mechanism factory_registration_mechanism.cpp)
add_executable(factory_registration_macro factory_registration_macro.cpp)
