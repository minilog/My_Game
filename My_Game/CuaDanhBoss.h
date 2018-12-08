#pragma once
// tách cửa đánh boss và boss ra thành các đối tượng riêng
// truyền vào con boss 2 cửa

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class CuaDanhBoss :
	public DoiTuong
{
public:
	// CONSTRUCTURE
	CuaDanhBoss(const Vec2& in_ToaDo);

	void CapNhat(float in_tg) {}

	// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi);

	void set_ChoPhepMoCua(bool in) { ChoPhepMoCua = in; }


// INFORMATION
private:
	bool ChoPhepMoCua = true;
	static constexpr float TG_MoCua = 0.25f * 17; 
	static constexpr float TG_DongCua = 0.25f * 17;
	float TGDem = 0.0f;
	HoatHinh *HH_DongCua;
	HoatHinh *HH_MoCua;
	HoatHinh *HH_HienTai;


// FUNCTION
private:
	void MoCua();
	void DongCua();
	void KhoaCua();

	void LoadThongTinHoatHinh();

// DESTRUCTURE
public:
	~CuaDanhBoss();
};

