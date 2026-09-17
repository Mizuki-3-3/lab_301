#pragma once

template <typename T, typename deleter>
class smart_base: private deleter {
    T* ptr;
public:
    ~smart_base();
    smart_base(T* new_ptr = nullptr, deleter d = deleter());
    smart_base(const smart_base& other){
        ptr = other.ptr;
        static_cast<deleter&>(*this) = static_cast<const deleter&>(other);
    }
    smart_base& operator=(const smart_base& other){
        if (this != &other) {
            ptr = other.ptr;
            static_cast<deleter&>(*this).~deleter();
            ::new (static_cast<void*>(static_cast<deleter*>(this)))deleter(static_cast<const deleter&>(other));
        }
        return *this;
        
    }

    smart_base(smart_base&& move) noexcept: deleter(std::move(move)), ptr(move.ptr) {
        move.ptr = nullptr;
    }

    smart_base& operator=(smart_base&& move){
        if (this != &move) {
            if (ptr) {static_cast<deleter&>(*this)(ptr);}
            ptr = move.ptr;
            move.ptr = nullptr;
            static_cast<deleter&>(*this).~deleter();
            ::new (static_cast<void*>(static_cast<deleter*>(this)))deleter(std::move(static_cast<const deleter&>(move)));
        }
        return *this;
    }

    template<typename ... Args>
    smart_base(Args&& ... args){
        ptr = new T(std::forward<Args>(args)...);
    }
    
    T* get() const noexcept;
    deleter& get_deleter() noexcept;
    const deleter& get_deleter() const noexcept;

    operator bool() const noexcept;

    bool operator==(const smart_base& other) const;
    bool operator!=(const smart_base& other) const;
    bool operator<(const smart_base& other) const;
    bool operator<=(const smart_base& other) const;
    bool operator>(const smart_base& other) const;
    bool operator>=(const smart_base& other) const;
protected:
    void set_ptr(T* new_ptr){ptr = new_ptr;}
};