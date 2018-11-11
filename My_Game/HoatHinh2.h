#pragma once

#include "HinhAnh.h"
#include <vector>

class HoatHinh2
{
public:
	HoatHinh2(std::vector<HinhAnh*> in_DSHinhAnh, float in_ThoiGianChuyenHinhAnh);
	~HoatHinh2();
	void CapNhat(float in_tg);
	void set_ToaDo(const Vec2& in_ToaDo)
	{
		mHinhAnhHienTai->set_ToaDo(in_ToaDo);
	}
	void set_DoDoi(const Vec2& in_DoDoi)
	{
		mHinhAnhHienTai->set_DoDoi(in_DoDoi);
	}
	void Ve();
private:
	std::vector<HinhAnh*> mDSHinhAnh;
	HinhAnh	*mHinhAnhHienTai;
	float mThoiGianThayDoi;
	float mThoiGianHienTai = 0.0f;
	int mViTriHienTai = 0;
};

