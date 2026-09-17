#include <memory>
#include "smart_base.hpp"

template<typename T, typename deleter = std::default_delete<T>>
class uni_ptr: public smart_base<T, deleter> {
    using element_type=T;
    uni_ptr(T* new_ptr = nullptr, deleter d = deleter());//

public:
    uni_ptr(const uni_ptr&) = delete;
    uni_ptr& operator=(const uni_ptr&) = delete;
//move-семантика
    uni_ptr& operator=(uni_ptr&& move) noexcept;//
    uni_ptr(uni_ptr&& move) noexcept;//

    element_type* release() noexcept;//
    void reset (element_type* new_ptr, deleter d) noexcept;//
    void swap(uni_ptr& other) noexcept;//

    ~uni_ptr() = default;

    T& operator*();//
    T* operator->();//


    template<typename ... Args>
    static uni_ptr make_unique(Args&& ... args);//
};
/////////////////////////////////////////

template<typename T, typename deleter>
class uni_ptr<T[], deleter> : public smart_base<T[], deleter> {
    using element_type=T;
    explicit uni_ptr(T* new_ptr = nullptr, deleter d = deleter());

public:
    uni_ptr(const uni_ptr&) = delete;
    uni_ptr& operator=(const uni_ptr&) = delete;

    uni_ptr(uni_ptr&& move) noexcept;
    uni_ptr& operator=(uni_ptr&& move) noexcept;
    ~uni_ptr() = default;

    element_type* release() noexcept;
    void reset(element_type* new_ptr = nullptr, deleter d = deleter()) noexcept;
    void swap(uni_ptr& other) noexcept;

    const element_type& operator[](size_t i) const;
    element_type& operator[](size_t i);
    
    static uni_ptr make_unique(size_t n);
};