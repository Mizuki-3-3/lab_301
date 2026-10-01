#pragma once
#include <chrono>
#include <ratio>
#include <stddef.h>
#include <iostream>

typedef void (*test_func)();

void register_test(const char* name, test_func test);
void run_test();
int print_stats();
void cleanup_tests();

typedef struct _test{
    const char* name;
    void (*test_func)(void);
    struct _test* next;
}_test;

#define TEST(test_name) \
    static void test_name##_test(); \
    static void test_name##_runner(){ \
        try{ \
        test_name##_test(); \
        }catch(...){ \
            std::cerr << "Exception caught in test: " << #test_name << std::endl; \
        } \
    } \
    static void __attribute__((constructor)) test_name##_init() { \
        register_test(#test_name, test_name##_runner); \
    } \
    static void test_name##_test()

#define TEST_ENTRY_POINT \
    int main(void) { \
        run_test(); \
        int result = print_stats(); \
        cleanup_tests(); \
        return result; \
    }