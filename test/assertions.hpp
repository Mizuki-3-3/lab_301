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

int assert_success(const char* expr, const char* file, unsigned int line);
int assert_fail(const char* expr, const char* file, unsigned int line);

void expected_true(const char* input, bool cond);

template <typename A, typename B>
void expect_eq_scalar(const char* input, A expected, B actual);
