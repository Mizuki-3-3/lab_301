#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"

template <typename T>
TEST_F(uni_ptr<int>, uni_ptr_copy_constructor){
    EXPECT_EQ_SCALAR("uni_ptr destructor test", "42", std::to_string(*ptr));
}