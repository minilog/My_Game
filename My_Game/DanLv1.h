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

class DanLv1 :
	public DoiTuong
{
public:
	DanLv1(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2());
	~DanLv1();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(DoiTuong* in_DoiTuong);

	void Remake()
	{
		DangTonTai();
	}

	eTrangThai get_TrangThai()
	{
		return mTrangThai;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_HienTai;

	float mTG_PhaHuy; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;

	eTrangThai mTrangThai;

	void LoadHinhAnhVao();

	void DangTanBien();

	void DangTonTai();

public :
	static constexpr float mVanTocDan = 380.0f;
};

