set(BYTECODE_READER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/BytecodeReader.cpp
)

set(NM_TARGET_DEF_FILE "${CMAKE_BINARY_DIR}/nmTarget.def")

file(WRITE ${NM_TARGET_DEF_FILE}
  "// This file is compile-time generated\n"
)

foreach(fmt IN LISTS NM_TARGET)
  if (fmt STREQUAL "ELF")
    file(GLOB ELF_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/ELF*.cpp")
    list(APPEND BYTECODE_READER_SOURCES ${ELF_SRCS})
    file(APPEND ${NM_TARGET_DEF_FILE}
      "NM_TARGET(elf, elf::BytecodeReader)\n"
    )
  elseif (fmt STREQUAL "LLVM")
    file(GLOB LLVM_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/LLVM*.cpp")
    list(APPEND BYTECODE_READER_SOURCES ${LLVM_SRCS})
    file(APPEND ${NM_TARGET_DEF_FILE}
      "NM_TARGET(llvm, llvm::BytecodeReader)\n"
    )
  else()
    message(FATAL_ERROR "Unknown NM_TARGET format: '${fmt}'")
  endif()
endforeach()

file(APPEND ${NM_TARGET_DEF_FILE}
  "#undef NM_TARGET"
)

add_library(BytecodeReader STATIC)

target_sources(BytecodeReader
  PRIVATE
    ${BYTECODE_READER_SOURCES}
)

target_include_directories(BytecodeReader
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}   # so the .def file is findable
)

target_compile_features(BytecodeReader PUBLIC cxx_std_23)
