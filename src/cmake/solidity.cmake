include(ExternalProject)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(SOLIDITY_CMAKE_COMMAND emcmake cmake)
else()
    set(SOLIDITY_CMAKE_COMMAND ${CMAKE_COMMAND})
endif()

set(prefix "${CMAKE_BINARY_DIR}/deps")


# TODO: Investigate why this breaks some emscripten builds and
# check whether this can be removed after updating the emscripten
# versions used in the CI runs.
if(EMSCRIPTEN)
    # Do not include all flags in CMAKE_CXX_FLAGS for emscripten,
    # but only use -std=c++14. Using all flags causes build failures
    # at the moment.
    set(SOLIDITY_CXX_FLAGS -std=c++14)
else()
    set(SOLIDITY_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

set(byproducts "")

if (SOLC_0_5_0)
	set(Solidity_GIT_TAG v0.5.0)
elseif (SOLC_0_5_10)
    set(Solidity_GIT_TAG v0.5.10)
endif ()

ExternalProject_Add(solidity-project
    PREFIX "${prefix}"
    GIT_REPOSITORY https://github.com/ethereum/solidity.git
    GIT_TAG ${Solidity_GIT_TAG}
    CMAKE_COMMAND ${SOLIDITY_CMAKE_COMMAND}
    INSTALL_COMMAND ${SOLIDITY_CMAKE_COMMAND} -E echo "Skipping install step."
)

set(SOLIDITY_LIBRARY "${prefix}/src/solidity-project-build/libsolidity/${CMAKE_STATIC_LIBRARY_PREFIX}solidity${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(SOLIDITY_INCLUDE_DIR "${prefix}/src/solidity-project")
set(DEVCORE_LIBRARY "${prefix}/src/solidity-project-build/libdevcore/${CMAKE_STATIC_LIBRARY_PREFIX}devcore${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(EVMASM_LIBRARY "${prefix}/src/solidity-project-build/libevmasm/${CMAKE_STATIC_LIBRARY_PREFIX}evmasm${CMAKE_STATIC_LIBRARY_SUFFIX}")


file(MAKE_DIRECTORY ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)  # Must exist.

# Create jsoncpp imported library
add_library(solidity STATIC IMPORTED)
# file(MAKE_DIRECTORY ${SOLIDITY_INCLUDE_DIR})  # Must exist.
set_property(TARGET solidity PROPERTY IMPORTED_LOCATION ${SOLIDITY_LIBRARY})
set_property(TARGET solidity PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
set_property(TARGET solidity PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
add_dependencies(solidity solidity-project)


add_library(evmasm STATIC IMPORTED)
# file(MAKE_DIRECTORY ${SOLIDITY_INCLUDE_DIR})  # Must exist.
set_property(TARGET evmasm PROPERTY IMPORTED_LOCATION ${EVMASM_LIBRARY})
set_property(TARGET evmasm PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
set_property(TARGET evmasm PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
add_dependencies(evmasm solidity-project)

add_library(devcore STATIC IMPORTED)
set_property(TARGET devcore PROPERTY IMPORTED_LOCATION ${DEVCORE_LIBRARY})
set_property(TARGET devcore PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
set_property(TARGET devcore PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
add_dependencies(devcore solidity-project)


if (SOLC_0_5_10)
    set(LANGUTIL_LIBRARY "${prefix}/src/solidity-project-build/liblangutil/${CMAKE_STATIC_LIBRARY_PREFIX}langutil${CMAKE_STATIC_LIBRARY_SUFFIX}")
    add_library(langutil STATIC IMPORTED)
    set_property(TARGET langutil PROPERTY IMPORTED_LOCATION ${LANGUTIL_LIBRARY})
    set_property(TARGET langutil PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
    set_property(TARGET langutil PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
    add_dependencies(langutil solidity-project)

    set(YUL_LIBRARY "${prefix}/src/solidity-project-build/libyul/${CMAKE_STATIC_LIBRARY_PREFIX}yul${CMAKE_STATIC_LIBRARY_SUFFIX}")
    add_library(yul STATIC IMPORTED)
    set_property(TARGET yul PROPERTY IMPORTED_LOCATION ${YUL_LIBRARY})
    set_property(TARGET yul PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
    set_property(TARGET yul PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SOLIDITY_INCLUDE_DIR} ${prefix}/src/solidity-project-build/include ${prefix}/src/solidity-project-build/deps/include)
    add_dependencies(yul solidity-project)
endif ()

set(JSON_prefix "${prefix}/src/solidity-project-build/deps")
set(JSONCPP_LIBRARY "${JSON_prefix}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}jsoncpp${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(JSONCPP_INCLUDE_DIR "${JSON_prefix}/include")
add_library(jsoncpp STATIC IMPORTED)
file(MAKE_DIRECTORY ${JSONCPP_INCLUDE_DIR})  # Must exist.
set_property(TARGET jsoncpp PROPERTY IMPORTED_LOCATION ${JSONCPP_LIBRARY})
set_property(TARGET jsoncpp PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${JSONCPP_INCLUDE_DIR})
set_property(TARGET jsoncpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${JSONCPP_INCLUDE_DIR})
add_dependencies(jsoncpp jsoncpp-project)


