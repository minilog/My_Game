#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "KieuDuLieu.h"

class GachBinhThuong : public DoiTuong
{
public:
	GachBinhThuong(Vec2 in_ToaDo) : 
		DoiTuong(in_ToaDo, Vec2(), 32, 32) 
	{
		mHoatHinh = new HoatHinh("Resources/normalbrick.png", 1, 1, 1, 1.0f);
		mHoatHinhBiPhaHuy = new HoatHinh("Resources/No.png", 1, 1, 1, 0.5f);
		mHoatHinhBiPhaHuy->set_TiLe(Vec2(0.045f, 0.045f));
		DoiTuong::mLoaiDoiTuong = eLDT_VienGachBinhThuong;
	}

	void CapNhat(float in_tg)
	{
		if (mBiPhaHuy == false)
		{
			mHoatHinh->CapNhat(in_tg);
		}
		else if (mThoiGianDem < mThoiGianHienThiNo)
		{
			mThoiGianDem += in_tg;
			mHoatHinhBiPhaHuy->CapNhat(in_tg);
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mBiPhaHuy == false)
		{
			mHoatHinh->set_ToaDo(mToaDo);
			mHoatHinh->set_DoDoi(in_DoDoi);
			mHoatHinh->Ve();
		}
		else if(mThoiGianDem < mThoiGianHienThiNo) 
		{
			mHoatHinhBiPhaHuy->set_ToaDo(mToaDo);
			mHoatHinhBiPhaHuy->set_DoDoi(in_DoDoi);
			mHoatHinhBiPhaHuy->Ve();
		}
	}

	void XuLyVaCham(const DoiTuong* in_DoiTuong) 
	{
		HinhChuNhat lHCNGioiHanGBT = get_HCNGioiHan();

		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanGBT, in_DoiTuong->get_HCNGioiHan());
		ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
		if (lKQVC.eKQVC_DaVaCham == true)
		{
			switch (in_DoiTuong->get_LoaiDoiTuong())
			{
			case eLDT_Mario:
				if (lPVC == ePVC_Duoi)
				{
					mBiPhaHuy = true;
				}
				break;
			}
		}

	}

	bool get_BiPhaHuy() const
	{
		return mBiPhaHuy;
	}
private:
	HoatHinh *mHoatHinh;
	HoatHinh *mHoatHinhBiPhaHuy;
	float mThoiGianHienThiNo = 0.2f;
	float mThoiGianDem = 0.0f;
	bool mBiPhaHuy = false;
};

