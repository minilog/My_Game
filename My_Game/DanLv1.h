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

		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 8, 6, 999.9f, HCN(113, 121, 535, 541)));
		mHoatHinh = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

		//lDSTTFrame.clear();
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 12, 12, 1.0f, HCN(127, 139, 532, 544)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 1.0f, HCN(144, 157, 531, 544)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 16, 1.0f, HCN(162, 178, 530, 545)));
		//mHoatHinhBiPhaHuy = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

		//mTG_PhaHuy = 0.0f;
		//for (int i = 0; i < (int)lDSTTFrame.size(); i++)
		//{
		//	mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
		//}
		
		mBiPhaHuy = true;
	}
	~DanLv1()
	{
		if (mHoatHinh)
			delete mHoatHinh;
		//if (mHoatHinhBiPhaHuy)
		//	delete mHoatHinhBiPhaHuy;
	}

	void CapNhat(float in_tg)
	{
		if (mBiPhaHuy)
		{
			return;
		}

		mTG_DemTonTai += in_tg;

		if (mTG_DemTonTai > mTG_TonTai)
		{
			mBiPhaHuy = true;
		}

		if (!mBiPhaHuy)
		{
			mToaDo.x += mVanToc.x * in_tg;
			mToaDo.y += mVanToc.y * in_tg;
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (!mBiPhaHuy)
		{
			mHoatHinh->set_ToaDo(mToaDo);
			mHoatHinh->set_DoDoi(in_DoDoi);
			mHoatHinh->Ve();
		}
	} // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}

	void Remake()
	{
		mBiPhaHuy = false;
		mTG_DemTonTai = 0.0f;
		//mTG_DemPhaHuy = 0.0f;
	}

	bool get_BiPhaHuy()
	{
		return mBiPhaHuy;
	}

private:
	HoatHinh *mHoatHinh;
	HoatHinh *mHoatHinhBiPhaHuy;

	bool mBiPhaHuy;

	float mTG_TonTai = 0.5f;
	float mTG_DemTonTai = 0.0f;

	//float mTG_PhaHuy;
	//float mTG_DemPhaHuy = 0.0f;

public :
	static constexpr float mVanTocDan = 250.0f;
};

