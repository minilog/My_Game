#pragma once

#include "HinhAnh.h"
#include <vector>
#include "KieuDuLieu.h"

using namespace std;

class HoatHinh : public HinhAnh
{
public:
	HoatHinh(const char* in_DuongDan, const std::vector<ThongTinFrame>& in_DSThongTinFrame,
		float in_ThoiGianThayDoi);
	~HoatHinh() {}
	void CapNhat(float in_tg);
	void Ve();

private:
	std::vector<ThongTinFrame> mDSThongTinFrame;
	ThongTinFrame mThongTinFrameHienTai;
	int mViTriFrame;
	float mThoiGianThayDoi;
	float mThoiGianDem;
};

