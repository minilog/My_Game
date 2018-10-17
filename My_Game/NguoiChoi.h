#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "HoatHinh.h"
#include "ToanCauGame.h"
#include "Camera.h"
#include "TrangThai.h"
#include "ThucThe.h"
#include "KieuDuLieuEnum.h"
#include <map>

class NguoiChoi : public ThucThe
{
public:
	NguoiChoi();
	void ThietLapCamera(Camera *in_Camera);
	void CapNhat(float in_tg);
	void Ve();
	void ThietLapTrangThai(TrangThai *in_TrangThaiNguoiChoi);
	void KhiVaCham(ThucThe *in_ThucTheVaCham, eKetQuaVaCham in_KetQuaVaCham, ePhiaVaCham in_PhiaVaCham);
	void KhiVaChamPhiaDuoi();
	eHuongDiChuyen hdcHuongDiChuyen();
	RECT rHCNGioiHan();
	eTrangThai ttTrangThai();
	void XuLyBanPhim(std::map<int, bool> in_Keys);
	void OnKeyPressed(int in_Keys);
	void OnKeyUp(int in_Keys);
	// true thì sẽ lật ngược hình
	void LatHinh(bool in_Co);
protected:
	void ThayDoiHoatHinh(eTrangThai in_TrangThai);
	
public:
	bool mChoPhepSangTrai;
	bool mChoPhepSangPhai;
protected:
	Camera	*mCamera;
	TrangThai *mTrangThaiNguoiChoi;
	HoatHinh *mHoatHinhHienTai;
	HoatHinh *mHoatHinhDangDung;
	HoatHinh *mHoatHinhDangChay;
	HoatHinh *mHoatHinhDangNhay;
	eTrangThai mTrangThaiHienTai;
	bool mChoPhepNhay, mLatHinhHieTai;
};

