template<typename T>
class uni_ptr{
    T* m_ptr;
    public:
        uni_ptr(const uni_ptr&) = delete;
        uni_ptr& operator=(const uni_ptr&) = delete;
        
        uni_ptr(T* ptr) : m_ptr(ptr) {}
        ~uni_ptr() { delete m_ptr; }

        T& operator*() { return *m_ptr; }
        T* operator->() { return m_ptr; }
        T* get() const { return m_ptr; }

        // Enable move semantics
        uni_ptr(uni_ptr&& other) noexcept : m_ptr(other.m_ptr) {
            other.m_ptr = nullptr;
        }
        uni_ptr& operator=(uni_ptr&& other) noexcept {
            if (this != &other) {
                delete m_ptr;
                m_ptr = other.m_ptr;
                other.m_ptr = nullptr;
            }
            return *this;
        }
};