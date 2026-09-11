#pragma once

#include <iostream>
#include <string>

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

#define EXPECT_EQ_SCALAR( input, expected, actual) \
    do{ \
        std::string _inp = (input); \
        std::string _exp = (expected); \
        std::string _act = (actual); \
        std::cerr << __FILE__ << ":" << __LINE__ <<"\nInput: " << _inp << "\n"; \
        if (_act == _exp){ \
            std::cerr << GREEN << " Expected: "<< _exp \
            << std::endl<<" Actual: " \
            <<_act<< " [PASS]" << RESET << std::endl; \
            int_success(); \
        }else{ \
            std::cerr << RED << " Expected: "<< _exp \
            << std::endl<<" Actual: " \
            <<_act<< " [FAIL]" << RESET << std::endl; \
            int_fail(); \
        } \
    } while(0); \

#define EXPECTED_TRUE(input, cond) \
    do{ \
        std::string _inp = (input); \
        std::cerr << __FILE__ << ":" << __LINE__ <<"\nInput: " << _inp << "\n"; \
        if (cond){ \
            std::cerr << GREEN << "[PASS]" << RESET << "\n"; \
            int_success(); \
        }else{ \
            std::cerr << RED << "[FAIL]" << RESET << "\n"; \
            int_fail(); \
        } \
    } while(0); \