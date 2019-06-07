#pragma once
#include "native.hpp"

struct ZRefCountedVtbl {
	padding(0x08);
	unsigned int(__thiscall* get_item_count_1)(void* ecx); //+ 0x08
	padding(0x3C);
	unsigned int(__thiscall* get_item_count_2)(void* ecx); //+ 0x48
};

class ZRefCounted {
	ZRefCounted() = delete;
protected:
	virtual ~ZRefCounted() = 0;
private:
	ZRefCountedVtbl* vfptr; //0x00
	union {
		int _m_nRef;
		ZRefCounted* _m_pNext;
	};
	ZRefCounted* _m_pPrev; //0x08
};

static_assert_size(sizeof(ZRefCounted), 0x10);