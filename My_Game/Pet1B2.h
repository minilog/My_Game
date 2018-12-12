#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class Pet1B2 :
	public DoiTuong
{
public:
	Pet1B2() 
		:
		DoiTuong(Vec2(), Vec2(), 0, 0)
	{

		// hoat hinh
		std::vector<ThongTinFrame> lDSTTFrame;
		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(12, 6, HCN(3, 3 + 12, 2, 2 + 6), 0.2f));
		lDSTTFrame.push_back(ThongTinFrame(20, 6, HCN(18, 18 + 20, 2, 8), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(32, 6, HCN(41, 41 + 32, 2, 8), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(20, 6, HCN(75, 75 + 20, 2, 8), 0.1f));
		lDSTTFrame.push_back(ThongTinFrame(12, 6, HCN(99, 99 + 12, 2, 8), 0.1f));
		HH_1 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2, 2 + 36, 13, 13 + 54), 0.2f));
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(41, 41 + 36, 13, 13 + 54), 0.2f));
		HH_2 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2, 2 + 36, 13, 13 + 54), 0.2f));
		lDSTTFrame.push_back(ThongTinFrame(44, 54, HCN(120, 120 + 44, 13, 13 + 54), 0.2f));
		lDSTTFrame.push_back(ThongTinFrame(36, 54, HCN(2, 2 + 36, 13, 13 + 54), 99.9));
		HH_3 = new HoatHinh(lDSTTFrame);
	}

	void CapNhat(float in_tg) {}
// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong) 
	{

	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}

	void Ve(const Vec2& in_DoDoi)
	{

	}
	void DiChuyen(const Vec2& in_ToaDo, const Vec2& in_VanToc, float in_TG)
	{

	}
// INFORMATION
private:
	HoatHinh *HH_1,
		*HH_2,
		*HH_3;

// DESTRUCTURE
public:
	~Pet1B2(){}
};

