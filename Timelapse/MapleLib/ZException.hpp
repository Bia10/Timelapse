#pragma once

#include "native.hpp"

	class ZException
	{
	public:
		ZException(HRESULT hr)
			: m_hr(hr)
		{

		}

		HRESULT Error() const
		{
			return this->m_hr;
		}

	private:
		const HRESULT m_hr;
	};

	static_assert_size(sizeof(ZException), 0x04);