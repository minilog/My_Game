#include "HoatHinh.h"

HoatHinh::HoatHinh(const char * in_DuongDan, const std::vector<ThongTinFrame>& in_DSThongTinFrame, D3DCOLOR in_Color)
	:HinhAnh(in_DuongDan, in_Color),
	mThongTinFrameHienTai(Vec2(0.0f, 0.0f), 0, 0, 0.0f),
	mViTriFrame(0),
	mThoiGianDem(0.0f)
{
	for (auto lThongTinFrame : in_DSThongTinFrame)
	{
		mDSThongTinFrame.push_back(lThongTinFrame);
	}

	mThongTinFrameHienTai = mDSThongTinFrame[mViTriFrame];

	HinhAnh::mChieuRong = mThongTinFrameHienTai.ChieuRong;
	HinhAnh::mChieuCao = mThongTinFrameHienTai.ChieuCao;

	if (mThongTinFrameHienTai.Hcn.Trai == 0 &&
		mThongTinFrameHienTai.Hcn.Phai == 0 &&
		mThongTinFrameHienTai.Hcn.Tren == 0 &&
		mThongTinFrameHienTai.Hcn.Duoi == 0)
	{
		HinhAnh::mHCN = HCN(
			int(mThongTinFrameHienTai.ToaDo.x),
			int(mThongTinFrameHienTai.ToaDo.x) + HinhAnh::mChieuRong,
			int(mThongTinFrameHienTai.ToaDo.y),
			int(mThongTinFrameHienTai.ToaDo.y) + HinhAnh::mChieuCao);
	}
	else
	{
		HinhAnh::mHCN = mThongTinFrameHienTai.Hcn;
	}
}

void HoatHinh::CapNhat(float in_tg)
{
	if (mDSThongTinFrame.size() <= 1)
	{
		return;
	}

	mThoiGianDem += in_tg;

	if (mThoiGianDem < mThongTinFrameHienTai.ThoiGian)
	{
		return;
	}
	else
	{
		mThoiGianDem -= mThongTinFrameHienTai.ThoiGian;
		mViTriFrame++;

		if (mViTriFrame >= (int)mDSThongTinFrame.size())
		{
			mViTriFrame = 0;
		}

		mThongTinFrameHienTai = mDSThongTinFrame[mViTriFrame];

		HinhAnh::mChieuRong = mThongTinFrameHienTai.ChieuRong;
		HinhAnh::mChieuCao = mThongTinFrameHienTai.ChieuCao;

		if (mThongTinFrameHienTai.Hcn.Trai == 0 &&
			mThongTinFrameHienTai.Hcn.Phai == 0 &&
			mThongTinFrameHienTai.Hcn.Tren == 0 &&
			mThongTinFrameHienTai.Hcn.Duoi == 0)
		{
			HinhAnh::mHCN = HCN(
				int(mThongTinFrameHienTai.ToaDo.x),
				int(mThongTinFrameHienTai.ToaDo.x) + HinhAnh::mChieuRong,
				int(mThongTinFrameHienTai.ToaDo.y),
				int(mThongTinFrameHienTai.ToaDo.y) + HinhAnh::mChieuCao);
		}
		else
		{
			HinhAnh::mHCN = mThongTinFrameHienTai.Hcn;
		}
	}
}

void HoatHinh::Ve(D3DCOLOR in_SubColor)
{
	HinhAnh::Ve(in_SubColor);
}

void HoatHinh::Remake(int in_ViTri, float in_Time)
{
	if (mDSThongTinFrame.size() <= 1)
		return;

	mThoiGianDem = in_Time;
	mViTriFrame = in_ViTri;
	mThongTinFrameHienTai = mDSThongTinFrame[mViTriFrame];

	HinhAnh::mChieuRong = mThongTinFrameHienTai.ChieuRong;
	HinhAnh::mChieuCao = mThongTinFrameHienTai.ChieuCao;

	if (mThongTinFrameHienTai.Hcn.Trai == 0 &&
		mThongTinFrameHienTai.Hcn.Phai == 0 &&
		mThongTinFrameHienTai.Hcn.Tren == 0 &&
		mThongTinFrameHienTai.Hcn.Duoi == 0)
	{
		HinhAnh::mHCN = HCN(
			int(mThongTinFrameHienTai.ToaDo.x),
			int(mThongTinFrameHienTai.ToaDo.x) + HinhAnh::mChieuRong,
			int(mThongTinFrameHienTai.ToaDo.y),
			int(mThongTinFrameHienTai.ToaDo.y) + HinhAnh::mChieuCao);
	}
	else
	{
		HinhAnh::mHCN = mThongTinFrameHienTai.Hcn;
	}
}

void HoatHinh::Ve(ThongTinFrame a, D3DCOLOR in_SubColor)
{
	HinhAnh::mChieuRong = a.ChieuRong;
	HinhAnh::mChieuCao = a.ChieuCao;

	if (a.Hcn.Trai == 0 &&
		a.Hcn.Phai == 0 &&
		a.Hcn.Tren == 0 &&
		a.Hcn.Duoi == 0)
	{
		HinhAnh::mHCN = HCN(
			int(a.ToaDo.x),
			int(a.ToaDo.x) + HinhAnh::mChieuRong,
			int(a.ToaDo.y),
			int(a.ToaDo.y) + HinhAnh::mChieuCao);
	}
	else
	{
		HinhAnh::mHCN = a.Hcn;
	}

	HoatHinh::Ve(in_SubColor);
}

int HoatHinh::get_ViTri() const
{	
	return mViTriFrame;
}

float HoatHinh::get_ThoiGian() const
{
	return mThoiGianDem;
}
