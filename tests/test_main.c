//
//  test_main.c
//  libudx tests
//
//  Unity-based test runner for libudx
//

#include "unity.h"
#include <stdio.h>

// 测试套件声明
void run_writer_tests(void);
void run_reader_tests(void);
void run_chunk_tests(void);
void run_words_tests(void);
void run_utils_tests(void);

int main(void) {
    printf("\n");
    printf("========================================\n");
    printf("  libudx Test Suite (Unity Framework)\n");
    printf("========================================\n\n");

    // 运行所有测试套件
    run_writer_tests();
    run_reader_tests();
    run_chunk_tests();
    run_words_tests();
    run_utils_tests();

    // 打印汇总
    printf("\n");
    printf("========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");

    return UnityEnd();
}
