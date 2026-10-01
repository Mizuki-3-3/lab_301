#pragma once
 
#include <iostream>
 
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
 
#define asser(expr) \
    if (!!(expr)) assert_success(#expr, __FILE__, __LINE__); \
    else assert_fail(#expr, __FILE__, __LINE__);
 
void int_success(void);
void int_fail(void);
 
int get_local_fail(void);
int get_local_success(void);
void reset_local_counts(void);
 
int assert_success(const char* expr, const char* file, unsigned int line);
int assert_fail(const char* expr, const char* file, unsigned int line);
 
void expected_true(const char* input, bool cond);

template <typename A, typename B>
void expect_eq_scalar(const char* input, A expected, B actual){
    std::cerr << __FILE__ << ":" << __LINE__ <<"\nInput: " << input << "\n";
    if (actual == expected){
        std::cerr << GREEN << " Expected: "<< expected
            << std::endl<<" Actual: "
            <<actual<< " [PASS]" << RESET << std::endl;
            int_success();
    }else{
        std::cerr << RED << " Expected: "<< expected
            << std::endl<<" Actual: "
            << actual << " [FAIL]" << RESET << std::endl;
            int_fail();
    }
}
 
