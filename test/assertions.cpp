#include "assertions.hpp"
#include "test.hpp"
#include <iostream>

static unsigned short int success_count = 0;
static unsigned short int fail_count = 0;
static unsigned short int success_count_local = 0;
static unsigned short int fail_count_local = 0;

static _test* head = nullptr;
static _test* tail = nullptr;

void register_test(const char* name, test_func test){
    _test* tmp = new _test;
    if (!tmp){
        std::cout<<"Memory allocation failed\n";
        return;
    }
    tmp->name = name;
    tmp->test_func = test;
    tmp->next = nullptr;
    if (!head && !tail){
        head = tail = tmp;
        return;
    }
    tail->next = tmp;
    tail = tmp;
}

void int_success(void){success_count++; success_count_local++;}
void int_fail(void){fail_count++; fail_count_local++;}

int get_local_fail(void){return fail_count_local;}
int get_local_success(void){return success_count_local;}

void reset_local_counts(){success_count_local = 0; fail_count_local = 0;}

int assert_success(const char* expr, const char* file, unsigned int line){
    std::cerr << GREEN << "[PASS] " << RESET << expr << " in " << file << ":" << line << "\n";
    return 0;
}

int assert_fail(const char* expr, const char* file, unsigned int line){
    std::cerr << RED << "[FAIL] " << RESET << expr << " in " << file << ":" << line << "\n";
    return 1;
}

void run_test() {
    _test* current = head;
    while (current != NULL) {
        fprintf(stderr, "\nRunning test: %s\n", current->name);
        success_count_local = 0;
        fail_count_local = 0;
        
        if (current->test_func != NULL) {
            current->test_func();
        }
        current = current->next;
    }
}

int print_stats(){
    int total = fail_count + success_count;
    if (total == 0) {
        std::cerr<<"No tests run\n";
        return 0;
    }
    float percentage = (float)success_count / (float)total * 100.0f;
    fprintf(stderr, "\n%d of %d tests passed. %.2f%% SUCCEEDED\n",
            success_count,
            total,
            percentage);
    return success_count == 0 ? 1 : 0;
}

void cleanup_tests(){
    _test* current = head;
    while (current){
        _test* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

template <typename T>
void fixture<T>::set_up(){
    fix_ptr = new T();
}

template <typename T>
void fixture<T>::tear_down(){
    delete fix_ptr;
    fix_ptr = nullptr;
}