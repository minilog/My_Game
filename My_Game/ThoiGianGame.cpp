#include "ThoiGianGame.h"

ThoiGianGame* ThoiGianGame::mTruongHop = NULL;

void ThoiGianGame::BatDauDem()
{
	if (!QueryPerformanceFrequency(&mTyLeThoiGian))
	{
		return;
	}

	QueryPerformanceCounter(&mBatDau);
}

float ThoiGianGame::NhanThoiGianDemDuoc()
{
	QueryPerformanceCounter(&mKetThuc);
	LARGE_INTEGER mDelta;
	mDelta.QuadPart = mKetThuc.QuadPart - mBatDau.QuadPart;

	return ((float)mDelta.QuadPart / mTyLeThoiGian.QuadPart);
}