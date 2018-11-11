#pragma once

#include "DoiTuong.h"
#include "HoatHinh2.h"
#include <vector>

class GachVang : public DoiTuong
{
public:
	GachVang(Vec2 in_ToaDo) 
		: 
		DoiTuong(in_ToaDo, Vec2(), 32, 32) 
	{
		std::vector<HinhAnh*> lDSHinhAnh;

		HinhAnh *lHA = new HinhAnh("Resources/goldbrick.png");
		lHA->set_ChieuRong(32);
		lHA->set_ChieuCao(32);
		lHA->set_HCN(HinhChuNhat(
			0, 32, 0, 32));
		lDSHinhAnh.push_back(lHA);

		HinhAnh *lHA2 = new HinhAnh("Resources/goldbrick.png");
		lHA2->set_ChieuRong(32);
		lHA2->set_ChieuCao(32);
		lHA2->set_HCN(HinhChuNhat(
			32, 64, 0, 32));
		lDSHinhAnh.push_back(lHA2);

		mHoatHinh2 = new HoatHinh2(lDSHinhAnh, 1.0f);

		DoiTuong::mLoaiDoiTuong = eLDT_VienGachVang;
	}

	void CapNhat(float in_tg)
	{
		mHoatHinh2->CapNhat(in_tg);
	}

	void Ve(const Vec2& in_DoDoi)
	{
		mHoatHinh2->set_ToaDo(mToaDo);
		mHoatHinh2->set_DoDoi(in_DoDoi);
		mHoatHinh2->Ve();
	}

	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
private:
	HoatHinh2 *mHoatHinh2;
};

