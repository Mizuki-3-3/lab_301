#pragma once
#include <cstddef>
#include <memory>
#include "smart_base.hpp"

template <typename T, typename deleter = std::default_delete<T>>
class share_ptr: public smart_base<T, deleter> {
    size_t* ref_count;
public:
    using element_type = T;
    using deleter_type = deleter;
    explicit share_ptr(element_type* ptr = nullptr, deleter d = deleter()); //

    share_ptr(const share_ptr& other); 
    share_ptr(share_ptr&& move) noexcept;
    share_ptr& operator=(const share_ptr& other) noexcept;
    share_ptr& operator=(share_ptr&& move) noexcept;

    ~share_ptr();//

    element_type& operator*() const;//
    element_type* operator->() const;//

    void reset(element_type* new_ptr = nullptr, deleter d = deleter()) noexcept;

    void swap(share_ptr& other) noexcept;//

    bool unique() const noexcept;//
    size_t use_count() const noexcept;//
};

///////////////////////////////////////////////////
template<typename T, typename deleter>
class share_ptr<T[], deleter> : public smart_base<T[], deleter> {
    using element_type = T;
    size_t* ref_count;
public:
    explicit share_ptr(element_type* ptr = nullptr, deleter d = deleter()); //
    share_ptr(const share_ptr& other);
    share_ptr& operator=(const share_ptr& other) noexcept;

    share_ptr(share_ptr&& move) noexcept;
    share_ptr& operator=(share_ptr&& move) noexcept;
    ~share_ptr();

    const element_type& operator[](size_t i) const;
    element_type& operator[](size_t i);
    
    void reset(element_type* new_ptr = nullptr, deleter d = deleter()) noexcept;
    void swap(share_ptr& other) noexcept;

    bool unique() const noexcept;//
    size_t use_count() const noexcept;//

};

#include "share_ptr.tpp"