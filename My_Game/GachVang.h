#pragma once

#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include <vector>

class GachVang : public DoiTuong
{
public:
	GachVang(Vec2 in_ToaDo) 
		: 
		DoiTuong(in_ToaDo, Vec2(), 32, 32) 
	{
		std::vector<ThongTinFrame> lDSThongTinFrame;

		lDSThongTinFrame.clear();
		lDSThongTinFrame.push_back(ThongTinFrame(Vec2(0.0f, 0.0f), 32, 32));
		lDSThongTinFrame.push_back(ThongTinFrame(Vec2(32.0f, 0.0f), 32, 32));
		mHoatHinh = new HoatHinh("Resources/goldbrick.png", lDSThongTinFrame, 0.5f);

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

