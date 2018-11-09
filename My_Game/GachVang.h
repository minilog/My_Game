#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"

class GachVang : public DoiTuong
{
public:
	GachVang(Vec2 in_ToaDo) : DoiTuong(in_ToaDo, Vec2(), 32, 32) 
	{
		mHoatHinh = new HoatHinh("Resources/goldbrick.png", 2, 1, 2, 1.0f);	
		DoiTuong::mLoaiDoiTuong = eLDT_VienGachVang;
	}

	void CapNhat(float in_tg)
	{
		mHoatHinh->CapNhat(in_tg);
	}

	void Ve(const Vec2& in_DoDoi)
	{
		mHoatHinh->set_ToaDo(mToaDo);
		mHoatHinh->set_DoDoi(in_DoDoi);
		mHoatHinh->Ve();
	}

	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
private:
	HoatHinh *mHoatHinh;
};

