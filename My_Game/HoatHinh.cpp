#include "HoatHinh.h"

void HoatHinh::KhoiTaoVoiHoatHinh(int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi)
{
	//GAMELOG("HoatHinh: TongKhuonHinh: %d, SoHang: %d, SoCot: %d, ThoiGianThayDoi: %f" in_TongKhuonHinh, in_SoHang, in_SoCot, in_ThoiGianThayDoi)
	mTongSoKhuonHinh = in_TongKhuonHinh;
	mSoHang = in_SoHang;
	mSoCot = in_SoCot;
	//mChieuCao, mChieuRong bây giờ là của khuôn hình Hoạt Hình
	HinhAnh::mChieuRong /= mSoHang;
	HinhAnh::mChieuCao /= mSoCot;

	mThoiGianThayDoi = in_ThoiGianThayDoi;
	mHangHienTai = 0;
	mCotHienTai = 0;
	mTongThoiGianHienTai = 0.0f;

	// chỉnh hình chữ nhật để đúng khuôn Hình được vẽ ra
	HinhAnh::mHCN.left = 0;
	HinhAnh::mHCN.right = HinhAnh::mChieuRong;
	HinhAnh::mHCN.top = 0;
	HinhAnh::mHCN.bottom = HinhAnh::mChieuCao;
}

void HoatHinh::CapNhat(float in_tg)
{
	if (mTongSoKhuonHinh <= 1)
	{
		return;
	}

	if (mTongThoiGianHienTai < mThoiGianThayDoi)
	{
		mTongThoiGianHienTai += in_tg;
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

		HinhAnh::mHCN.left = mCotHienTai * HinhAnh::mChieuRong;
		HinhAnh::mHCN.right = HinhAnh::mHCN.left + HinhAnh::mChieuRong;
		HinhAnh::mHCN.top = mHangHienTai * HinhAnh::mChieuCao;
		HinhAnh::mHCN.bottom = HinhAnh::mHCN.top + HinhAnh::mChieuCao;
	}
}
