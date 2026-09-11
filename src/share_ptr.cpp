#include "share_ptr.hpp"


template <typename T, typename deleter>
share_ptr<T, deleter>::share_ptr(const share_ptr& other) : ptr(other.ptr), ref_count(other.ref_count), deleter(other.get_deleter()) {
    ++(*ref_count);
}

template <typename T, typename deleter>
share_ptr<T, deleter>& share_ptr<T, deleter>::operator=(const share_ptr& other) noexcept {
    if (this!=&other){
        if(--(*ref_count) == 0) {
            static_cast<deleter&>(*this)(ptr);
            delete ref_count;
        }
        ptr = other.ptr;
        ref_count = other.ref_count;
        static_cast<deleter&>(*this) = other.get_deleter();
        ++(*ref_count);
    }
    return *this;
}
template <typename T, typename deleter>
share_ptr<T, deleter>::share_ptr(share_ptr&& move) noexcept:
            ptr(std::move(move.ptr)), ref_count(std::move(move.ref_count)),
            deleter(std::move(static_cast<deleter&>(move))) {}


template <typename T, typename deleter>
share_ptr<T, deleter>::~share_ptr() {
    if (--(*ref_count) == 0) {
        static_cast<deleter&>(*this)(ptr);
        delete ref_count;
    }
}

template <typename T, typename deleter>
share_ptr<T, deleter>& share_ptr<T, deleter>::operator=(share_ptr&& move) noexcept{
    if (this != &move) {
        if (--(*ref_count) == 0) {
            static_cast<deleter&>(*this)(ptr);
            delete ref_count;
        }
        ptr = std::move(move.ptr);
        ref_count = std::move(move.ref_count);
        static_cast<deleter&>(*this) = std::move(static_cast<deleter&>(move));
    }
    return *this;
}

template <typename T, typename deleter>
T& share_ptr<T, deleter>::operator*() const { return *ptr; }

template <typename T, typename deleter>
T* share_ptr<T, deleter>::operator->() const { return ptr; }

template <typename T, typename deleter>
T* share_ptr<T, deleter>::get() const { return ptr; }

template <typename T, typename deleter>
deleter& share_ptr<T, deleter>::get_deleter() const { return static_cast<deleter&>(*this); }

template <typename T, typename deleter>
size_t share_ptr<T, deleter>::use_count() const noexcept { return *ref_count; }

template <typename T, typename deleter>
bool share_ptr<T, deleter>::unique() const noexcept { return *ref_count == 1; }

template <typename T, typename deleter>
void share_ptr<T, deleter>::reset(element_type* new_ptr, deleter d) noexcept{   //нерабериха какая-то, можно ж два раза вызвать у двух разных shar с одним сырым указателем и тогда у обоих будут разные счетчики
    if (--(*ref_count)==0){
        delete ref_count;
        static_cast<deleter&>(*this)(ptr);
    }
    ptr = new_ptr;
    ref_count = new size_t(1);
    static_cast<deleter&>(*this) = d;
}

template <typename T, typename deleter>
template<typename ... Args>
void share_ptr<T, deleter>::reset(Args&& ... args) noexcept{
    reset(new element_type(std::forward<Args>(args)...));
}


template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator==(const share_ptr& other) const{return ptr == other.ptr;}
template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator!=(const share_ptr& other) const{return ptr != other.ptr;}
template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator<(const share_ptr& other) const{return ptr < other.ptr;}
template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator<=(const share_ptr& other) const{return ptr <= other.ptr;}
template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator>(const share_ptr& other) const{return ptr > other.ptr;}
template <typename T, typename deleter>
bool share_ptr<T, deleter>::operator>=(const share_ptr& other) const{return ptr >= other.ptr;}