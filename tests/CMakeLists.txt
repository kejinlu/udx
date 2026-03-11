# Unity Test Framework
set(UNITY_SOURCES unity/unity.c)
set(UNITY_HEADERS unity/unity.h unity/unity_internals.h)

# Test sources
set(TEST_SOURCES
    test_fixture.c
    test_main.c
    test_writer.c
    test_reader.c
    test_chunk.c
    test_words.c
    test_utils.c
)

# Create test executable
add_executable(udx_tests
    ${UNITY_SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(udx_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/unity
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(udx_tests PRIVATE udx)

# Enable testing
add_test(NAME UnityTestSuite COMMAND udx_tests)
