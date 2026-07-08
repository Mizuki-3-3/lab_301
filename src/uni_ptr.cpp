#include "uni_ptr.hpp"

template<typename T>
uni_ptr<T>& uni_ptr<T>::operator=(uni_ptr<T>&& other) noexcept{
    if (this != &other) {
        delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
}