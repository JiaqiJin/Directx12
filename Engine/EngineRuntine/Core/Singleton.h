#pragma once

#include <type_traits>

namespace Kawaii
{
	template<typename T>
	class Singleton
	{
	public:
		static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
		{
			static T instance;
			return instance;
		}

		virtual ~Singleton() noexcept { }
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	protected:
		Singleton() {}
	};
}