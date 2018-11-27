#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>

class HieuUngLuot :
	public DoiTuong
{
public:
	HieuUngLuot()
		:
		DoiTuong(Vec2(), Vec2(), 0, 0)
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(144, 154, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(144, 160, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(144, 176, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(185, 217, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(232, 260, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(273, 301, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(312, 340, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(349, 377, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.08f, HCN(349, 377, 812, 842)));
		mHoatHinh = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame, D3DCOLOR_XRGB(0, 128, 128));

		mTG_TonTai = 0.0f;
		for (int i = 0; i < (int)lDSTTFrame.size(); i++)
		{
			mTG_TonTai += lDSTTFrame[i].ThoiGian;
		}

		mHoatHinh->set_GocXoayHinh(-90.0f);

		mBienMat = true;
		mTG_DemTonTai = 999.9f;
	}

	~HieuUngLuot()
	{
		delete mHoatHinh;
	}

	void CapNhat(float in_tg)
	{
		if (!mBienMat)
		{
			mTG_DemTonTai += in_tg;
			mHoatHinh->CapNhat(in_tg);
		}
		if (mTG_DemTonTai > mTG_TonTai && !mBienMat)
		{
			mBienMat = true;
		}
	}
	void Ve(const Vec2& in_DoDoi)
	{
		if (!mBienMat)
		{
			mHoatHinh->set_ToaDo(mToaDo);
			mHoatHinh->set_DoDoi(in_DoDoi);
			mHoatHinh->Ve();
		}
	} // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{
	}

	void Remake()
	{
		mTG_DemTonTai = 0.0f;
		mBienMat = false;
		mHoatHinh->Remake();
	}

	bool get_BienMat()
	{
		return mBienMat;
	}

private:
	HoatHinh *mHoatHinh;

	float mTG_TonTai;
	float mTG_DemTonTai = 0.0f;
	bool mBienMat = true;

};

