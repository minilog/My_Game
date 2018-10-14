#include "ThoiGian.h"

ThoiGian* ThoiGian::mTruongHop = NULL;

void ThoiGian::BatDauDem()
{
	if (!QueryPerformanceFrequency(&mTyLeThoiGian))
	{
		return;
	}

	QueryPerformanceCounter(&mBatDau);
}

float ThoiGian::NhanThoiGianDemDuoc()
{
	QueryPerformanceCounter(&mKetThuc);
	LARGE_INTEGER mDelta;
	mDelta.QuadPart = mKetThuc.QuadPart - mBatDau.QuadPart;

	return ((float)mDelta.QuadPart / mTyLeThoiGian.QuadPart);
}