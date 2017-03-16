#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <numeric>
#include <optional>

template <class ElementType>
class lazy_vector
{
private:
	std::vector<ElementType>& m_container;

	using m_functor_type = std::function<ElementType(lazy_vector, std::size_t)>;
	m_functor_type m_functor;
public:
	using value_type = ElementType;

	lazy_vector(std::vector<ElementType>& container, m_functor_type functor)
		: m_functor(functor), m_container(container)
	{
	}

	ElementType operator[](std::size_t index)
	{
		if (index >= m_container.size())
		{
			auto res = m_functor(*this, index);
			m_container.push_back(res);
			return res;
		}
		else
		{
			return m_container[index];
		}
	}
};

template <class ElementType>
lazy_vector<ElementType> lazy_range(std::vector<ElementType>& vec, ElementType diff, ElementType init = 0)
{
	vec = { init };
	lazy_vector<ElementType> result(vec, [diff](auto lv, std::size_t index)
	{
		return lv[index - 1] + diff;
	});

	return result;
}

template <class ElementType, class IterElementType>
lazy_vector<ElementType> lazy_comp(std::vector<ElementType>& vec,
	lazy_vector<IterElementType> iter_lv,
	std::function<ElementType(lazy_vector<ElementType>, std::size_t)> func)
{
	lazy_vector<ElementType> result(vec, func);
	return result;
}

#define LAZY_COMP(vec, lazy_vec, functor) lazy_comp<decltype(vec)::value_type, decltype(lazy_vec)::value_type>(vec, lazy_vec, functor)