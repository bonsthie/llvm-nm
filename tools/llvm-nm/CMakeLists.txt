add_executable(llvm-nm nm.cpp)

target_link_libraries(llvm-nm
	PRIVATE
		BytecodeReader
)

target_include_directories(llvm-nm
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
)
