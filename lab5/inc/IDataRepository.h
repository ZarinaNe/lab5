#pragma once

#include <vector>

//определяется шаблонный класс IDataRepository, параметризованный типом T, который будет представлять тип элементов в хранилище данных.
template <typename T>
class IDataRepository {
protected:
	std::vector<T> m_arr; //Защищенное член-данные m_arr типа std::vector<T>, который будет использоваться для хранения элементов типа T
public:
	virtual std::vector<T> Get() { return m_arr; }; //Виртуальная функция Get() возвращает копию вектора m_arr, содержащую все элементы хранилища.
	virtual void Add(T item) { m_arr.push_back(item); }; //добавляет элемент item в конец вектора m_arr.
	virtual void Remove(T item) { m_arr.erase(find(m_arr.begin(), m_arr.end(), item)); }; //удаляет элемент item из вектора m_arr, используя алгоритм std::find для поиска элемента и метод erase для его удаления.
};
