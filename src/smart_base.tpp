#include "smart_base.hpp"

template <typename T, typename deleter>
smart_base<T, deleter>::smart_base(T* new_ptr, deleter d): deleter(d), ptr(new_ptr) {}

template <typename T, typename deleter>
smart_base<T, deleter>::~smart_base() {
    static_cast<deleter&>(*this)(ptr);
}

template <typename T, typename deleter>
T* smart_base<T, deleter>::get() const noexcept{
    return ptr;
}

template <typename T, typename deleter>
deleter& smart_base<T, deleter>::get_deleter() noexcept{
    return static_cast<deleter&>(*this);
}

template <typename T, typename deleter>
const deleter& smart_base<T, deleter>::get_deleter() const noexcept{
    return static_cast<const deleter&>(*this);
}

template<typename T, typename deleter>
smart_base<T, deleter>::operator bool() const noexcept { return ptr != nullptr; }

template<typename T, typename deleter>
bool smart_base<T, deleter>::operator==(const smart_base& other) const{return ptr==other.ptr;}
template<typename T, typename deleter>
bool smart_base<T, deleter>::operator!=(const smart_base& other) const{return ptr!=other.ptr;}
template<typename T, typename deleter>
bool smart_base<T, deleter>::operator<(const smart_base& other) const{return ptr<other.ptr;}
template<typename T, typename deleter>
bool smart_base<T, deleter>::operator<=(const smart_base& other) const{return ptr<=other.ptr;}
template<typename T, typename deleter>
bool smart_base<T, deleter>::operator>(const smart_base& other) const{return ptr>other.ptr;}
template<typename T, typename deleter>
bool smart_base<T, deleter>::operator>=(const smart_base& other) const{return ptr>=other.ptr;}
//////////////////////////////////////////////////////////////////////////////

template <typename T, typename deleter>
smart_base<T[], deleter>::smart_base(T* new_ptr, deleter d): deleter(d), ptr(new_ptr) {}

template <typename T, typename deleter>
smart_base<T[], deleter>::~smart_base() {
    static_cast<deleter&>(*this)(ptr);
}

template <typename T, typename deleter>
T* smart_base<T[], deleter>::get() const noexcept{
    return ptr;
}

template <typename T, typename deleter>
deleter& smart_base<T[], deleter>::get_deleter() noexcept{
    return static_cast<deleter&>(*this);
}

template <typename T, typename deleter>
const deleter& smart_base<T[], deleter>::get_deleter() const noexcept{
    return static_cast<const deleter&>(*this);
}

template<typename T, typename deleter>
smart_base<T[], deleter>::operator bool() const noexcept { return ptr != nullptr; }

template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator==(const smart_base& other) const{return ptr==other.ptr;}
template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator!=(const smart_base& other) const{return ptr!=other.ptr;}
template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator<(const smart_base& other) const{return ptr<other.ptr;}
template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator<=(const smart_base& other) const{return ptr<=other.ptr;}
template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator>(const smart_base& other) const{return ptr>other.ptr;}
template<typename T, typename deleter>
bool smart_base<T[], deleter>::operator>=(const smart_base& other) const{return ptr>=other.ptr;}

template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator++(int){
    auto tmp = *this;
    ++ptr;
    return tmp;
}

template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator++(){
    ++ptr;
    return *this;
}
template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator--(int){
    auto tmp = *this;
    --ptr;
    return tmp;
}
template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator--(){
    ptr--;
    return *this;
}
template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator+(int n){
    ptr += n;
    return *this;
}

template<typename T, typename deleter>
smart_base<T[], deleter> smart_base<T[], deleter>::operator-(int n){
    ptr -= n;
    return *this;
}