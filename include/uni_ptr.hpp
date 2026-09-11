#include <cstddef>
#include <memory>
template<typename T, typename deleter = std::default_delete<T>>
class uni_ptr: private deleter {
    using element_type=T;
    T* m_ptr;
    uni_ptr(T* ptr = nullptr, deleter d = deleter());//

public:
    uni_ptr(const uni_ptr&) = delete;
    uni_ptr& operator=(const uni_ptr&) = delete;
//move-семантика
    uni_ptr& operator=(uni_ptr&& move) noexcept;//
    uni_ptr(uni_ptr&& move) noexcept;//
//

    element_type* release(element_type* new_ptr = nullptr) noexcept;//
    void reset (element_type* new_ptr) noexcept;//
    void swap(uni_ptr& other) noexcept;//

    ~uni_ptr();//

    T* get() const noexcept;//
    deleter& get_deleter() noexcept;//
    const deleter& get_deleter() const noexcept;
    operator bool() const noexcept;//
    T& operator*();//
    T* operator->();//
    T& operator[](std::size_t i);

    bool operator==(const uni_ptr& other) const;//
    bool operator!=(const uni_ptr& other) const;//
    bool operator<(const uni_ptr& other) const;
    bool operator<=(const uni_ptr& other) const;
    bool operator>(const uni_ptr& other) const;
    bool operator>=(const uni_ptr& other) const;

    template<typename ... Args>
    uni_ptr make_unique(Args&& ... args);//
    uni_ptr make_unique(size_t size);//
};