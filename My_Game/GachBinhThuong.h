#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"

class GachBinhThuong : public DoiTuong
{
public:
	GachBinhThuong(D3DXVECTOR3 in_ToaDo) : 
		DoiTuong(in_ToaDo, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 32) 
	{
		mHoatHinh = new HoatHinh("Resources/normalbrick.png", 1, 1, 1, 1.0f);
	}

	void CapNhat(float in_tg)
	{
		mHoatHinh->ThietLapToaDo(mToaDo);
		mHoatHinh->CapNhat(in_tg);
	}
	void Ve(D3DXVECTOR2 in_DoDoi)
	{
		mHoatHinh->ThietLapDoDoi(in_DoDoi);
		mHoatHinh->Ve();
	}
private:
	HoatHinh *mHoatHinh;
};

