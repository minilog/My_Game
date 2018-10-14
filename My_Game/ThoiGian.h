#pragma once
#ifndef __Thoi_Gian__
#define	__Thoi_Gian__

#include <Windows.h>

class ThoiGian
{
public:
	static ThoiGian* LayTruongHop();
	void BatDauDem();
	float NhanThoiGianDemDuoc();
private:
	ThoiGian() = default;

private:
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
	static ThoiGian *mTruongHop;
};

#endif