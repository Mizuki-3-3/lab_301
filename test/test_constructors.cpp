#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"
#include <type_traits>

struct cast_destr{
    template<typename T>
    void operator()(T* ptr) const { delete ptr; }
    bool operator==(const cast_destr&) const { return true; } 
};

template <typename T>
void test_default_constructor(){
    T smrt_ptr;
    using elem_t = typename T::element_type;
    expect_eq_scalar("default ptr", nullptr, smrt_ptr.get());
    expected_true("default deleter",(std::is_same_v<typename T::deleter_type,std::default_delete<elem_t>>));
    if constexpr (std::is_same_v<T, share_ptr<elem_t>>){
        expect_eq_scalar("default", 0u, smrt_ptr.use_count());
    }
}

template <typename T>
void test_init_constructor(){
    using elem_t = typename T::element_type;
    elem_t* ref = new elem_t(9);
    T smrt_ptr(ref, cast_destr());
    expect_eq_scalar("указатель созданый через new", ref, smrt_ptr.get());
    expected_true("castom deleter", (std::is_same_v<typename T::deleter_type, decltype(cast_destr())>));
    if constexpr (std::is_same_v<T, share_ptr<elem_t>>){
        expect_eq_scalar("how many shared to this ptr", 1u, smrt_ptr.use_count());
    }
}

template <typename T>
void test_copy_constructor(){
    using elem_t = typename T::element_type;
    elem_t* ref = new elem_t(9);
    T smrt_ptr(ref, cast_destr());
    T copy_ptr(smrt_ptr);
    expect_eq_scalar("совпадают ли указатели", smrt_ptr.get(), copy_ptr.get());
    expected_true("совпадают ли удалители", (copy_ptr.get_deleter() == smrt_ptr.get_deleter()));
    expect_eq_scalar("how many shared to this ptr", 2u, smrt_ptr.use_count());
}

template <typename T>
void test_copy_assignment_operator(){
    using elem_t = typename T::element_type;
    elem_t* ref = new elem_t(9);
    T smrt_ptr(ref, cast_destr());
    T copy_ptr = smrt_ptr;
    expect_eq_scalar("совпадают ли указатели", smrt_ptr.get(), copy_ptr.get());
    expected_true("совпадают ли удалители", (copy_ptr.get_deleter() == smrt_ptr.get_deleter()));
    expect_eq_scalar("how many shared to this ptr", 2u, smrt_ptr.use_count());
}

template <typename T>
void test_move_constructor(){
    using elem_t = typename T::element_type;
    elem_t* ref = new elem_t(9);
    T old_ptr(ref, cast_destr());
    T move_ptr(std::move(old_ptr));
    expect_eq_scalar("проверить новый указатель", ref, move_ptr.get());
    expect_eq_scalar("проверить старый указатель", nullptr, old_ptr.get());

    expected_true("совпадают ли удалители", (move_ptr.get_deleter() == old_ptr.get_deleter()));
    if constexpr (std::is_same_v<T, share_ptr<elem_t>>){
        expect_eq_scalar("how many shared to this ptr", 1u, move_ptr.use_count());
        expect_eq_scalar("how many shared to this ptr", 0u, old_ptr.use_count());
    }
}

template <typename T>
void test_move_assignment_operator(){
    using elem_t = typename T::element_type;
    elem_t* ref = new elem_t(9);
    T old_ptr(ref, cast_destr());
    T move_ptr = std::move(old_ptr);
    expect_eq_scalar("проверить новый указатель", ref, move_ptr.get());
    expect_eq_scalar("проверить старый указатель", nullptr, old_ptr.get());

    expected_true("совпадают ли удалители", (move_ptr.get_deleter() == old_ptr.get_deleter()));
    if constexpr (std::is_same_v<T, share_ptr<elem_t>>){
        expect_eq_scalar("how many shared to this ptr", 1u, move_ptr.use_count());
        expect_eq_scalar("how many shared to this ptr", 0u, old_ptr.use_count());
    }
}

TEST(uni_ptr_default_constructor){test_default_constructor<uni_ptr<int>>();}
TEST(share_ptr_default_constructor){test_default_constructor<share_ptr<int>>();}

TEST(uni_ptr_init_constructor){test_init_constructor<uni_ptr<int, cast_destr>>();}
TEST(share_ptr_init_constructor){test_init_constructor<share_ptr<int, cast_destr>>();}

TEST(share_ptr_copy_constructor){test_copy_constructor<share_ptr<int, cast_destr>>();}

TEST(share_ptr_copy_assignment_operator){test_copy_assignment_operator<share_ptr<int, cast_destr>>();}

TEST(uni_ptr_move_constructor){test_move_constructor<uni_ptr<int, cast_destr>>();}
TEST(share_ptr_move_constructor){test_move_constructor<share_ptr<int, cast_destr>>();}

TEST(uni_ptr_move_assignment_operator){test_move_assignment_operator<uni_ptr<int, cast_destr>>();}
TEST(share_ptr_move_assignment_operator){test_move_assignment_operator<share_ptr<int, cast_destr>>();}

