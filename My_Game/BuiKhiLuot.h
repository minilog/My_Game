#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>

class BuiKhiLuot : public DoiTuong
{
public:
	BuiKhiLuot(const Vec2& in_ToaDo);

	~BuiKhiLuot();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(DoiTuong* in_DoiTuong) 
	{
	}

	void Remake();

	bool get_BienMat()
	{
		return mBienMat;
	}

private:
	HoatHinh *mHoatHinh;

	float mTG_TonTai;
	float mTG_DemTonTai = 0.0f;
	bool mBienMat = true;

};
