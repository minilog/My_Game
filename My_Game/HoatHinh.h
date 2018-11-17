#pragma once

#include "HinhAnh.h"
#include <vector>
#include "KieuDuLieu.h"

using namespace std;

class HoatHinh : public HinhAnh
{
public:
	HoatHinh(const char* in_DuongDan, const std::vector<ThongTinFrame>& in_DSThongTinFrame);
	~HoatHinh() {}
	void CapNhat(float in_tg);
	void Ve();
	void Remake();

private:
	std::vector<ThongTinFrame> mDSThongTinFrame;
	ThongTinFrame mThongTinFrameHienTai;
	int mViTriFrame;
	float mThoiGianDem;
};

