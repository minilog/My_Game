#include "HoatHinh.h"

HoatHinh::HoatHinh(const char * in_DuongDan, const std::vector<ThongTinFrame>& in_DSThongTinFrame)
	:HinhAnh(in_DuongDan),
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

void HoatHinh::Ve()
{
	HinhAnh::Ve();
}

void HoatHinh::Remake(int in_ViTri, float in_Time)
{
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
