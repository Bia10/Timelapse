#pragma once
#include <vector>
#include <memory>
#include "MapleLib/ZRef.hpp"
#include "MapleLib/ZArray.hpp"
#include "MapleLib/TSecType.hpp"

namespace Timelapse
{
#pragma pack(push, 1)
	struct ZRefCountedVtbl {
		padding(0x08);
		unsigned int(__thiscall* get_item_count_1)(void* ecx); //+ 0x08
		padding(0x3C);
		unsigned int(__thiscall* get_item_count_2)(void* ecx); //+ 0x48
	};

	struct ZRefCounted {
		ZRefCountedVtbl* vfptr;
		union {
			int ref;
			ZRefCounted* next;
		};
		ZRefCounted* prev;
	};

	struct GW_ItemSlotBase {
		ZRefCounted baseclass;                                 //+ 0x00
		TSecType<long> nItemID;                                //+ 0x0C
		LARGE_INTEGER liCastItemSN;                            //+ 0x18
		FILETIME dateExpire;                                   //+ 0x20
		padding(0x14);                                         //+ 0x28
	};

	struct CharacterData {		
		//GW_CharacterStat characterStat; // size? 249 229 217 bytes? D9
		padding(0xD9)
		ZRef<GW_ItemSlotBase> aEquipped[60]; // why 60? should be less
		//ZRef<GW_ItemSlotBase> aEquipped2[60]; // ?? in v 0.95
		//ZRef<GW_ItemSlotBase> aDragonEquipped[4]; // ?? in v 0.95
		//ZRef<GW_ItemSlotBase> aMechanicEquipped[5]; // ?? in v 0.95
		ZArray<ZRef<GW_ItemSlotBase>> aaItemSlot[6]; // ?? in v 0.95
	};
#pragma pack(pop)

struct item {
	item(std::size_t tab, std::size_t index, std::size_t item_id, std::size_t quantity)
		: tab(tab), index(index), item_id(item_id), quantity(quantity) {}

	std::size_t tab;
	std::size_t index;
	std::size_t item_id;
	std::size_t quantity;
};

class inventory {
	public:
		inventory(unsigned int CWvsContext, unsigned int CWvsContext__GetCharacterData, unsigned int TSecType__GetData)
		: CWvsContext(reinterpret_cast<void* const>(CWvsContext)), inventories(nullptr), equip(nullptr) {
		this->CWvsContext__GetCharacterData = reinterpret_cast<CWvsContext__GetCharacterData_t>(CWvsContext__GetCharacterData);
		this->TSecType__GetData = reinterpret_cast<TSecType__GetData_t>(TSecType__GetData);
		}

		~inventory(){}

		bool update() {
			ZRef<CharacterData> ref_characterdata;

			if (!CWvsContext__GetCharacterData(*reinterpret_cast<void**>(this->CWvsContext), nullptr, &ref_characterdata)) {
				return false;
			}

			this->inventories = ref_characterdata.p->aaItemSlot;
			this->equip = ref_characterdata.p->aEquipped;

			return true;
		}

		std::size_t get_size(int type) {
			ZRef<GW_ItemSlotBase>* inventory = this->inventories[static_cast<int>(type)].a;
			return reinterpret_cast<std::size_t>(inventory[-1].p) - 1;
		}

		bool get_items(std::vector<std::shared_ptr<item> > &items) {
			for (int k = 1; k <= 5; k++) {
				ZRef<GW_ItemSlotBase>* inventory = this->inventories[static_cast<int>(k)].a;
				const std::size_t size = this->get_size(k);

				if (k == 3) {
					k = 4;
				}
				else if (k == 4) {
					k = 3;
				}

				for (std::size_t i = 1; i < (size + 1); i++) {
					ZRef<GW_ItemSlotBase> slot = inventory[i];
					if (slot.p) {
						items.push_back(std::shared_ptr<item>(new item(k, i, (TSecType__GetData(&slot.p->nItemID, 0)), this->get_quantity(slot))));
					}
				}

				if (k == 3) {
					k = 4;
				}
				else if (k == 4) {
					k = 3;
				}
			}

			if (items.empty()) { return false; }
			return true;
		}

	static std::size_t get_quantity(ZRef<GW_ItemSlotBase> slot) {
			if (!slot.p) {
				return 0;
			}

			std::size_t quantity = slot.p->baseclass.vfptr->get_item_count_1(slot.p);

			if (!quantity) {
				quantity = slot.p->baseclass.vfptr->get_item_count_2(slot.p);
			}

			return quantity;
		}

	private:
		void* const CWvsContext;
		ZArray<ZRef<GW_ItemSlotBase>>* inventories;
		ZRef<GW_ItemSlotBase>* equip;
		typedef ZRef<CharacterData>* (__fastcall* CWvsContext__GetCharacterData_t)(void* ecx, void* edx, ZRef<CharacterData>* result);
		CWvsContext__GetCharacterData_t CWvsContext__GetCharacterData;
		typedef unsigned int(__fastcall* TSecType__GetData_t)(void* lpvEcx, void* lpvEdx);
		TSecType__GetData_t TSecType__GetData;
	};
}
