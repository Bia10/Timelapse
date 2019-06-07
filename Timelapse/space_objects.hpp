#pragma once
#include "MapleLib/native.hpp"
#include "MapleLib/TSingleton.hpp"

const unsigned int TSingleton_CWvsPhysicalSpace2D = 0xBEBFA0; // 8B 0D ? ? ? ? 85 C9 74 ? 8B 55 ? 6A 01

namespace Timelapse
{
	class CWvsPhysicalSpace2D : public TSingleton<CWvsPhysicalSpace2D, TSingleton_CWvsPhysicalSpace2D> {
	public:
		explicit CWvsPhysicalSpace2D(const RECT& tag_rect);

	private:
		~CWvsPhysicalSpace2D() = delete;

	public:
		bool IsInRect(POINT pt) const
		{
			return (PtInRect(&this->m_rcMBR, pt) != FALSE);
		}

		void GetTopLeft(POINT* pt) const
		{
			pt->x = m_rcMBR.left;
			pt->y = m_rcMBR.top;
		}

		void GetBoundary(RECT* rc) const
		{
			rc->left = this->m_rcMBR.left;
			rc->top = this->m_rcMBR.top;
			rc->right = this->m_rcMBR.right;
			rc->bottom = this->m_rcMBR.bottom;
		}

	private:
		padding(0x0C);
		RECT m_rcMBR;
	};

	inline CWvsPhysicalSpace2D::CWvsPhysicalSpace2D(const RECT& tag_rect): TSingleton<CWvsPhysicalSpace2D, TSingleton_CWvsPhysicalSpace2D>(), __padding0x0C{}, m_rcMBR(tag_rect)
	{
	}

	static_assert_size(sizeof(CWvsPhysicalSpace2D), 0x1C);
}