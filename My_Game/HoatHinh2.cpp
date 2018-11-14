#include "HoatHinh2.h"

HoatHinh2::HoatHinh2(std::vector<HinhAnh*> in_DSHinhAnh, float in_ThoiGianChuyenHinhAnh)
{
	for (auto lHinhAnh : in_DSHinhAnh)
	{
		mDSHinhAnh.push_back(lHinhAnh);
	}

	mThoiGianThayDoi = in_ThoiGianChuyenHinhAnh;

	mHinhAnhHienTai = mDSHinhAnh[0];
	mViTriHienTai = 0;
}

HoatHinh2::~HoatHinh2()
{
	for (int i = 0; i < int(mDSHinhAnh.size()); i++)
	{
		if (mDSHinhAnh[i])
		{
			delete mDSHinhAnh[i];
		}
	}
	mDSHinhAnh.clear();
}

void HoatHinh2::CapNhat(float in_tg)
{
	if (mDSHinhAnh.size() <= 0)
	{
		return;
	}

	mThoiGianHienTai += in_tg;

	if (mThoiGianHienTai < mThoiGianThayDoi)
	{
		return;
	}
	else
	{
		mThoiGianHienTai -= mThoiGianThayDoi;

		mViTriHienTai++;
		if (mViTriHienTai >= int(mDSHinhAnh.size()))
		{
			mViTriHienTai = 0;
		}

		mHinhAnhHienTai = mDSHinhAnh[mViTriHienTai];
	}
}

void HoatHinh2::Ve()
{
	mHinhAnhHienTai->Ve();
}
