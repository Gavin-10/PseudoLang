
#pragma once

#include <variant>

#include "Object.h"
#include "LangError.h"

namespace ValueOps {

	typedef std::variant<bool, double, Obj*, nullptr_t> Value;

	template <typename T>
	inline static T valueAs(Value value, std::string_view type, int line) {
		try {
			return std::get<T>(value);
		}
		catch (const std::bad_variant_access& ex) {
			LangError::valueAccessError(type, line);
		}
	}

	template <typename T>
	inline static bool valueIs(Value value) {
		return std::holds_alternative<T>(value);
	}

}