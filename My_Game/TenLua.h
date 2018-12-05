//#pragma once
//
//#include "DoiTuong.h"
//#include "HoatHinh.h"
//#include "VaChamGame.h"
//#include "DS_HinhAnh.h"
//
//
//class TenLua :
//	public DoiTuong
//{
//public:
//
//
//	TenLua();
//
//// FUNCTION
//	void CapNhat(float in_tg);
//	void Ve(const Vec2& in_DoDoi);
//	void XuLyVaCham(const DoiTuong* in_DoiTuong);
//	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc);
//
//// INFORMATION
//private:
//	HoatHinh *mHH_Dan;
//	HoatHinh *mHH_HieuUngPhatNo;
//
//	const float mTG_NoTung = 0.08f * 6;
//	float mTGDem_NoTung = mTG_NoTung + 0.1f;
//	Vec2 mToaDo_HieuUngNoTung;
//
//	// lỡ như ko va chạm thì Đạn có thể tự động biến mất để có thể dùng tiếp
//	static constexpr float mTG_TonTai = 1.1f;
//	float mTGDem_TonTai = 0.0f;
//
//	static constexpr float mGiaTocTrongTruong = 1000.0f;
//	float mVanTocRoiToiDa = 200.0f;
//
//
//	// SUB-FUNCTION
//	void LoadThongTinHoatHinh();
//
//	//DESTRUCTURE
//	~TenLua()
//	{
//
//	}
//
//};
//
