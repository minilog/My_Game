#pragma once

#include "HinhAnh.h"
#include <vector>
#include "KieuDuLieu.h"

using namespace std;

class HoatHinh : public HinhAnh
{
public:
	HoatHinh(const char* in_DuongDan, const std::vector<ThongTinFrame>& in_DSThongTinFrame, D3DCOLOR in_Color = NULL);
	~HoatHinh() {}
	void CapNhat(float in_tg);
	void Ve(D3DCOLOR in_SubColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Remake(int in_ViTri = 0, float in_Time = 0.0f);
	void Ve(ThongTinFrame a, D3DCOLOR in_SubColor = D3DCOLOR_ARGB(255, 255, 255, 255));

	int get_ViTri() const;
	float get_ThoiGian() const;

	ThongTinFrame get_ThongTinFrameHienTai()
	{
		return mThongTinFrameHienTai;
	}

private:
	std::vector<ThongTinFrame> mDSThongTinFrame;
	ThongTinFrame mThongTinFrameHienTai;
	int mViTriFrame;
	float mThoiGianDem;
};

