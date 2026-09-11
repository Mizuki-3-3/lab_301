#pragma once

#include <cstddef>

//control block в умных указателях
//виртуальный деструктор

typedef void (*test_func)();

void register_test(const char* name, test_func test);
void run_test();
int print_stats();
void cleanup_tests();

typedef struct _test{
    const char* name;
    void (*test_func)(void);
    struct _test* next;
}_testtest;

template <typename F>
F& get_fixture(){
    static F instance;
    return instance; 
}

#define TEST_F(test_obj, test_name) \
    static void test_name##_test(test_obj& _fix); \
    static void test_name##_runner(){ \
        test_obj& _fix = get_fixture<test_obj>(); \
        _fix.set_up(); \
        test_name##_test(_fix); \
        _fix.tear_down(); \
    } \
    static void __attribute__((constructor)) test_name##_init() { \
        register_test(#test_name, test_name##_runner); \
    } \
    static void test_name##_test(fixture_type& _fix)

#define TEST_ENTRY_POINT \
    int main(void) { \
        run_test(); \
        int result = print_stats(); \
        cleanup_tests(); \
        return result; \
    }

template <typename T>
class fixture{
    T* fixture_ptr;
    void set_up();
    void tear_down();
};