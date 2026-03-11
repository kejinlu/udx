//
//  test_utils.c
//  libudx tests
//
//  Utils module tests using Unity framework
//

#include "unity.h"
#include "udx_utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ============================================================
// String Folding Tests
// ============================================================

void test_fold_string_basic(void) {
    char* folded = udx_fold_string("Hello World");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("hello world", folded);
    free(folded);
}

void test_fold_string_all_upper(void) {
    char* folded = udx_fold_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("abcdefghijklmnopqrstuvwxyz", folded);
    free(folded);
}

void test_fold_string_all_lower(void) {
    char* folded = udx_fold_string("abcdefghijklmnopqrstuvwxyz");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("abcdefghijklmnopqrstuvwxyz", folded);
    free(folded);
}

void test_fold_string_mixed(void) {
    char* folded = udx_fold_string("HeLLo WoRLd");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("hello world", folded);
    free(folded);
}

void test_fold_string_empty(void) {
    char* folded = udx_fold_string("");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("", folded);
    free(folded);
}

void test_fold_string_null(void) {
    char* folded = udx_fold_string(NULL);
    TEST_ASSERT_NULL(folded);
}

void test_fold_string_with_numbers(void) {
    char* folded = udx_fold_string("Test123ABC456");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("test123abc456", folded);
    free(folded);
}

void test_fold_string_with_spaces(void) {
    char* folded = udx_fold_string("  Multiple   Spaces  ");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("  multiple   spaces  ", folded);
    free(folded);
}

void test_fold_string_with_punctuation(void) {
    char* folded = udx_fold_string("Hello, World! How are you?");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("hello, world! how are you?", folded);
    free(folded);
}

void test_fold_string_with_newlines(void) {
    char* folded = udx_fold_string("Line1\nLine2\nLine3");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("line1\nline2\nline3", folded);
    free(folded);
}

void test_fold_string_with_tabs(void) {
    char* folded = udx_fold_string("Column1\tColumn2\tColumn3");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("column1\tcolumn2\tcolumn3", folded);
    free(folded);
}

void test_fold_string_special_chars(void) {
    char* folded = udx_fold_string("!@#$%^&*()_+-={}[]|\\:;\"'<>?,./");
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING("!@#$%^&*()_+-={}[]|\\:;\"'<>?,./", folded);
    free(folded);
}

void test_fold_string_unicode_ascii(void) {
    // Test ASCII characters (0-127)
    char input[128];
    char expected[128];

    for (int i = 1; i < 128; i++) {
        input[i-1] = (char)i;
        expected[i-1] = (char)tolower((unsigned char)i);
    }
    input[127] = '\0';
    expected[127] = '\0';

    char* folded = udx_fold_string(input);
    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_EQUAL_STRING(expected, folded);
    free(folded);
}

void test_fold_string_single_char(void) {
    char* folded;

    folded = udx_fold_string("A");
    TEST_ASSERT_EQUAL_STRING("a", folded);
    free(folded);

    folded = udx_fold_string("Z");
    TEST_ASSERT_EQUAL_STRING("z", folded);
    free(folded);

    folded = udx_fold_string("a");
    TEST_ASSERT_EQUAL_STRING("a", folded);
    free(folded);

    folded = udx_fold_string("5");
    TEST_ASSERT_EQUAL_STRING("5", folded);
    free(folded);
}

void test_fold_string_returns_copy(void) {
    const char* original = "Original String";
    char* folded = udx_fold_string(original);

    TEST_ASSERT_NOT_NULL(folded);
    TEST_ASSERT_NOT_EQUAL(original, folded);  // Should be different pointer

    // Modifying folded should not affect original
    folded[0] = 'X';
    TEST_ASSERT_EQUAL_STRING("Original String", original);

    free(folded);
}

void test_fold_string_preserves_length(void) {
    const char* test_strings[] = {
        "A",
        "AB",
        "ABC",
        "A Very Long String With Many Words That Should Preserve Its Length",
        "1234567890"
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        size_t original_len = strlen(test_strings[i]);
        char* folded = udx_fold_string(test_strings[i]);
        TEST_ASSERT_NOT_NULL(folded);
        TEST_ASSERT_EQUAL_UINT32(original_len, strlen(folded));
        free(folded);
    }
}

void test_fold_string_allocation(void) {
    char* folded = udx_fold_string("Test");
    TEST_ASSERT_NOT_NULL(folded);

    // Verify we can modify it
    strcpy(folded, "Modified");
    TEST_ASSERT_EQUAL_STRING("Modified", folded);

    free(folded);
}

void test_fold_string_repeated_calls(void) {
    char* folded1 = udx_fold_string("First");
    char* folded2 = udx_fold_string("SECOND");
    char* folded3 = udx_fold_string("ThIrD");

    TEST_ASSERT_EQUAL_STRING("first", folded1);
    TEST_ASSERT_EQUAL_STRING("second", folded2);
    TEST_ASSERT_EQUAL_STRING("third", folded3);

    // Verify they are independent
    folded1[0] = 'X';
    TEST_ASSERT_EQUAL_STRING("second", folded2);
    TEST_ASSERT_EQUAL_STRING("third", folded3);

    free(folded1);
    free(folded2);
    free(folded3);
}

// ============================================================
// Test Suite Runner
// ============================================================

void run_utils_tests(void) {
    printf("\n");
    printf("========================================\n");
    printf("  Utils Tests\n");
    printf("========================================\n");

    RUN_TEST(test_fold_string_basic);
    RUN_TEST(test_fold_string_all_upper);
    RUN_TEST(test_fold_string_all_lower);
    RUN_TEST(test_fold_string_mixed);

    RUN_TEST(test_fold_string_empty);
    RUN_TEST(test_fold_string_null);

    RUN_TEST(test_fold_string_with_numbers);
    RUN_TEST(test_fold_string_with_spaces);
    RUN_TEST(test_fold_string_with_punctuation);
    RUN_TEST(test_fold_string_with_newlines);
    RUN_TEST(test_fold_string_with_tabs);
    RUN_TEST(test_fold_string_special_chars);

    RUN_TEST(test_fold_string_unicode_ascii);
    RUN_TEST(test_fold_string_single_char);
    RUN_TEST(test_fold_string_returns_copy);
    RUN_TEST(test_fold_string_preserves_length);
    RUN_TEST(test_fold_string_allocation);
    RUN_TEST(test_fold_string_repeated_calls);
}
