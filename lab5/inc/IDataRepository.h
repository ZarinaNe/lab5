#pragma once

#include <vector>

template <typename T>
class IDataRepository {
protected:
	std::vector<T> m_arr;
public:
	virtual std::vector<T> Get() { return m_arr; };
	virtual void Add(T item) { m_arr.push_back(item); };
	virtual void Remove(T item) { m_arr.erase(find(m_arr.begin(), m_arr.end(), item)); };
};