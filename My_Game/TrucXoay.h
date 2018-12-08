#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class TrucXoay :
	public DoiTuong
{
public:
	TrucXoay(const Vec2& in_ToaDo, int in_ChieuRong = 32, int in_ChieuCao = 32, int k = 0) :
		DoiTuong(in_ToaDo, Vec2(), in_ChieuRong, in_ChieuCao)
	{
		mLoaiDoiTuong = eLDT_TrucXoay;
		K = k;
		if (K == 1 || 
			K == 2)
		{
			LatHinh = true;
		}
		if (K == -1 ||
			K == -2)
		{
			LatHinh = false;
		}


		std::vector<ThongTinFrame> lDSTTFrame;

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(102, 102 + 32, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(68, 68 + 32, 0, 32),   0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(34, 34 + 32, 0, 32),   0.25f));
		lDSTTFrame.push_back(ThongTinFrame(32, 32, HCN(0, 32, 0, 32),         0.25f));
		HH_1 = new HoatHinh(lDSTTFrame);

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(16, 32, HCN(60, 60 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(16, 32, HCN(40, 40 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(16, 32, HCN(20, 20 + 18, 0, 32), 0.25f));
		lDSTTFrame.push_back(ThongTinFrame(16, 32, HCN(0, 18, 0, 32), 0.25f));
		HH_2 = new HoatHinh(lDSTTFrame);

	}

	void CapNhat(float in_tg) {}

// FUNCTION
	void Ve(const Vec2& in_DoDoi) 
	{
		if (K == 1 ||
			K == -1)
		{
			HH_1->Ve(DS_HinhAnh::get_TH()->TrucXoay1_png, LatHinh, mToaDo, in_DoDoi);
		}
		else if (K == 2 ||
			K == -2)
		{
			HH_2->Ve(DS_HinhAnh::get_TH()->TrucXoay2_png, LatHinh, mToaDo, in_DoDoi);
		}
	} // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong)
	{
		if (K == 1 ||
			K == -1)
		{
			HH_1->CapNhat(in_tg);
		}
		else if (K == 2 ||
			K == -2)
		{
			HH_2->CapNhat(in_tg);
		}
	}

// INFORMATION
private:
	HoatHinh* HH_1;
	HoatHinh* HH_2;

	bool LatHinh = false;
public:
	int K = 0;

// DESTRUCTURE
	~TrucXoay()
	{

	}
};

