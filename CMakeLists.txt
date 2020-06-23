cmake_minimum_required(VERSION 3.7)

project(poseidon VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

################################### TRIDENT ################################
include_directories(../trident/include/)
include_directories(../trident/build/kognac/include/)
include_directories(../trident/build/kognac/external/sparsehash/src)
################################### ARES ###################################
include_directories(../ares/include/)
file(GLOB ARES_SOURCES
    "../ares/src/formula/*.cpp"
        "../ares/src/formula/extended/*.cpp"
        "../ares/src/util/*.cpp"
        "../ares/src/rule/*.cpp"
        "../ares/src/rule/filter/*.cpp"
        "../ares/src/rule/math/*.cpp"
        "../ares/src/rule/math/evaluator/*.cpp"
        "../ares/src/core/*.cpp"
        "../ares/src/example/*.cpp"
        "../ares/src/service/*.cpp"
        )

find_package(Threads)

################################## POSEIDON ##################################
include_directories(include/)
file(GLOB POSEIDON_SOURCES
        "src/*.cpp"
    )

set(POSEIDON_ARES_SOURCES ${ARES_SOURCES} ${POSEIDON_SOURCES})
add_executable(poseidon main.cpp ${POSEIDON_ARES_SOURCES})
target_link_libraries(poseidon ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(poseidon ${CMAKE_SOURCE_DIR}/../trident/build/libtrident-sparql.so)
target_link_libraries(poseidon ${CMAKE_SOURCE_DIR}/../trident/build/libtrident-core.so)

