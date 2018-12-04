#pragma once

#include "HinhAnh.h"
#include <vector>
#include "KieuDuLieu.h"

using namespace std;

class HoatHinh
{
public:
	HoatHinh(const std::vector<ThongTinFrame>& in_DSThongTinFrame);
	~HoatHinh() {}

// FUNCTION
	void CapNhat(float in_tg);
	void Ve(HinhAnh *in_HinhAnh, bool in_LatHinh, const Vec2& in_ToaDo, const Vec2& in_DoDoi,
		const D3DCOLOR &in_SubColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Remake(int in_ViTri = 0, float in_Time = 0.0f);
	//void Ve(HinhAnh *in_HinhAnh, bool in_LatHinh, const Vec2& in_ToaDo, const Vec2& in_DoDoi,
	//	const ThongTinFrame& in_TTFrame,
	//	const D3DCOLOR &in_SubColor = D3DCOLOR_ARGB(255, 255, 255, 255));

// INFORMATION
private:
	std::vector<ThongTinFrame> mDSThongTinFrame;
	int mViTriFrame;
	float mThoiGianDem;

// SUB-FUNCTION
public:
	int get_ViTriFrame() const { return mViTriFrame; }
	float get_ThoiGianDem() const { return mThoiGianDem; }
	ThongTinFrame get_TTFrameHienTai() const { return mDSThongTinFrame[mViTriFrame]; }
};

