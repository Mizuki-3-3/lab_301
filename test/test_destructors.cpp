#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"

template <typename T>
void destruction_after_construct_with_lambda_destructor(){}

template <typename T>
void destruction_after_construct_with_file_destructor(){}

TEST(uni_ptr_lambda_destructor_test){destruction_after_construct_with_file_destructor<uni_ptr<int>>();}
TEST(share_ptr_lambda_destructor_test){destruction_after_construct_with_file_destructor<share_ptr<int>>();}
TEST(uni_ptr_file_destructor_test){destruction_after_construct_with_file_destructor<uni_ptr<int>>();}
TEST(share_ptr_file_destructor_test){destruction_after_construct_with_file_destructor<share_ptr<int>>();}
