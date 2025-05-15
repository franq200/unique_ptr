#pragma once
#include <utility>
#include <memory>
template <typename T, typename D = std::default_delete<T>>
class unique_ptr
{
public:
	unique_ptr();
	explicit unique_ptr(T* ptr, D deleter = std::default_delete<T>());
	unique_ptr(unique_ptr&& other) noexcept;
	~unique_ptr();
	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;
	T* Get() const;
	T* Release();
	void Reset(T* p = nullptr);
	void Swap(unique_ptr& other);
	T& operator*() const;
	T* operator->() const;
	unique_ptr& operator=(unique_ptr&& other) noexcept;
private:
	T* m_ptr;
	D m_deleter;
};

template<typename T, typename D>
inline unique_ptr<T, D>::unique_ptr() : m_ptr(nullptr)
{}

template<typename T, typename D>
inline unique_ptr<T, D>::unique_ptr(unique_ptr&& other) noexcept
{
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
}

template<typename T, typename D>
inline unique_ptr<T, D>::unique_ptr(T* ptr, D deleter) : m_ptr(ptr), m_deleter(deleter)
{}

template<typename T, typename D>
inline unique_ptr<T, D>::~unique_ptr()
{
	m_deleter(m_ptr);
}

template<typename T, typename D>
inline T* unique_ptr<T, D>::Get() const
{
	return m_ptr;
}

template<typename T, typename D>
inline T* unique_ptr<T, D>::Release()
{
	T* temp = m_ptr;
	m_ptr = nullptr;
	return temp;
}

template<typename T, typename D>
inline void unique_ptr<T, D>::Reset(T* p)
{
	m_deleter(m_ptr);
	m_ptr = p;
}

template<typename T, typename D>
inline void unique_ptr<T, D>::Swap(unique_ptr& other)
{
	std::swap(m_ptr, other.m_ptr);
}

template<typename T, typename D>
inline T& unique_ptr<T, D>::operator*() const
{
	return *m_ptr;
}

template<typename T, typename D>
inline T* unique_ptr<T, D>::operator->() const
{
	return m_ptr;
}

template<typename T, typename D>
inline unique_ptr<T,D>& unique_ptr<T, D>::operator=(unique_ptr&& other) noexcept
{
	m_deleter(m_ptr);
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
	return *this;
}
