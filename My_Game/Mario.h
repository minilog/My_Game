#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"

class Mario : public DoiTuong
{	
public:
	Mario();
	~Mario();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi);

	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void XuLyBanPhim(std::map<int, bool> keys);
	void Roi();
	void DungIm();
	void ChaySangBenPhai();
	void ChaySangBenTrai();
	void Nhay();

private:
	HoatHinh	*mHH_HienTai,
				*mHH_DungIm,
				*mHH_Chay,
				*mHH_Nhay;
	eTrangThai	mTT_HienTai;
	bool		mLatHinh = false;
};

