cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_VERSION "0.1.0")
project(FairCon VERSION ${PROJECT_VERSION} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(ETH_CMAKE_DIR   "${CMAKE_CURRENT_LIST_DIR}/cmake"   CACHE PATH "The the path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${ETH_CMAKE_DIR})

option(SOLC_0_5_0 "mount symbolic execution engine on solc==0.5.0" ON)
option(SOLC_0_5_10 "mount symbolic execution engine on solc==0.5.10" OFF)
option(SOLC_0_5_17 "mount symbolic execution engine on solc==0.5.17" OFF)

include(solidity)

include(EthToolchains)

# Set cmake_policies
include(EthPolicy)
eth_policy()

include(EthCompilerSettings)

# # Setup cccache.
include(EthCcache)

# # Let's find our dependencies
include(EthDependencies)

find_package(Threads)

# # Figure out what compiler and system are we using
include(EthCompilerSettings)

# # Include utils
include(EthUtils)


# configure_file("${CMAKE_SOURCE_DIR}/cmake/templates/license.h.in" include/license.h)
include(EthOptions)
# configure_project(TESTS)

# #add libfort to format text table
add_subdirectory(third-party/libfort)

find_package(Z3 4.6.0)
if (${Z3_FOUND})
  add_definitions(-DHAVE_Z3)
  message("Z3 SMT solver found. This enables optional SMT checking with Z3.")
  set(z3_SRCS formal/Z3Interface.cpp formal/Z3Interface.h)
else()
  set(z3_SRCS)
endif()

add_subdirectory(solse)

