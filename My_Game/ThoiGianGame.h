#pragma once

#include <Windows.h>

class ThoiGianGame
{
public:
	static ThoiGianGame* NhanTruongHop();
	void BatDauDem();
	float NhanThoiGianDemDuoc();

private:
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
	static ThoiGianGame *mTruongHop;
};
