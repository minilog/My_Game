#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"
#include "Camera.h"
#include "GameLog.h"

class DanNo1 : public DoiTuong
{
public:
	DanNo1() 
		:DoiTuong(Vec2(), Vec2(), 8, 8)
	{
		mLoaiDoiTuong = eLDT_DanNo1;
		LoadHinhAnhVao();

		mTrangThai = eTTDan_DaBiPhaHuy;
	}

	void CapNhat(float in_tg)
	{
		// cập nhật hiệu ứng
		if (mTGDem_NoTung <= mTG_NoTung)
		{
			mTGDem_NoTung += in_tg;
			mHH_HieuUngNoTung->CapNhat(in_tg);
		}

		// nếu đạn đã bị phá hủy -> ko cần Cập Nhật
		if (mTrangThai == eTTDan_DaBiPhaHuy)
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
			mHH_HieuUngNoTung->set_DoDoi(in_DoDoi);
			mHH_HieuUngNoTung->Ve();
		}

		// nếu đã bị phá hủy -> ko cần phải Vẽ ra
		if (mTrangThai == eTTDan_DaBiPhaHuy)
		{
			return;
		}
		mHH_Dan->set_ToaDo(mToaDo);
		mHH_Dan->set_DoDoi(in_DoDoi);
		mHH_Dan->Ve();
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
		// nếu đã bị phá hủy -> ko cần phải xét va chạm
		if (mTrangThai == eTTDan_DaBiPhaHuy)
		{
			return;
		}

		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
			{
				mTrangThai = eTTDan_DaBiPhaHuy;
				mTGDem_NoTung = 0.0f;
				// set tọa độ hiệu ứng nổ tung 
				mHH_HieuUngNoTung->set_ToaDo(mToaDo);
				mHH_HieuUngNoTung->Remake();
			}
		}

	}
	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc)
	{
		mToaDo = in_ToaDo;
		mVanToc = in_VanToc;
		mTrangThai = eTTDan_DangTonTai;
	}

private:
	HoatHinh *mHH_Dan;
	HoatHinh *mHH_HieuUngNoTung;

	const float mTG_NoTung = 0.08f * 6;
	float mTGDem_NoTung = mTG_NoTung + 0.1f;

	eTrangThai mTrangThai;

	void LoadHinhAnhVao();

public:
	~DanNo1()
	{
		if (mHH_Dan)
			delete mHH_Dan;
		
		if (mHH_HieuUngNoTung)
			delete mHH_HieuUngNoTung;
	}
};

