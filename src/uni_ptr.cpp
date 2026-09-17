#include "uni_ptr.hpp"
#include "smart_base.hpp"

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(T* new_ptr, deleter d): smart_base<T, deleter>(new_ptr, d) {};

//move-семантика
template<typename T, typename deleter>
uni_ptr<T, deleter>& uni_ptr<T, deleter>::operator=(uni_ptr<T, deleter>&& move) noexcept{
    if (this != &move) {
        static_cast<smart_base<T, deleter>&>(*this) = std::move(static_cast<smart_base<T, deleter>&>(move));
    }
    return *this;
}

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(uni_ptr<T, deleter>&& move) noexcept:
                smart_base<T, deleter>(std::move(static_cast<smart_base<T,deleter>&>(move))){}

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::release() noexcept{
    T* temp = get();
    smart_base<T, deleter>::set_ptr(nullptr);
    return temp;
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::reset (element_type* new_ptr, deleter d) noexcept{
    static_cast<smart_base<T, deleter>*>(this)->~smart_base();
    ::new (static_cast<void*>(static_cast<smart_base<T, deleter>*>(this)))
        smart_base<T,deleter>(new_ptr, std::move(d));
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::swap(uni_ptr& other) noexcept{
    std::swap(static_cast<smart_base<T,deleter>&>(*this), static_cast<smart_base<T, deleter>&>(other));
}


template<typename T, typename deleter>
T& uni_ptr<T, deleter>::operator*() { return *smart_base<T, deleter>::get(); }

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::operator->() { return smart_base<T, deleter>::get(); }

template<typename T, typename deleter>
template<typename ... Args>
uni_ptr<T, deleter> uni_ptr<T, deleter>::make_unique(Args&& ... args) {
    return uni_ptr(new T(std::forward<Args>(args)...));
}
////////////////////////////////////////////

template<typename T, typename deleter>
uni_ptr<T[], deleter>::uni_ptr(T* new_ptr, deleter d): smart_base<T[], deleter>(new_ptr, d) {};

//move-семантика
template<typename T, typename deleter>
uni_ptr<T[], deleter>& uni_ptr<T[], deleter>::operator=(uni_ptr<T[], deleter>&& move) noexcept{
    if (this != &move) {
        static_cast<smart_base<T[], deleter>&>(*this) = std::move(static_cast<smart_base<T[], deleter>&>(move));
    }
    return *this;
}

template<typename T, typename deleter>
uni_ptr<T[], deleter>::uni_ptr(uni_ptr<T[], deleter>&& move) noexcept:
                smart_base<T[], deleter>(std::move(static_cast<smart_base<T[], deleter>&>(move))){}

template<typename T, typename deleter>
T* uni_ptr<T[], deleter>::release() noexcept{
    T* temp = get();
    smart_base<T[], deleter>::set_ptr(nullptr);
    return temp;
}

template<typename T, typename deleter>
void uni_ptr<T[], deleter>::reset (element_type* new_ptr, deleter d) noexcept{
    static_cast<smart_base<T[], deleter>*>(this)->~smart_base();
    ::new (static_cast<void*>(static_cast<smart_base<T[], deleter>*>(this)))
        smart_base<T[], deleter>(new_ptr, std::move(d));
}

template<typename T, typename deleter>
void uni_ptr<T[], deleter>::swap(uni_ptr& other) noexcept{
    std::swap(static_cast<smart_base<T[], deleter>&>(*this), static_cast<smart_base<T[], deleter>&>(other));
}


template<typename T, typename deleter>
const T& uni_ptr<T[], deleter>::operator[](size_t i) const {return smart_base<T[], deleter>::get()[i];}

template<typename T, typename deleter>
T& uni_ptr<T[], deleter>::operator[](size_t i) {return smart_base<T[], deleter>::get()[i];}

template<typename T, typename deleter>
uni_ptr<T[], deleter> uni_ptr<T[], deleter>::make_unique(size_t size) {
    return uni_ptr(new T[size]);
}