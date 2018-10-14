#pragma once

#include <Windows.h>

class ThoiGian
{
public:
	static ThoiGian* NhanTruongHop()
	{
		if (!mTruongHop)
		{
			mTruongHop = new ThoiGian();
		}
		return mTruongHop;
	}
	void BatDauDem();
	float NhanThoiGianDemDuoc();
private:
	ThoiGian() = default;

private:
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
	static ThoiGian *mTruongHop;
};
