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
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.024f, HCN(144, 154, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.024f, HCN(144, 157, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.024f, HCN(144, 160, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 163, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 166, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(144, 169, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(185, 212, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(232, 256, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(273, 301, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(312, 340, 812, 842)));
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(349, 377, 812, 842)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 30, 0.01f, HCN(349, 377, 812, 842)));
		mHoatHinh = new HoatHinh("Resources_X3/XMan/XMan - Copy.png", lDSTTFrame, D3DCOLOR_XRGB(255, 255, 255));
		mHoatHinh->set_TiLe(Vec2(1.0f, 1.3f));

		mTG_TonTai = 0.0f;
		for (int i = 0; i < (int)lDSTTFrame.size(); i++)
		{
			mTG_TonTai += lDSTTFrame[i].ThoiGian;
		}

		mHoatHinh->set_GocXoayHinh(180.0f);

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
			if (!mLatHinh)
			{
				mHoatHinh->set_GocXoayHinh(180.0f);
				mHoatHinh->set_LatTheoChieuDoc(mLatHinh);
			}
			else
			{
				mHoatHinh->set_GocXoayHinh(181.0f);
				mHoatHinh->set_LatTheoChieuDoc(mLatHinh);
			}
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

	void BienMat()
	{
		mBienMat = true;
	}

	void LatHinh(bool a)
	{
		mLatHinh = a;
	}

private:
	HoatHinh *mHoatHinh;

	float mTG_TonTai;
	float mTG_DemTonTai = 0.0f;
	bool mBienMat = true;
	bool mLatHinh = false;
};

