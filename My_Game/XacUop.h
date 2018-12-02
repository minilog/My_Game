#pragma once
#include "DoiTuong.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"
#include "Camera.h"
#include "XMan.h"

class XacUop :
	public DoiTuong
{
public:
	XacUop(const Vec2& in_ToaDo, const Vec2& in_VanToc)
		:
		DoiTuong(in_ToaDo, in_VanToc, 22, 38)
	{
		mLoaiDoiTuong = eLDT_XacUop;
		LoadHinhAnh();
		DungIm();
	}

	void CapNhat(float in_tg) {} // ko dùng 

	void CapNhat(float in_tg, const XMan *in_XMan)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;

		mKhoangCach_XMan = mToaDo.x - in_XMan->get_ToaDo().x;

		mHH_HienTai->CapNhat(in_tg);

		switch (mTrangThai)
		{
		case eTTXacUop_DungIm:
			mTGDem_DungIm += in_tg;
			if (mTGDem_DungIm > TG_DungIm)
			{
				TanCong();
			}

			if (mKhoangCach_XMan < -mKhoangCach_TanCong || mKhoangCach_XMan > mKhoangCach_TanCong)
			{
				DiChuyen();
			}

			if (mKhoangCach_XMan < 0)
			{
				mLatHinh = true;
			}
			else
			{
				mLatHinh = false;
			}

			break;

		case eTTXacUop_DiChuyen:
			// xác định hướng quay mặt

			if (mLatHinh)
			{
				mVanToc.x = VanTocDiChuyen;

			}
			else
			{
				mVanToc.x = -VanTocDiChuyen;
			}

			if (mKhoangCach_XMan > -mKhoangCach_TanCong && mKhoangCach_XMan < mKhoangCach_TanCong)
			{
				TanCong();
			}

			if (mKhoangCach_XMan < 0)
			{
				mLatHinh = true;
			}
			else
			{
				mLatHinh = false;
			}

			break;

		case eTTXacUop_TanCong:
			mTGDem_TanCong += in_tg;
			if (mLatHinh)
			{
				mVanToc.x = 50.0f / 3.2f;

			}
			else
			{
				mVanToc.x = -50.0f / 3.2f;
			}
			if (mTGDem_TanCong > TG_TanCong)
			{
				DungIm();

			}
			break;

		default:
			break;
		}
	}
	void Ve(const Vec2& in_DoDoi) // Độ dời phụ thuộc Camera hiện tại
	{
		mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
		mHH_HienTai->set_ToaDo(mToaDo);
		mHH_HienTai->set_DoDoi(in_DoDoi);
		mHH_HienTai->Ve();
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{

	}

	eTrangThai get_TrangThai() const
	{
		return mTrangThai;
	}


private:
	void DungIm()
	{
		mTrangThai = eTTXacUop_DungIm; // Thông tin Trạng Thái = DungIm
		mHH_HienTai = mHH_DungIm; // Hoạt Hình trỏ đến HH_DungIm
		mHH_HienTai->Remake(); // Hoạt Hình được reset lại
		mTGDem_DungIm = 0.0f;
		mVanToc.x = 0.0f;
	}

	void DiChuyen()
	{
		mTrangThai = eTTXacUop_DiChuyen;
		mHH_HienTai = mHH_DiChuyen;
		mHH_HienTai->Remake();
		//mTGDem_DiChuyen = 0.0f;
	}

	void TanCong()
	{
		mTrangThai = eTTXacUop_TanCong;
		mHH_HienTai = mHH_TanCong;
		mHH_HienTai->Remake();
		mTGDem_TanCong = 0.0f;
	}

	void LoadHinhAnh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 20, 38, 99.9f /* ko care*/, HCN(85, 85 + 22, 4, 4 + 40)));
		mHH_DungIm = new HoatHinh("Resources_X3/Enemies/XacUop.png", lDSTTFrame, D3DCOLOR_XRGB(84, 109, 142));

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 36, 0.1f, HCN(50, 50 + 30, 60, 60 + 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 34, 38, 0.1f, HCN(80, 80 + 30, 58, 58 + 40)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 38, 0.1f, HCN(110,110+30 ,60,60+40 )));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 34, 38, 0.1f, HCN(80, 80 + 30, 58, 58 + 40)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 36, 0.1f, HCN(50, 50 + 30, 60, 60 + 38)));
		mHH_DiChuyen = new HoatHinh("Resources_X3/Enemies/XacUop.png", lDSTTFrame, D3DCOLOR_XRGB(84, 109, 142));

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 38,  0.12f, HCN(3, 3 + 26, 107, 107 + 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26 ,36 , 0.12f, HCN(30,30+34,108,108+36)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32 ,38 , 0.12f, HCN(63, 63+32, 107, 107+36)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 52 ,38 , 0.12f, HCN(95, 95+44, 107, 107+36)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 74 ,38 , 0.12f, HCN(139, 139+54, 107, 107+36)));
		mHH_TanCong = new HoatHinh("Resources_X3/Enemies/XacUop.png", lDSTTFrame, D3DCOLOR_XRGB(84, 109, 142));
	}

	HoatHinh *mHH_DungIm,
		*mHH_DiChuyen,
		*mHH_TanCong;

	HoatHinh *mHH_HienTai;

	bool mLatHinh = false;
	eTrangThai mTrangThai;

	const float TG_DungIm = 0.4f;
	float mTGDem_DungIm = 0.0f;

	//const float TG_DiChuyen = 0.2f;
	//float mTGDem_DiChuyen = 0.0f;
	
	const float TG_TanCong = 0.12f * 5;
	float mTGDem_TanCong = 0.0f;

	float mKhoangCach_XMan;

	const float VanTocDiChuyen = 70.0f;

	float mKhoangCach_TanCong = 50.0f;

public:
	~XacUop() 
	{
		if (mHH_DungIm)
			delete mHH_DungIm;

		if (mHH_DiChuyen)
			delete mHH_DiChuyen;

		if (mHH_TanCong)
			delete mHH_TanCong;
	}
};

