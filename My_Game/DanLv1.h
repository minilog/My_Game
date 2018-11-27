#pragma once
#include "DoiTuong.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>

class DanLv1 :
	public DoiTuong
{
public:
	DanLv1(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2())
		: 
		DoiTuong(in_ToaDo, in_VanToc, 0, 0)
	{
		mLoaiDoiTuong = eLDT_DanLv1;

		LoadHinhAnhVao();

		mHH_HienTai = mHH_DangTonTai;

		mTrangThai = eTT_DaBiPhaHuy;
	}
	~DanLv1()
	{
		if (mHH_DangTonTai)
			delete mHH_DangTonTai;
		if (mHH_DangTanBien)
			delete mHH_DangTanBien;
	}

	void CapNhat(float in_tg)
	{
		if (mTrangThai == eTT_DaBiPhaHuy)
		{
			return;
		}

		if (mTrangThai == eTT_DangTonTai)
		{
			mTG_DemTonTai += in_tg;
			mToaDo.x += mVanToc.x * in_tg;
			mToaDo.y += mVanToc.y * in_tg;

			if (mTG_DemTonTai > mTG_TonTai)
			{
				DangTanBien();
			}
		}

		if (mTrangThai == eTT_DangTanBien)
		{
			mHH_HienTai->CapNhat(in_tg);
			mTG_DemPhaHuy += in_tg;
			
			if (mTG_DemPhaHuy > mTG_PhaHuy)
			{
				DaBiPhaHuy();
			}
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (mTrangThai != eTT_DaBiPhaHuy)
		{
			mHH_HienTai->set_ToaDo(mToaDo);
			mHH_HienTai->set_DoDoi(in_DoDoi);
			mHH_HienTai->Ve();
		}
	} // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}

	void Remake()
	{
		DangTonTai();
	}

	eTrangThai get_BiPhaHuy()
	{
		return mTrangThai;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_HienTai;

	float mTG_TonTai = 0.5f;
	float mTG_DemTonTai = 0.0f;

	float mTG_PhaHuy; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;

	eTrangThai mTrangThai;

	void LoadHinhAnhVao()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 8, 6, 999.9f, HCN(113, 121, 535, 541)));
		mHH_DangTonTai = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 12, 12, 0.1f, HCN(127, 139, 532, 544)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 0.1f, HCN(144, 157, 531, 544)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 16, 0.1f, HCN(162, 178, 530, 545)));
		mHH_DangTanBien = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

		mTG_PhaHuy = 0.0f;
		for (int i = 0; i < (int)lDSTTFrame.size(); i++)
		{
			mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
		}
	}

	void DangTanBien()
	{
		mTG_DemPhaHuy = 0.0f;
		mTrangThai = eTT_DangTanBien;
		mHH_HienTai = mHH_DangTanBien;
		mHH_HienTai->Remake();
	}

	void DangTonTai()
	{
		mTG_DemTonTai = 0.0f;
		mTrangThai = eTT_DangTonTai;
		mHH_HienTai = mHH_DangTonTai;
		mHH_HienTai->Remake();
	}

	void DaBiPhaHuy()
	{
		mTrangThai = eTT_DaBiPhaHuy;
	}

public :
	static constexpr float mVanTocDan = 250.0f;
};

