#pragma once
#include "HinhAnh.h"

class DS_HinhAnh
{
public:
	static DS_HinhAnh* get_TH()
	{
		if (!mTH)
		{
			mTH = new DS_HinhAnh();
		}
		return mTH;
	}
private:
	static DS_HinhAnh *mTH;
	DS_HinhAnh()
	{
		HieuUngPhatNo_png = new HinhAnh("Resources/Enemies/HieuUngPhatNo.png");
		DanNo1_png = new HinhAnh("Resources/Enemies/DanNo1.png", D3DCOLOR_XRGB(255, 0, 255));

		Ech_png = new HinhAnh("Resources/Enemies/Ech.png", D3DCOLOR_XRGB(255, 0, 255));
		Ech_Shining_png = new HinhAnh("Resources/Enemies/Ech_Shining.png", D3DCOLOR_XRGB(255, 0, 255));

		XacUop_png = new HinhAnh("Resources/Enemies/XacUop.png", D3DCOLOR_XRGB(84, 109, 142));

		Bui_png = new HinhAnh("Resources/HieuUng/Bui.png", D3DCOLOR_XRGB(0, 128, 128));
		
		DanLv1_png = new HinhAnh("Resources/XMan/DanLv1.png", D3DCOLOR_XRGB(50, 96, 166));

		DanLv2_png = new HinhAnh("Resources/XMan/DanLv2.png", D3DCOLOR_XRGB(50, 96, 166));

		DanLv3_png = new HinhAnh("Resources/XMan/DanLv3.png", D3DCOLOR_XRGB(50, 96, 166));

		HieuUngBatRa_png = new HinhAnh("Resources/HieuUng/HieuUngBatRa.png", D3DCOLOR_XRGB(0, 128, 128));

		XMan_png = new HinhAnh("Resources/XMan/XMan.png");
		XMan_Shining_png = new HinhAnh("Resources/XMan/XMan_Shining.png", D3DCOLOR_XRGB(255, 255, 255));
		HieuUngNapDanLv2_png = new HinhAnh("Resources/XMan/HieuUngNapDanLv2.png", D3DCOLOR_XRGB(0, 128, 128));
		HieuUngNapDanLv3_png = new HinhAnh("Resources/XMan/HieuUngNapDanLv3.png", D3DCOLOR_XRGB(0, 128, 128));

		LoCot_png = new HinhAnh("Resources/Enemies/LoCot.png", D3DCOLOR_XRGB(255, 0, 255));
		LoCot_Shining_png = new HinhAnh("Resources/Enemies/LoCot_Shining.png", D3DCOLOR_XRGB(255, 0, 255));

		ThangMay_png = new HinhAnh("Resources/ThangMay.png", D3DCOLOR_XRGB(255, 255, 255));
		
		TrucXoay1_png = new HinhAnh("Resources/TrucXoay1.png", D3DCOLOR_XRGB(255, 255, 255));
		TrucXoay2_png = new HinhAnh("Resources/TrucXoay2.png", D3DCOLOR_XRGB(255, 255, 255));

		XManPhatNo_png = new HinhAnh("Resources/XManPhatNo.png", D3DCOLOR_XRGB(50, 96, 166));
	}
	~DS_HinhAnh()
	{

	}

public:
	HinhAnh *HieuUngPhatNo_png;
	HinhAnh *DanNo1_png;

	HinhAnh* Ech_png;
	HinhAnh* Ech_Shining_png;

	HinhAnh* XacUop_png;

	HinhAnh *Bui_png;

	HinhAnh* DanLv1_png;

	HinhAnh* DanLv2_png;

	HinhAnh* DanLv3_png;

	HinhAnh* HieuUngBatRa_png;

	HinhAnh* XMan_png;
	HinhAnh* XMan_Shining_png;
	HinhAnh* HieuUngNapDanLv2_png;
	HinhAnh* HieuUngNapDanLv3_png;

	HinhAnh* LoCot_png;
	HinhAnh* LoCot_Shining_png;

	HinhAnh* ThangMay_png;

	HinhAnh* TrucXoay1_png;
	HinhAnh* TrucXoay2_png;

	HinhAnh* XManPhatNo_png;
};

