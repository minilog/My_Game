#include "HoatHinh.h"

HoatHinh::HoatHinh(const char * in_DuongDan, int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi)
	:HinhAnh(in_DuongDan)
{
	//GAMELOG("HoatHinh: TongKhuonHinh: %d, SoHang: %d, SoCot: %d, ThoiGianThayDoi: %f" in_TongKhuonHinh, in_SoHang, in_SoCot, in_ThoiGianThayDoi)
	mTongKhuonHinh = in_TongKhuonHinh;
	mSoHang = in_SoHang;
	mSoCot = in_SoCot;
	//mChieuCao, mChieuRong bây giờ là của khuôn hình Hoạt Hình
	HinhAnh::mChieuRong /= mSoCot;
	HinhAnh::mChieuCao /= mSoHang;

	mHangHienTai = 0;
	mCotHienTai = 0;

	mThoiGianThayDoi = in_ThoiGianThayDoi;
	mTongThoiGianHienTai = 0.0f;

	// chỉnh hình chữ nhật để đúng khuôn Hình được vẽ ra
	HinhAnh::mHCN = HinhChuNhat(
		0,
		HinhAnh::mChieuRong,
		0,
		HinhAnh::mChieuCao);
}

void HoatHinh::CapNhat(float in_tg)
{
	if (mTongKhuonHinh <= 1)
	{
		return;
	}

	mTongThoiGianHienTai += in_tg;

	if (mTongThoiGianHienTai < mThoiGianThayDoi)
	{
		return;
	}
	else
	{
		mTongThoiGianHienTai -= mThoiGianThayDoi;
		mCotHienTai++;

		if (mCotHienTai >= mSoCot)
		{
			mCotHienTai = 0;
			mHangHienTai++;

			if (mHangHienTai >= mSoHang)
			{
				mHangHienTai = 0;
			}
		}

		HinhAnh::mHCN = HinhChuNhat(
			mCotHienTai * HinhAnh::mChieuRong,
			mCotHienTai * HinhAnh::mChieuRong + HinhAnh::mChieuRong,
			mHangHienTai * HinhAnh::mChieuCao,
			mHangHienTai * HinhAnh::mChieuCao + HinhAnh::mChieuCao);
	}
}

void HoatHinh::Ve()
{
	HinhAnh::Ve();
}
