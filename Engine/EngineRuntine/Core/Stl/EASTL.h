#pragma once

#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/string_view.h>
#include <EASTL/string.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/weak_ptr.h>
#include <EASTL/functional.h>

namespace Kawaii
{
	// Vector
	template<class T> 
	using vector = eastl::vector<T>;

	// Map
	template<class Key, class Val> 
	using unordered_map = eastl::unordered_map<Key, Val>;

	// String View
	using string_view = eastl::string_view;
	using wstring_view = eastl::wstring_view;
	using u8string_view = eastl::u8string_view;
	using u16string_view = eastl::u16string_view;
	using u32string_view = eastl::u32string_view;

	// String
	using string = eastl::string;
	using wstring = eastl::wstring;
	using u8string = eastl::string8;
	using u16string = eastl::string16;
	using u32string = eastl::string32;

	// Ptr
	template <typename T>
	using RefPtr = eastl::shared_ptr<T>;

	template <typename T, typename... Args>
	RefPtr<T> MakeRef(Args&&... args)
	{
		return eastl::make_shared<T>(eastl::forward<Args>(args)...);
	}

	template <typename T>
	using UniquePtr = eastl::unique_ptr<T>;

	template <typename T, typename... Args>
	UniquePtr<T> MakeUnique(Args&&... args)
	{
		return eastl::make_unique<T>(eastl::forward<Args>(args)...);
	}

	template <typename T>
	using WeakRefPtr = eastl::weak_ptr<T>;

}