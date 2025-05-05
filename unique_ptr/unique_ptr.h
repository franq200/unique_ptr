#pragma once
#include <utility>

template <typename T>
class unique_ptr
{
public:
	unique_ptr();
	unique_ptr(unique_ptr&& other) noexcept;
	explicit unique_ptr(T* ptr);
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

};

template<typename T>
inline unique_ptr<T>::unique_ptr() : m_ptr(nullptr)
{}

template<typename T>
inline unique_ptr<T>::unique_ptr(unique_ptr&& other) noexcept
{
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
}

template<typename T>
inline unique_ptr<T>::unique_ptr(T* ptr) : m_ptr(ptr) 
{}

template<typename T>
inline unique_ptr<T>::~unique_ptr()
{
	delete m_ptr;
}

template<typename T>
inline T* unique_ptr<T>::Get() const
{
	return m_ptr;
}

template<typename T>
inline T* unique_ptr<T>::Release()
{
	T* temp = m_ptr;
	m_ptr = nullptr;
	return temp;
}

template<typename T>
inline void unique_ptr<T>::Reset(T* p)
{
	delete m_ptr;
	m_ptr = p;
}

template<typename T>
inline void unique_ptr<T>::Swap(unique_ptr& other)
{
	std::swap(m_ptr, other.m_ptr);
}

template<typename T>
inline T& unique_ptr<T>::operator*() const
{
	return *m_ptr;
}

template<typename T>
inline T* unique_ptr<T>::operator->() const
{
	return m_ptr;
}

template<typename T>
inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& other) noexcept
{
	delete m_ptr;
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
	return *this;
}
