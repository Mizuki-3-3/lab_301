#include "share_ptr.hpp"
#include "uni_ptr.hpp"
#include "assertions.hpp"
#include "test.hpp"

TEST(uni_ptr_swap_exchanges_pointers){
    int* raw1 = new int(1);
    int* raw2 = new int(2);
    uni_ptr<int> a = uni_ptr<int>::make_unique(raw1);
    uni_ptr<int> b= uni_ptr<int>::make_unique(raw2);
    a.swap(b);
    expect_eq_scalar("a теперь владеет вторым указателем", raw2, a.get());
    expect_eq_scalar("b теперь владеет первым указателем", raw1, b.get());
}

TEST(uni_ptr_swap_with_empty){
    uni_ptr<int> full= uni_ptr<int>::make_unique(new int(9));
    uni_ptr<int> empty_ptr= uni_ptr<int>::make_unique();
    full.swap(empty_ptr);
    expect_eq_scalar("full стал пустым", nullptr, full.get());
    expect_eq_scalar("empty_ptr получил значение", 9, *empty_ptr);
}

TEST(uni_ptr_self_swap_does_not_break_state){
    uni_ptr<int> ptr= uni_ptr<int>::make_unique(new int(5));
    ptr.swap(ptr);
    expect_eq_scalar("значение не изменилось после self-swap", 5, *ptr);
}

TEST(share_ptr_swap_exchanges_pointers_and_ref_counts){
    share_ptr<int> a(new int(1));
    share_ptr<int> a_copy(a);
    share_ptr<int> b(new int(2));

    a.swap(b);

    expect_eq_scalar("a теперь владеет объектом b", 2, *a);
    expect_eq_scalar("b теперь владеет объектом a", 1, *b);
    expect_eq_scalar("use_count у a теперь 1 (объект b был не разделён)", 1u, a.use_count());
    expect_eq_scalar("use_count у b теперь 2 (счётчик пришёл вместе с объектом a)", 2u, b.use_count());
    expect_eq_scalar("a_copy по-прежнему разделяет исходный объект a (сейчас в b)", 2u, a_copy.use_count());
}

TEST(share_ptr_swap_with_empty){
    share_ptr<int> full(new int(3));
    share_ptr<int> empty_ptr;
    full.swap(empty_ptr);
    expect_eq_scalar("full стал пустым", nullptr, full.get());
    expect_eq_scalar("empty_ptr получил значение", 3, *empty_ptr);
    expect_eq_scalar("use_count у full теперь 0", 0u, full.use_count());
    expect_eq_scalar("use_count у empty_ptr теперь 1", 1u, empty_ptr.use_count());
}

TEST(uni_ptr_array_swap){
    auto a = uni_ptr<int[]>::make_unique(3);
    auto b = uni_ptr<int[]>::make_unique(5);
    a[0] = 111;
    b[0] = 222;
    a.swap(b);
    expect_eq_scalar("a получил элемент из бывшего b", 222, a[0]);
    expect_eq_scalar("b получил элемент из бывшего a", 111, b[0]);
}

TEST(share_ptr_array_swap){
    share_ptr<int[]> a(new int[2]{1, 2});
    share_ptr<int[]> b(new int[2]{9, 8});
    a.swap(b);
    expect_eq_scalar("a[0] после swap", 9, a[0]);
    expect_eq_scalar("b[0] после swap", 1, b[0]);
}
