#include "uni_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"
#include <utility>

namespace {
struct point3d {
    int x, y, z;
    point3d(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};
}

TEST(uni_ptr_make_unique_scalar_value){
    uni_ptr<int> ptr = uni_ptr<int>::make_unique(42);
    expect_eq_scalar("make_unique(42) создаёт int со значением 42", 42, *ptr);
}

TEST(uni_ptr_make_unique_multi_arg_constructor){
    uni_ptr<point3d> ptr = uni_ptr<point3d>::make_unique(1, 2, 3);
    expect_eq_scalar("x", 1, ptr->x);
    expect_eq_scalar("y", 2, ptr->y);
    expect_eq_scalar("z", 3, ptr->z);
}

TEST(uni_ptr_make_unique_array_basic){
    auto ptr = uni_ptr<int[]>::make_unique(20);
    for (int i = 0; i < 20; ++i) { ptr[i] = i; }
    expect_eq_scalar("первый элемент", 0, ptr[0]);
    expect_eq_scalar("последний элемент (индекс 19)", 19, ptr[19]);
}

TEST(uni_ptr_make_unique_array_zero_size_does_not_crash){
    auto ptr = uni_ptr<int[]>::make_unique(0);
    expected_true("не упало на size == 0", true);
}

TEST(uni_ptr_make_unique_result_is_movable){
    uni_ptr<int> a = uni_ptr<int>::make_unique(5);
    uni_ptr<int> b = std::move(a);
    expect_eq_scalar("владение перешло", 5, *b);
    expect_eq_scalar("старый указатель пуст", nullptr, a.get());
}
