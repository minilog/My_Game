#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Box :
	public DoiTuong
{
public:
	Box()
		:
		DoiTuong(Vec2(), Vec2(), 48, 48)
	{

	}

	void CapNhat(float in_tg) {}
	// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{

	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong)
	{

	}
	void Ve(const Vec2& in_DoDoi)
	{
		HH->Ve(DS_HinhAnh::get_TH()->Box_png, false, mToaDo, in_DoDoi);
	}

	void DiChuyen(const Vec2& in_ToaDo, const Vec2& in_VanToc)
	{
		mTrangThai = eTT_Box_DiChuyen;

	}
private:
	HoatHinh *HH;


	void PhatNo()
	{
		mTrangThai = eTT_Box_PhatNo;
	}
	void BienMat()
	{
		mTrangThai = eTT_Box_BienMat;
	}

	void LoadThongTinHoatHinh()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(48, 48, HCN(0, 48, 0, 48)));
		HH = new HoatHinh(lDSTTFrame);
	}

public:
	~Box()
	{

	}
};

