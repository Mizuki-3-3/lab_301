#include "uni_ptr.hpp"
#include "share_ptr.hpp"
#include "test.hpp"
#include "assertions.hpp"
#include <memory>
#include <type_traits>

template <typename T>
void reset_from_default(){
    T ptr;
    auto ref = new int(2435);
    ptr.reset(ref);
    expect_eq_scalar("from nullptr to new int(2345)", ref, ptr.get());
    expected_true("same default deleter", std::is_same_v<std::default_delete<int>, typename T::deleter_type>);
}

template <typename T>
void reset_from_not_default_only_ref_to_nullptr(){
    auto ref = new int(2435);
    T ptr(ref);
    T old_del_ptr(new int(2324));
    ptr.reset();
    expect_eq_scalar("ptr after reset() without arg", nullptr, ptr.get());
    expected_true("same destr as was", std::is_same_v<decltype(old_del_ptr.get_deleter()), decltype(ptr.get_deleter())>);
}

template<typename T>
void reset_from_not_def_to_other_ref(){
    
}

TEST(uni_ptr_reset_from_default){reset_from_default<uni_ptr<int>>();}
TEST(share_ptr_reset_from_default){reset_from_default<share_ptr<int>>();}

TEST(uni_ptr_reset_from_not_default_only_ref_to_nullptr){reset_from_not_default_only_ref_to_nullptr<uni_ptr<int>>();}
TEST(share_ptr_reset_from_not_default_only_ref_to_nullptr){reset_from_not_default_only_ref_to_nullptr<share_ptr<int>>();}
// template <typename T>
// void reset_from_not_default_ref_and_del(){
//     auto ref = new int(2435);
//     T ptr(ref);

//     ptr.reset()
// }