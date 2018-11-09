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
	void XuLyBanPhim(std::map<int, bool> in_Keys);

private:
	void Roi();
	void DungIm();
	void ChaySangTrai();
	void ChaySangPhai();
	void Nhay();

private:
	HoatHinh	*mHH_HienTai,
				*mHH_DungIm,
				*mHH_Chay,
				*mHH_Nhay;
	eTrangThai	mTT_HienTai;
	bool		mLatHinh = false;

	// vì hàm xử lý va chạm: thực hiện với một DS đối tượng trước khi Cập Nhật
	// phải xét hết tất cả đối tượng, nếu không có đối tượng nào bên dưới thì mới rơi
	bool mDangDungTuNhienRoi = false;

	static constexpr float mGiaTocTrongTruong = 0.25f;
	float mGiaTocTrongTruongHienTai = 0.0f;
	static constexpr int mVanTocNhayCaoNhat = 8;
};

