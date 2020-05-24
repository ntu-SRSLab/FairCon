set(
	sources
	CommandLineInterface.cpp CommandLineInterface.h
    mechanism.cpp mechanism.h  
	SolidityExprTranslator.cpp SolidityExprTranslator.h
	SymExecEngine.cpp SymExecEngine.h
	main.cpp
)

# add_executable(solse ${sources})
add_executable(faircon ${sources})
target_link_libraries(faircon PRIVATE solidity ${Boost_PROGRAM_OPTIONS_LIBRARIES} fort)

include(GNUInstallDirs)
install(TARGETS faircon DESTINATION "${CMAKE_INSTALL_BINDIR}")
