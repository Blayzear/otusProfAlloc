#include <memory>

template <typename T>
struct MyAllocator : std::allocator<T>
{
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind {
		using other = MyAllocator<U>;
	};

	MyAllocator() = default;
	~MyAllocator() = default;

	template <typename U>
	MyAllocator(const MyAllocator<U>&) {}

	T* allocate(std::size_t n) {
		auto p = std::malloc(n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T*>(p);
	}

	void deallocate(T* p, std::size_t n) {
		std::free(p);
	}

	template <typename T, typename... Args>
	void construct(T* p, Args &&...args) {
		new ((void*)p) T(std::forward<Args>(args)...);;
	};

	template <typename T>
	void destroy(T* p) {
		p->~T();
	}
};