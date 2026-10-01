#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"

TEST(uni_ptr_dereference_operators){
    uni_ptr<int> ptr(new int(10));
    expect_eq_scalar("operator* reads value", 10, *ptr);
    *ptr = 20;
    expect_eq_scalar("operator* allows write", 20, *ptr);
    expect_eq_scalar("operator-> reads value", 20, *ptr.operator->());
}

TEST(share_ptr_dereference_operators){
    share_ptr<int> ptr(new int(10));
    expect_eq_scalar("operator* reads value", 10, *ptr);
    *ptr = 20;
    expect_eq_scalar("operator* allows write", 20, *ptr);
    expect_eq_scalar("operator-> reads value", 20, *ptr.operator->());
}

TEST(share_ptr_dereference_visible_through_all_copies){
    share_ptr<int> a(new int(1));
    share_ptr<int> b(a);
    *a = 99;
    expect_eq_scalar("изменение через одну копию видно через другую", 99, *b);
}

TEST(uni_ptr_array_operator_index){
    auto ptr = uni_ptr<int[]>::make_unique(5);
    for (int i = 0; i < 5; ++i) { ptr[i] = i * i; }
    expect_eq_scalar("first element", 0, ptr[0]);
    expect_eq_scalar("last element", 16, ptr[4]);
}

TEST(share_ptr_array_operator_index){
    share_ptr<int[]> ptr(new int[5]{0, 1, 4, 9, 16});
    expect_eq_scalar("element at 2", 4, ptr[2]);
    ptr[2] = 100;
    expect_eq_scalar("write through operator[]", 100, ptr[2]);
    const share_ptr<int[]>& cref = ptr;
    expect_eq_scalar("const operator[] reads value", 100, cref[2]);
}

TEST(smart_base_operator_bool){
    uni_ptr<int> empty_ptr;
    uni_ptr<int> full_ptr(new int(1));
    expected_true("пустой указатель приводится к false", !static_cast<bool>(empty_ptr));
    expected_true("непустой указатель приводится к true", static_cast<bool>(full_ptr));
}

TEST(smart_base_operator_bool_after_release){
    uni_ptr<int> ptr(new int(1));
    ptr.release();
    expected_true("после release() указатель пуст", !static_cast<bool>(ptr));
}

TEST(smart_base_comparison_self_equal){
    uni_ptr<int> a(new int(1));
    expected_true("указатель равен самому себе", a == a);
    expected_true("указатель не меньше самого себя", !(a < a));
}

TEST(share_ptr_comparison_between_copies){
    share_ptr<int> a(new int(1));
    share_ptr<int> b(a);
    expected_true("копии share_ptr равны (указывают на один объект)", a == b);
    expected_true("копии не считаются неравными", !(a != b));
}

TEST(smart_base_comparison_different_objects){
    uni_ptr<int> a(new int(1));
    uni_ptr<int> b(new int(2));
    expected_true("разные объекты не равны", a != b);
    expected_true("ровно один из операторов < или > верен", (a < b) != (a > b));
}

TEST(smart_base_comparison_empty_pointers_equal){
    uni_ptr<int> a;
    uni_ptr<int> b;
    expected_true("два пустых указателя равны между собой", a == b);
}

TEST(smart_base_less_equal_greater_equal_consistency){
    uni_ptr<int> a(new int(1));
    uni_ptr<int> b(new int(2));
    expected_true("a <= b согласован с a < b или a == b", (a <= b) == (a < b || a == b));
    expected_true("a >= b согласован с a > b или a == b", (a >= b) == (a > b || a == b));
}
