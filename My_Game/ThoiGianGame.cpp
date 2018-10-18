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

float ThoiGianGame::fThoiGianDemDuoc()
{
	QueryPerformanceCounter(&mKetThuc);
	LARGE_INTEGER mDelta;
	mDelta.QuadPart = mKetThuc.QuadPart - mBatDau.QuadPart;

	return ((float)mDelta.QuadPart / mTyLeThoiGian.QuadPart);
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

ThoiGianGame * ThoiGianGame::tggTruongHop()
{
	if (!mTruongHop)
	{
		mTruongHop = new ThoiGianGame();
	}
	return mTruongHop;
}