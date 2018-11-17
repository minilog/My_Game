#pragma once

#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>

class XMan : public DoiTuong
{
public:
	XMan(const Vec2& in_ToaDo);
	~XMan();

	virtual void CapNhat(float in_tg);
	virtual void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong);

	void XuLyBanPhim(std::map<int, bool> in_Keys);
	
private:
	HoatHinh *mHH_DungIm,
		*mHH_Chay,
		*mHH_ChuanBiChay,
		*mHH_Nhay,
		*mHH_Roi,
		*mHH_TiepDat;
	HoatHinh *mHH_HienTai;

	float mTG_ChuanBiChay = 0.02f;
	float mTG_DemChuanBiChay = 0.0f;
	float mTG_TiepDat = 0.1f;
	float mTG_DemTiepDat = 0.0f;

	float mGiaTocTrongTruong = 1200.0f;
	float mVanTocRoiToiDa = 350.0f;

	float mVanTocChayToiDa = 100.0f;

	std::map<int, bool> mKeys;
	bool mChoPhepNhay = true;


	eTrangThai mTrangThai;

	bool		mLatHinh = false;
	
	// vì hàm xử lý va chạm: thực hiện với một DS đối tượng trước khi Cập Nhật
	// phải xét hết tất cả đối tượng, nếu không có đối tượng nào bên dưới thì mới rơi
	bool mDangDungTuNhienRoi = false;

	void LoadHinhAnhVao();

	void DungIm();
	void ChuanBiChaySangTrai();
	void ChuanBiChaySangPhai();
	void ChaySangTrai();
	void ChaySangPhai();
	void Nhay();
	void Roi();
	void TiepDat();
};

