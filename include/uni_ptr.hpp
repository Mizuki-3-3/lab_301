#include <memory>
template<typename T, typename deleter = std::default_delete<T>>
class uni_ptr: private deleter {
    using element_type=T;
    T* ptr;
    uni_ptr(T* new_ptr = nullptr, deleter d = deleter());//

public:
    uni_ptr(const uni_ptr&) = delete;
    uni_ptr& operator=(const uni_ptr&) = delete;
//move-семантика
    uni_ptr& operator=(uni_ptr&& move) noexcept;//
    uni_ptr(uni_ptr&& move) noexcept;//

    element_type* release() noexcept;//
    template<typename ... Args>
    void reset(Args&& ... args) noexcept;//
    void reset (element_type* new_ptr, deleter d) noexcept;//
    void swap(uni_ptr& other) noexcept;//

    ~uni_ptr();//

    T* get() const noexcept;//
    deleter& get_deleter() noexcept;//
    const deleter& get_deleter() const noexcept;
    operator bool() const noexcept;//
    T& operator*();//
    T* operator->();//

    bool operator==(const uni_ptr& other) const;//
    bool operator!=(const uni_ptr& other) const;//
    bool operator<(const uni_ptr& other) const;//
    bool operator<=(const uni_ptr& other) const;//
    bool operator>(const uni_ptr& other) const;//
    bool operator>=(const uni_ptr& other) const;//

    template<typename ... Args>
    uni_ptr make_unique(Args&& ... args);//
};
/////////////////////////////////////////

template<typename T, typename deleter>
class uni_ptr<T[], deleter> : private deleter {
    using element_type = T;
    T* ptr;
    explicit uni_ptr(T* new_ptr = nullptr, deleter d = deleter());

public:
    uni_ptr(const uni_ptr&) = delete;
    uni_ptr& operator=(const uni_ptr&) = delete;

    uni_ptr(uni_ptr&& move) noexcept;
    uni_ptr& operator=(uni_ptr&& move) noexcept;
    ~uni_ptr();

    element_type* release() noexcept;
    void reset(element_type* new_ptr = nullptr, deleter d = deleter()) noexcept;
    void swap(uni_ptr& other) noexcept;

    T* get() const noexcept;
    deleter& get_deleter() noexcept;
    const deleter& get_deleter() const noexcept;
    operator bool() const noexcept;

    bool operator==(const uni_ptr& other) const;//
    bool operator!=(const uni_ptr& other) const;//
    bool operator<(const uni_ptr& other) const;//
    bool operator<=(const uni_ptr& other) const;//
    bool operator>(const uni_ptr& other) const;//
    bool operator>=(const uni_ptr& other) const;//

    const element_type& operator[](size_t i) const;
    element_type& operator[](size_t i);
    
    uni_ptr make_unique(size_t n);
};