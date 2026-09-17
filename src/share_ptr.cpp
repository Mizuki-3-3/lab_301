#include "share_ptr.hpp"

template <typename T, typename deleter>
share_ptr<T, deleter>::share_ptr(element_type* ptr, deleter d)
    : smart_base<T, deleter>(ptr, std::move(d)), ref_count(new size_t(1)) {}

template <typename T, typename deleter>
share_ptr<T, deleter>::share_ptr(const share_ptr& other) : smart_base<T, deleter>(other.get(), other.get_deleter()), ref_count(other.ref_count){
    ++(*ref_count);
}

template <typename T, typename deleter>
share_ptr<T, deleter>& share_ptr<T, deleter>::operator=(const share_ptr& other) noexcept {
    if (this!= &other){
        if (ref_count){
            if(--(*ref_count) != 0) {
                smart_base<T, deleter>::set_ptr(nullptr);
            }else {delete ref_count;}
        }
        static_cast<smart_base<T, deleter>*>(this)->~smart_base();
        ::new (static_cast<void*>(static_cast<smart_base<T, deleter>*>(this))) smart_base<T, deleter>(other.get(), other.get_deleter());
        ref_count = other.ref_count;
        ++(*ref_count);
    }
    return *this;
}
template <typename T, typename deleter>
share_ptr<T, deleter>::share_ptr(share_ptr&& move) noexcept:
            smart_base<T, deleter>(std::move(static_cast<smart_base<T, deleter>&>(move))), ref_count(move.ref_count){
    move.ref_count = nullptr;
}


template <typename T, typename deleter>
share_ptr<T, deleter>::~share_ptr() {
    if (ref_count){
        if (--(*ref_count) != 0) {
            smart_base<T, deleter>::set_ptr(nullptr);
        }else{delete ref_count;}
    }
}

template <typename T, typename deleter>
share_ptr<T, deleter>& share_ptr<T, deleter>::operator=(share_ptr&& move) noexcept{
    if (this != &move) {
        if(ref_count){
            if(--(*ref_count) != 0) {
                smart_base<T, deleter>::set_ptr(nullptr);
            }else {delete ref_count;}
        }
        static_cast<smart_base<T, deleter>*>(this)->~smart_base();
        ::new (static_cast<void*>(static_cast<smart_base<T, deleter>*>(this))) smart_base<T, deleter>(std::move(static_cast<smart_base<T, deleter>&>(move)));
        ref_count = move.ref_count;
        move.ref_count = nullptr;
    }
    return *this;
}

template <typename T, typename deleter>
T& share_ptr<T, deleter>::operator*() const { return *get(); }

template <typename T, typename deleter>
T* share_ptr<T, deleter>::operator->() const { return get(); }

template <typename T, typename deleter>
size_t share_ptr<T, deleter>::use_count() const noexcept { return ref_count ? *ref_count : 0; }

template <typename T, typename deleter>
bool share_ptr<T, deleter>::unique() const noexcept { return ref_count && *ref_count == 1; }

template <typename T, typename deleter>
void share_ptr<T, deleter>::reset(element_type* new_ptr, deleter d) noexcept{   //нерабериха какая-то, можно ж два раза вызвать у двух разных shar с одним сырым указателем и тогда у обоих будут разные счетчики
    if (ref_count){
        if (--(*ref_count)==0){
            delete ref_count;
        }else{smart_base<T, deleter>::set_ptr(nullptr);}
    }
    static_cast<smart_base<T, deleter>*>(this)->~smart_base();
    ::new (static_cast<void*>(static_cast<smart_base<T, deleter>*>(this)))
        smart_base<T, deleter>(new_ptr, std::move(d));
    ref_count = new size_t(1);
}

template <typename T, typename deleter>
void share_ptr<T, deleter>::swap(share_ptr& other) noexcept{
    std::swap(static_cast<smart_base<T, deleter>&>(*this), static_cast<smart_base<T, deleter>&>(other));
    std::swap(ref_count, other.ref_count);
}

