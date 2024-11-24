#include <iterator>
#include <cstddef>
#include "allocator.cpp"

template <typename T, class Allocator = std::allocator<T> >
struct MyContainer {
public:
	void push_back(T& element) {
        if (m_size == m_capacity)
        {
            m_capacity *= 2;
            T* new_data = m_allocator.allocate(m_capacity);
            auto buff = new_data;
            for (auto i = begin(); i != end(); i++)
            {
                m_allocator.construct(buff, *i);
                buff++;
            }
            std::swap(new_data, m_data);
            m_allocator.deallocate(new_data, m_capacity);
        }
        m_allocator.construct(end().operator->(), element);
        m_size++;
    };
    void reserve(std::size_t n) {
        m_data = m_allocator.allocate(n);
        m_capacity += n;
    }
	size_t size() {
        return m_size;
    };
    bool empty() {
        begin() == end() ? return true;
    };
    MyContainer() {
        reserve(default_capacity);
    };
    ~MyContainer() {
        m_allocator.deallocate(m_data, m_capacity);
    };

    struct Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(T) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[m_size]); }

private:
    Allocator m_allocator;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
    T* m_data = nullptr;
    const std::size_t default_capacity = 5;
};