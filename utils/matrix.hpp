#pragma once

#include <vector>
#include <memory>

template<typename T>
class matrix
{
 public:
	using value_type = T;
	
	matrix(size_t rows, size_t cols) : m_arr(rows, std::vector<T>(cols)),
									   m_rows(rows),
									   m_cols(cols) { }
	size_t num_rows() const
	{
		return m_rows;
	}
	size_t num_cols() const
	{
		return m_cols;
	}
	std::vector<T>& operator [](size_t i)
	{
		return m_arr[i];
	}
	const std::vector<T>& operator [](size_t i) const
	{
		return m_arr[i];
	}
 
 private:
	std::vector<std::vector<T>> m_arr;
	size_t m_rows;
	size_t m_cols;
};