///////////////////////////
template <typename T, typename deleter>
share_ptr<T[], deleter>::share_ptr(element_type* ptr, deleter d)
    : smart_base<T[], deleter>(ptr, std::move(d)), ref_count(new size_t(1)) {}

template <typename T, typename deleter>
share_ptr<T[], deleter>::share_ptr(const share_ptr& other) : smart_base<T[], deleter>(other.get(), other.get_deleter()), ref_count(other.ref_count){
    ++(*ref_count);
}

template <typename T, typename deleter>
share_ptr<T[], deleter>& share_ptr<T[], deleter>::operator=(const share_ptr& other) noexcept {
    if (this!= &other){
        if (ref_count){
            if(--(*ref_count) != 0) {
                smart_base<T[], deleter>::set_ptr(nullptr);
            }else {delete ref_count;}
        }
        static_cast<smart_base<T[], deleter>*>(this)->~smart_base();
        ::new (static_cast<void*>(static_cast<smart_base<T[], deleter>*>(this))) smart_base<T[], deleter>(other.get(), other.get_deleter());
        ref_count = other.ref_count;
        ++(*ref_count);
    }
    return *this;
}
template <typename T, typename deleter>
share_ptr<T[], deleter>::share_ptr(share_ptr&& move) noexcept:
            smart_base<T[], deleter>(std::move(static_cast<smart_base<T[], deleter>&>(move))), ref_count(move.ref_count){
    move.ref_count = nullptr;
}


template <typename T, typename deleter>
share_ptr<T[], deleter>::~share_ptr() {
    if (ref_count){
        if (--(*ref_count) != 0) {
            smart_base<T[], deleter>::set_ptr(nullptr);
        }else{delete ref_count;}
    }
}

template <typename T, typename deleter>
share_ptr<T[], deleter>& share_ptr<T[], deleter>::operator=(share_ptr&& move) noexcept{
    if (this != &move) {
        if(ref_count){
            if(--(*ref_count) != 0) {
                smart_base<T[], deleter>::set_ptr(nullptr);
            }else {delete ref_count;}
        }
        static_cast<smart_base<T[], deleter>*>(this)->~smart_base();
        ::new (static_cast<void*>(static_cast<smart_base<T[], deleter>*>(this))) smart_base<T[], deleter>(std::move(static_cast<smart_base<T[], deleter>&>(move)));
        ref_count = move.ref_count;
        move.ref_count = nullptr;
    }
    return *this;
}

template <typename T, typename deleter>
T& share_ptr<T[], deleter>::operator[](size_t i) { return get()[i]; }

template <typename T, typename deleter>
const T& share_ptr<T[], deleter>::operator[](size_t i) const { return get()[i]; }

template <typename T, typename deleter>
size_t share_ptr<T[], deleter>::use_count() const noexcept { return ref_count ? *ref_count : 0; }

template <typename T, typename deleter>
bool share_ptr<T[], deleter>::unique() const noexcept { return ref_count && *ref_count == 1; }

template <typename T, typename deleter>
void share_ptr<T[], deleter>::reset(element_type* new_ptr, deleter d) noexcept{   //нерабериха какая-то, можно ж два раза вызвать у двух разных shar с одним сырым указателем и тогда у обоих будут разные счетчики
    if (ref_count){
        if (--(*ref_count)==0){
            delete ref_count;
        }else{smart_base<T[], deleter>::set_ptr(nullptr);}
    }
    static_cast<smart_base<T[], deleter>*>(this)->~smart_base();
    ::new (static_cast<void*>(static_cast<smart_base<T[], deleter>*>(this)))
        smart_base<T[], deleter>(new_ptr, std::move(d));
    ref_count = new size_t(1);
}

template <typename T, typename deleter>
void share_ptr<T[], deleter>::swap(share_ptr& other) noexcept{
    std::swap(static_cast<smart_base<T[], deleter>&>(*this), static_cast<smart_base<T[], deleter>&>(other));
    std::swap(ref_count, other.ref_count);
}