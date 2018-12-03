#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"

class DanNo1 : public DoiTuong
{
public:
	DanNo1() 
		:DoiTuong(Vec2(), Vec2(), 8, 8)
	{
		mLoaiDoiTuong = eLDT_DanNo1;
		mTrangThai = eTT_DanNo1_BienMat;

		LoadThongTinHoatHinh();
	}

// FUNCTION
	void CapNhat(float in_tg)
	{
		// cập nhật hiệu ứng
		if (mTGDem_NoTung <= mTG_NoTung)
		{
			mTGDem_NoTung += in_tg;
			mHH_HieuUngPhatNo->CapNhat(in_tg);
		}

		// nếu đạn đã bị phá hủy -> ko cần Cập Nhật
		if (mTrangThai == eTT_DanNo1_BienMat)
		{
			return;
		}

		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mTGDem_NoTung <= mTG_NoTung)
		{
			mHH_HieuUngPhatNo->Ve(DanNo1::HieuUngPhatNo_png, false, mToaDo_HieuUngNoTung, in_DoDoi);
		}

		// nếu đã bị phá hủy -> ko cần phải Vẽ ra
		if (mTrangThai == eTT_DanNo1_BienMat)
		{
			return;
		}

		mHH_Dan->Ve(DanNo1::DanNo1_png, false, mToaDo, in_DoDoi);
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
		// nếu đã bị phá hủy -> ko cần phải xét va chạm
		if (mTrangThai == eTT_DanNo1_BienMat)
		{
			return;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				mTrangThai = eTT_DanNo1_BienMat;
				mTGDem_NoTung = 0.0f;
				// set tọa độ hiệu ứng nổ tung 
				mToaDo_HieuUngNoTung = mToaDo;
				mHH_HieuUngPhatNo->Remake();
			}
		}

	}
	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc)
	{
		mToaDo = in_ToaDo;
		mVanToc = in_VanToc;
		mTrangThai = eTT_DanNo1_TonTai;
	}

// INFORMATION
private:
	HoatHinh *mHH_Dan;
	HoatHinh *mHH_HieuUngPhatNo;

	const float mTG_NoTung = 0.08f * 6;
	float mTGDem_NoTung = mTG_NoTung + 0.1f;
	Vec2 mToaDo_HieuUngNoTung;

// SUB-FUNCTION
	void LoadThongTinHoatHinh();

// DESTRUCTURE
public:
	~DanNo1()
	{
		if (mHH_Dan)
			delete mHH_Dan;
		
		if (mHH_HieuUngPhatNo)
			delete mHH_HieuUngPhatNo;
	}


// NƠI CHỨA HÌNH ẢNH
public:
	static HinhAnh *HieuUngPhatNo_png;
	static HinhAnh *DanNo1_png;
};

