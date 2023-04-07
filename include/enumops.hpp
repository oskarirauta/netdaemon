#pragma once

// original source: https://stackoverflow.com/a/40982624/1314831

namespace EnumOps {

	// ADL helper.  See #define below for macro that writes
	// the "this enum should use enum ops" overload:

	template<class T>
	std::false_type use_enum_ops_f(T&&) { return {}; }

	// trait class that detects if we should be messing with this enum:
	template<class T>
	using use_enum_ops = decltype(use_enum_ops_f(std::declval<T>()));

	// to-from underlying type:
	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	constexpr std::underlying_type_t<E> get_underlying(E e) {
		return static_cast<std::underlying_type_t<E>>(e);
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	constexpr E from_underlying(std::underlying_type_t<E> e) {
		return static_cast<E>(e);
	}

	// Clamps your Enum value from 0 to E::MAX_VALUE using modular arithmetic
	// You must include a MAX_VALUE in your enum.

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E clamp_max(std::underlying_type_t<E> e) {
		constexpr auto max = get_underlying(E::MAX_VALUE);
		if (e < 0) {
			auto count = -(e-max+1)/max;
			e =  e + count*max;
		}
		return from_underlying<E>(e % max);
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E& operator+=(E& e, std::underlying_type_t<E> x) {
		e = clamp_max<E>(get_underlying(e) + x);
		return e;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E& operator-=(E& e, std::underlying_type_t<E> x) {
		e = clamp_max<E>(get_underlying(e) - x);
		return e;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E operator+(E e, std::underlying_type_t<E> x) {
		return e+=x;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E operator+(std::underlying_type_t<E> x, E e) {
		return e+=x;
	}

	// no int - enum permitted, but enum-int is:
	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E operator-(E e, std::underlying_type_t<E> x) {
		e -= x;
		return e;
	}

	// enum-enum returns the distance between them:
	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	std::underlying_type_t<E> operator-(E lhs, E rhs) {
		return get_underlying(lhs) - get_underlying(rhs);
	}

	// ++ and -- support:
	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E& operator++(E& lhs ) {
		lhs += 1;
		return lhs;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E operator++(E& lhs, int) {
		auto tmp = lhs;
		++lhs;
		return tmp;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E& operator--(E& lhs) {
		lhs -= 1;
		return lhs;
	}

	template<class E, std::enable_if_t<use_enum_ops<E>{}, int> = 0>
	E operator--(E& lhs, int) {
		auto tmp = lhs;
		--lhs;
		return tmp;
	}

}
// use this macro in the namespace of your enum
// passing it your enun name:
#define ENABLE_ENUM_OPS(...) \
	std::true_type use_enum_ops_f(__VA_ARGS__){return {};}
// Where you wnat to use ops, you must also
// using namespace EnumOps;

// Example code:
/*

#include <iostream>
#include <string>
#include "include/enumops.hpp"

namespace somewhere {

	enum class bob { A, B, C, MAX_VALUE };
	ENABLE_ENUM_OPS(bob)

	const std::string bobName(bob value) {
		if ( value == bob::A ) return "A";
		else if ( value == bob::B ) return "B";
		else if ( value == bob::C ) return "C";
		else if ( value == bob::MAX_VALUE ) return "MAX_VALUE";
		else return "unknown";
	}

	const int bobValue(bob value) {
		if ( value == bob::A ) return 0;
		else if ( value == bob::B ) return 1;
		else if ( value == bob::C ) return 2;
		else if ( value == bob::MAX_VALUE ) return 255;
		else return -1;
	}

}

int main(int argc, char **argv) {

	// note that using EnumOps namespace is mandatory for this to work
	using namespace EnumOps;
	auto x = somewhere::bob::A;
	std::cout << "x is A: " << ( x == somewhere::bob::A ? "true" : "false" ) << " name: " << somewhere::bobName(x) << " value: " << somewhere::bobValue(x) << std::endl;
	std::cout << "increasing x by 1, should become B.." << std::endl;
	++x;
	std::cout << "x is B: " << ( x == somewhere::bob::B ? "true" : "false" ) << " name: " << somewhere::bobName(x) << " value: " << somewhere::bobValue(x) << std::endl;
	std::cout << "increasing x by 3, should become B (b + 1 = c + 1 = a + 1 = b)" << std::endl;
	x+=3;
	std::cout << "x is B: " << ( x == somewhere::bob::B ? "true" : "false" ) << " name: " << somewhere::bobName(x) << " value: " << somewhere::bobValue(x) << std::endl;
	std::cout << "decreasing x by 4, should become A (b - 1 = a, a - 1 = c - 1 = b - 1 = a)" << std::endl;
	x-=4;
	std::cout << "x is A: " << ( x == somewhere::bob::A ? "true" : "false" ) << " name: " << somewhere::bobName(x) << " value: " << somewhere::bobValue(x) << std::endl;
	return 0;
}

*/
