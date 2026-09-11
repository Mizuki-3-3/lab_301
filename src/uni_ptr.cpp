#include "uni_ptr.hpp"

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(T* ptr, deleter d): deleter(d), m_ptr(ptr) {};


template<typename T, typename deleter>
uni_ptr<T, deleter>::~uni_ptr() {  static_cast<deleter&>(*this)(m_ptr); }

//move-семантика
template<typename T, typename deleter>
uni_ptr<T, deleter>& uni_ptr<T, deleter>::operator=(uni_ptr<T, deleter>&& other) noexcept{
    if (this != &other) {
        delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
}

template<typename T, typename deleter>
uni_ptr<T, deleter>::uni_ptr(uni_ptr<T, deleter>&& other) noexcept : deleter(std::move(other.deleter)), m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::release(element_type* new_ptr = nullptr) noexcept{
    element_type* temp=m_ptr;
    m_ptr=new_ptr;
    return temp;
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::reset (element_type* new_ptr) noexcept{
    static_cast<deleter&>(*this)(m_ptr);
    m_ptr=new_ptr;
}

template<typename T, typename deleter>
void uni_ptr<T, deleter>::swap(uni_ptr& other) noexcept{
        std::swap(m_ptr, other.m_ptr);
    }
template<typename T, typename deleter>
T& uni_ptr<T, deleter>::operator*() { return *m_ptr; }

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::operator->() { return m_ptr; }

template<typename T, typename deleter>
T* uni_ptr<T, deleter>::get() const { return m_ptr; }

template<typename T, typename deleter>
deleter& uni_ptr<T, deleter>::get_deleter() const noexcept {return static_cast<deleter&>(*this); }

template<typename T, typename deleter>
uni_ptr<T, deleter>::operator bool() const noexcept { return m_ptr != nullptr; }

template<typename T, typename deleter>
T& uni_ptr<T, deleter>::operator[](std::size_t pos){return m_ptr[pos];}

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator==(const uni_ptr& other) const{return m_ptr==other.m_ptr;}

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator!=(const uni_ptr& other) const{return m_ptr!=other.m_ptr;}


template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator<(const uni_ptr& other) const{return m_ptr<other.m_ptr;}

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator<=(const uni_ptr& other) const{return m_ptr<=other.m_ptr;}

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator>(const uni_ptr& other) const{return m_ptr>other.m_ptr;}

template<typename T, typename deleter>
bool uni_ptr<T, deleter>::operator>=(const uni_ptr& other) const{return m_ptr>=other.m_ptr;}

template<typename T, typename deleter>
template<typename ... Args>
uni_ptr<T, deleter> uni_ptr<T, deleter>::make_unique(Args&& ... args) {
    return uni_ptr(new T(std::forward<Args>(args)...));
}
template<typename T, typename deleter>
uni_ptr<T, deleter> uni_ptr<T, deleter>::make_unique(size_t size) {
    return uni_ptr(new T[size]);
}