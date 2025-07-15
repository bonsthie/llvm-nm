# i need to make better setup for this with build dependency and auto sub test but right now
# i have the crampte of doing cmake (deep inside me i think i prefer Makefile (i now that a
# skill issue because i don't now cmake)) might want to learn to do it in bazel insted

include(GoogleTest)

add_executable(llvmTest Reader/test_ByteReader.cpp)

target_link_libraries(llvmTest PRIVATE ByteReader GTest::gtest_main)
gtest_discover_tests(llvmTest)
