#pragma once
#include "native.hpp"

template <typename T>
struct ZRef {
	operator const T*() const {
		return this->p;
	}
	padding(0x04);
	T* p;
};

static_assert_size(sizeof(ZRef<void*>), 0x08);