#pragma once
#include <algorithm>
#include <functional>
#include "MapleLib/ZRefCounted.hpp"
#include "MapleLib/TSingleton.hpp"
#include "MapleLib/ZRef.hpp"
#include "MapleLib/ZList.hpp"
#include "MapleLib/ZMap.hpp"
#include "MapleLib/TSecType.hpp"
#include "space_objects.hpp"

namespace Timelapse
{
	struct DROP : public ZRefCounted {
		struct SECPOINT {
			TSecType<long> y;
			TSecType<long> x;
		};
		SECPOINT pt1;				// 0x00
		void* posList;				// 0x18
		char nEnterType;			// 0x1C
		char bReal;					// 0x1D
		//0000001E                 db ? ; undefined
		//0000001F                 db ? ; undefined
		unsigned int dwId;			// 0x20
		unsigned int dwOwnerID;		// 0x24
		unsigned int dwSourceID;	// 0x28
		int nOwnType;				// 0x2C
		int bIsMoney;				// 0x30
		int nInfo;					// 0x34
		void* pLayer;				// 0x38
		void* pvec;					// 0x3C
		int tCreateTime;			// 0x40
		int tLeaveTime;				// 0x44
		int nState;					// 0x48
		int tTickTime;				// 0x4C
		int tEndParabolicMotion;	// 0x50
		int tLastTryPickUp;			// 0x54
		unsigned int dwPickupID;	// 0x58
		//0000005C                 db ? ; undefined
		//0000005D                 db ? ; undefined
		//0000005E                 db ? ; undefined
		//0000005F                 db ? ; undefined
		long double fAngle;			// 0x60
		SECPOINT pt2;				// 0x68
		_FILETIME m_dateExpire;		// 0x80
		int bByPet;					// 0x88
		//0000008C                 db ? ; undefined
		//0000008D                 db ? ; undefined
		//0000008E                 db ? ; undefined
		//0000008F                 db ? ; undefined
		//00000090 DROP            ends
	};

	const unsigned int TSingleton_CDropPool = 0xBED6AC; // 8B 35 ? ? ? ? ? FF 50 ? ? 8B CE E8 ? ? ? ? B8
	class CDropPool : public TSingleton<CDropPool, TSingleton_CDropPool> {
		virtual ~CDropPool() = 0;
	public:
		static int size() {
			if (!IsInitialized())
				return 0;

			return GetInstance()->m_lDrop.GetCount();
		}

		static void try_pick_up_drop(POINT* pt_user) {
			//return CDropPool__TryPickUpDrop(this, nullptr, pt_user);
		}

		bool get_drop(POINT* pt_drop, unsigned int number) {
			if (pt_drop != nullptr && this->m_lDrop.GetCount() > number) {
				this->m_lDrop.EnumerateList([&](ZRef<DROP>* drop) -> bool {
					if (drop->p->nInfo != 0) {
						pt_drop->x = drop->p->pt2.x.GetData();
						pt_drop->y = drop->p->pt2.y.GetData();

						if (CWvsPhysicalSpace2D::GetInstance()->IsInRect(*pt_drop)) {
							if (number-- == 0) return true;
						}
					}
					return false;
				});
			}
			return (number == -1);
		}

		bool get_random_drop(POINT* pt_drop) {
			if (pt_drop != nullptr) {
				this->m_lDrop.EnumerateList([&](ZRef<DROP>* drop) -> bool {
					if (drop->p->nInfo != 0) {
						pt_drop->x = drop->p->pt2.x.GetData();
						pt_drop->y = drop->p->pt2.y.GetData();

						if (CWvsPhysicalSpace2D::GetInstance()->IsInRect(*pt_drop)) return true;
					}
					return false;
				});
			}
			return (pt_drop && pt_drop->x != 0 && pt_drop->y != 0);
		}

		bool get_closest_drop(POINT* pt_drop, POINT pt_user) {
			if (pt_drop != nullptr) {
				POINT pt_min;
				memset(&pt_min, 0, sizeof(POINT));

				this->m_lDrop.EnumerateList([&, this](ZRef<DROP>* drop) -> bool {
					if (drop->p->nInfo != 0) {
						POINT pt_temp;
						pt_temp.x = drop->p->pt2.x.GetData();
						pt_temp.y = drop->p->pt2.y.GetData();

						POINT pt_temp_min = std::min<POINT>(pt_min, pt_temp, [&](const POINT& pt1, const POINT& pt2) {
							return (get_drop_distance(pt1, pt_user) < get_drop_distance(pt2, pt_user));
						});

						if (CWvsPhysicalSpace2D::GetInstance()->IsInRect(pt_temp_min)) {
							pt_min.x = pt_temp_min.x;
							pt_min.y = pt_temp_min.y;
						}
					}
					return false;
				});

				if (pt_min.x != 0 || pt_min.y != 0) {
					pt_drop->x = pt_min.x;
					pt_drop->y = pt_min.y;
					return true;
				}
			}
			return false;
		}

	private:
		double get_drop_distance(POINT pt_drop, POINT pt_user) const {
			const std::function<int(int)> square = [](int x) {
				return x * x;
			};
			const int squared = square(pt_drop.x - pt_user.x) + square(pt_drop.y - pt_user.y);

			return std::sqrt(static_cast<long double>(squared));
		}

		int m_tLastExplodeSound;											// 0x04
		ZMap<unsigned long, ZRef<DROP>, unsigned long> m_mDrop;				// 0x08
		ZList<ZRef<DROP>> m_lDrop;											// 0x20
		ZList<ZRef<DROP>> m_lDropPickUpByPet;								// 0x34
		ZMap<unsigned long, POINT, unsigned long> m_mDropPt;				// 0x48
		void* m_pPropMoneyIcon;												// 0x60
		ZList<POINT> m_lpRecentPickupedItem;								// 0x64
		int m_bRecentPickupedItemCheck;										// 0x78
	};

	static_assert_size(sizeof(DROP), 0xA0);
	static_assert_size(sizeof(CDropPool), 0x7C);
}