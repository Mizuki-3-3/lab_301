#pragma once
#include <cstddef>
#include <memory>

template <typename T, typename deleter = std::default_delete<T>>
class share_ptr: private deleter {
    using element_type=T;
    element_type* ptr;
    size_t* ref_count;
public:
    explicit share_ptr(element_type* ptr = nullptr); //

    share_ptr(const share_ptr& other); //
    share_ptr(share_ptr&& move) noexcept; //
    share_ptr& operator=(const share_ptr& other) noexcept; //
    share_ptr& operator=(share_ptr&& move) noexcept; //

    ~share_ptr(); //


    element_type& operator*() const;//
    element_type* operator->() const;//

    void reset(element_type* new_ptr = nullptr, deleter d = deleter()) noexcept;//
    template<typename ... Args>
    void reset(Args&& ... args) noexcept;//


    void swap(share_ptr& other) noexcept;

    element_type* get() const;//
    deleter& get_deleter() const;//
    size_t use_count() const noexcept;//
    bool unique() const noexcept;//


    element_type& operator[](size_t pos);
    bool operator==(const share_ptr& other) const;//
    bool operator!=(const share_ptr& other) const;//
    bool operator<(const share_ptr& other) const;//
    bool operator<=(const share_ptr& other) const;//
    bool operator>(const share_ptr& other) const;//
    bool operator>=(const share_ptr& other) const;//
    template<class Y> bool owner_before(const share_ptr<Y>& other) const noexcept;
    
    operator bool() const noexcept;

};