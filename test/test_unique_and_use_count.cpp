#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"

TEST(share_ptr_unique_and_use_count_simple){
    share_ptr<int> ptr(new int(5));
    expected_true("this ptr is unique", ptr.unique());
    expect_eq_scalar("use count should be 1", 1u, ptr.use_count());
}
TEST(share_ptr_unique_and_use_count_not_unique){
    share_ptr<int> ptr1(new int(5));
    share_ptr<int> ptr2(ptr1);
    expected_true("this ptr is not unique", !(ptr1.unique()));
    expect_eq_scalar("use count should be 2", 2u, ptr1.use_count());
}

TEST(share_ptr_unique_and_use_count_stress){
    share_ptr<int> ptr1(new int(9));
    share_ptr<int> cont[99];
    for (size_t i = 0; i < 99; ++i) {
        cont[i] = ptr1;
    }
    expected_true("this ptr is not unique", !(ptr1.unique()));
    expect_eq_scalar("use count should be 100", 100u, ptr1.use_count());
}