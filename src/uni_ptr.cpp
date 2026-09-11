#include "uni_ptr.hpp"

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(T* new_ptr, deleter d): deleter(d), ptr(new_ptr) {};

template<typename T, typename deleter>
uni_ptr<T, deleter>::~uni_ptr() {  static_cast<deleter&>(*this)(ptr); }

//move-семантика
template<typename T, typename deleter>
uni_ptr<T, deleter>& uni_ptr<T, deleter>::operator=(uni_ptr<T, deleter>&& move) noexcept{
    if (this != &move) {
        static_cast<deleter&>(*this)(ptr);
        ptr = std::move(move.ptr);
        move.ptr = nullptr;
        static_cast<deleter&>(*this) = std::move(static_cast<deleter&>(move));
    }
    return *this;
}

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(uni_ptr<T, deleter>&& move) noexcept:
                deleter(move.get_deleter()), ptr(std::move(move.ptr)) {
                    move.ptr = nullptr;
                }

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::release() noexcept{
    element_type* temp=ptr;
    ptr=nullptr;
    return temp;
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::reset (element_type* new_ptr, deleter d) noexcept{
    static_cast<deleter&>(*this)(ptr);
    ptr = new_ptr;
    static_cast<deleter&>(*this)= d;
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::swap(uni_ptr& other) noexcept{
    std::swap(ptr, other.ptr);
    std::swap(static_cast<deleter&>(*this), static_cast<deleter&>(other));
}

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::get() const noexcept{ return ptr; }

template<typename T, typename deleter>
const deleter& uni_ptr<T, deleter>::get_deleter() const noexcept {return static_cast<deleter&>(*this); }

template<typename T, typename deleter>
deleter& uni_ptr<T, deleter>::get_deleter() noexcept {return static_cast<deleter&>(*this); }

template<typename T, typename deleter>
T& uni_ptr<T, deleter>::operator*() { return *ptr; }

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::operator->() { return ptr; }

template<typename T, typename deleter>
uni_ptr<T, deleter>::operator bool() const noexcept { return ptr != nullptr; }

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator==(const uni_ptr& other) const{return ptr==other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator!=(const uni_ptr& other) const{return ptr!=other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator<(const uni_ptr& other) const{return ptr<other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator<=(const uni_ptr& other) const{return ptr<=other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator>(const uni_ptr& other) const{return ptr>other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator>=(const uni_ptr& other) const{return ptr>=other.ptr;}

template<typename T, typename deleter>
template<typename ... Args>
void uni_ptr<T, deleter>::reset(Args&& ... args) noexcept{
    static_cast<deleter&>(*this)(ptr);
    ptr = new T(std::forward<Args>(args)...);
}

template<typename T, typename deleter>
template<typename ... Args>
uni_ptr<T, deleter> uni_ptr<T, deleter>::make_unique(Args&& ... args) {
    return uni_ptr(new T(std::forward<Args>(args)...));
}
/////////////////////////////////////////////

template<typename T, typename deleter>
uni_ptr<T[], deleter>::uni_ptr(T* new_ptr, deleter d): deleter(d), ptr(new_ptr) {};

template<typename T, typename deleter>
uni_ptr<T[], deleter>::~uni_ptr() {  static_cast<deleter&>(*this)(ptr); }

//move-семантика
template<typename T, typename deleter>
uni_ptr<T[], deleter>& uni_ptr<T[], deleter>::operator=(uni_ptr<T[], deleter>&& move) noexcept{
    if (this != &move) {
        static_cast<deleter&>(*this)(ptr);
        ptr = std::move(move.ptr);
        move.ptr = nullptr;
        static_cast<deleter&>(*this) = std::move(static_cast<deleter&>(move));
    }
    return *this;
}

template<typename T, typename deleter>
uni_ptr<T[], deleter>::uni_ptr(uni_ptr<T[], deleter>&& move) noexcept:
                deleter(move.get_deleter()), ptr(std::move(move.ptr)) {
                    move.ptr = nullptr;
                }

template<typename T, typename deleter>
T* uni_ptr<T[], deleter>::release() noexcept{
    element_type* temp=ptr;
    ptr=nullptr;
    return temp;
}

template<typename T, typename deleter>
void uni_ptr<T[], deleter>::reset (element_type* new_ptr, deleter d) noexcept{
    static_cast<deleter&>(*this)(ptr);
    ptr = new_ptr;
    static_cast<deleter&>(*this)= d;
}

template<typename T, typename deleter>
void uni_ptr<T[], deleter>::swap(uni_ptr& other) noexcept{
    std::swap(ptr, other.ptr);
    std::swap(static_cast<deleter&>(*this), static_cast<deleter&>(other));
}

template<typename T, typename deleter>
T* uni_ptr<T[], deleter>::get() const noexcept{ return ptr; }

template<typename T, typename deleter>
const deleter& uni_ptr<T[], deleter>::get_deleter() const noexcept {return static_cast<deleter&>(*this); }

template<typename T, typename deleter>
deleter& uni_ptr<T[], deleter>::get_deleter() noexcept {return static_cast<deleter&>(*this); }

template<typename T, typename deleter>
uni_ptr<T[], deleter>::operator bool() const noexcept { return ptr != nullptr; }

template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator==(const uni_ptr& other) const{return ptr==other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator!=(const uni_ptr& other) const{return ptr!=other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator<(const uni_ptr& other) const{return ptr<other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator<=(const uni_ptr& other) const{return ptr<=other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator>(const uni_ptr& other) const{return ptr>other.ptr;}
template<typename T, typename deleter>
bool uni_ptr<T[], deleter>::operator>=(const uni_ptr& other) const{return ptr>=other.ptr;}

template<typename T, typename deleter>
const T& uni_ptr<T[], deleter>::operator[](size_t i) const {return ptr[i];}

template<typename T, typename deleter>
T& uni_ptr<T[], deleter>::operator[](size_t i) {return ptr[i];}

template<typename T, typename deleter>
uni_ptr<T[], deleter> uni_ptr<T[], deleter>::make_unique(size_t size) {
    return uni_ptr(new T[size]);
}