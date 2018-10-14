#include "ThoiGian.h"

ThoiGian* ThoiGian::mTruongHop = NULL;

ThoiGian::ThoiGian()
{
}

ThoiGian* ThoiGian::LayTruongHop()
{
	if (!mTruongHop)
	{
		mTruongHop = new ThoiGian();
	}

	return mTruongHop;
}

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