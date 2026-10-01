#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"
 
namespace {
 
struct counting_deleter {
    int* counter;
    explicit counting_deleter(int* c = nullptr) : counter(c) {}
    template <typename T>
    void operator()(T* ptr) const {
        if (counter && ptr) { ++(*counter); }
        delete ptr;
    }
    bool operator==(const counting_deleter& other) const { return counter == other.counter; }
};
}
struct counting_array_deleter {
    int* counter;
    explicit counting_array_deleter(int* c = nullptr) : counter(c) {}
    template <typename T>
    void operator()(T* ptr) const {
        if (counter &&  ptr) { ++(*counter); }
        delete[] ptr;
    }
    bool operator==(const counting_array_deleter& other) const { return counter == other.counter; }
};
 
}
 
TEST(uni_ptr_destructor_calls_deleter_once){
    int calls = 0;
    {
        uni_ptr<int, counting_deleter> ptr= uni_ptr<int, counting_deleter>::make_unique(new int(1), counting_deleter(&calls));
        expect_eq_scalar("deleter not called yet", 0, calls);
    }
    expect_eq_scalar("deleter called exactly once on scope exit", 1, calls);
}
 
TEST(uni_ptr_destructor_on_nullptr_is_safe){
    int calls = 0;
    {
        uni_ptr<int, counting_deleter> ptr = uni_ptr<int, counting_deleter>::make_unique(nullptr, counting_deleter(&calls));
    }
    expect_eq_scalar("deleter invoked exactly once even for nullptr", 1, calls);
}
 
TEST(share_ptr_destructor_does_not_delete_while_other_owners_alive){
    int calls = 0;
    share_ptr<int, counting_deleter> outer(nullptr, counting_deleter(&calls));
    {
        share_ptr<int, counting_deleter> inner(new int(42), counting_deleter(&calls));
        outer = inner;
        expect_eq_scalar("use_count is 2", 2u, inner.use_count());
    }
    expect_eq_scalar("object not deleted while outer alive", 0, calls);
    expect_eq_scalar("outer still owns the object", 1u, outer.use_count());
}
 
TEST(share_ptr_destructor_deletes_only_when_last_owner_dies){
    int calls = 0;
    {
        share_ptr<int, counting_deleter> a(new int(7), counting_deleter(&calls));
        {
            share_ptr<int, counting_deleter> b(a);
            expect_eq_scalar("use_count is 2 inside inner scope", 2u, a.use_count());
        }
        expect_eq_scalar("object still alive, a is the last owner", 0, calls);
        expect_eq_scalar("use_count back to 1", 1u, a.use_count());
    }
    expect_eq_scalar("object deleted exactly once when last owner destroyed", 1, calls);
}
 
TEST(share_ptr_array_destructor_calls_delete_array){
    int calls = 0;
    {
        share_ptr<int[], counting_array_deleter> ptr(new int[10], counting_array_deleter(&calls));
        for (int i = 0; i < 10; ++i) { ptr[i] = i; }
    }
    expect_eq_scalar("delete[] вызван ровно один раз", 1, calls);
}
 
TEST(uni_ptr_array_destructor_no_crash_with_default_delete){
    {
        auto ptr = uni_ptr<int[]>::make_unique(10);
        for (int i = 0; i < 10; ++i) { ptr[i] = i; }
        expect_eq_scalar("последний элемент записан верно", 9, ptr[9]);
    }
    expected_true("scope exited without crashing", true);
}
