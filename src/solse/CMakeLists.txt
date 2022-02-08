set(
	sources
    # CommandLineInterface.cpp CommandLineInterface.h 
	mechanism.cpp mechanism.h  
	# SolidityExprTranslator.h
	SymExecEngine.cpp SolidityExprTranslator.cpp  SymExecEngine.h 
	main.cpp
	# mainTest.cpp
)

# add_library(faircon ${sources})
add_executable(faircon ${sources})
# target_include_directories(faircon PUBLIC "${CMAKE_SOURCE_DIR}")
target_include_directories(faircon SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
message("${Boost_PROGRAM_OPTIONS_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY}" )
if (SOLC_0_5_0)
	target_link_libraries(faircon PUBLIC solidity evmasm devcore ${Boost_FILESYSTEM_LIBRARIES} ${Boost_REGEX_LIBRARIES} ${Boost_SYSTEM_LIBRARIES} Threads::Threads fort jsoncpp)
	if (${Z3_FOUND})
	target_link_libraries(faircon PUBLIC Z3::Z3)
	endif()
endif ()
if (SOLC_0_5_10)
	target_link_libraries(faircon PUBLIC  solidity yul evmasm langutil devcore ${Boost_FILESYSTEM_LIBRARIES} ${Boost_REGEX_LIBRARIES} ${Boost_SYSTEM_LIBRARIES} Threads::Threads fort jsoncpp)
	if (${Z3_FOUND})
	target_link_libraries(faircon PUBLIC Z3::Z3)
	endif()
endif ()

include(GNUInstallDirs)
install(TARGETS faircon DESTINATION "${CMAKE_INSTALL_BINDIR}")
