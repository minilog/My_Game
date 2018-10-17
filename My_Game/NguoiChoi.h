#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "HoatHinh.h"
#include "ToanCauGame.h"
#include "Camera.h"
#include "TrangThaiNguoiChoi.h"
#include "ThucThe.h"
#include "KieuDuLieuEnum.h"
#include <map>

class NguoiChoi : public ThucThe
{
public:
	NguoiChoi();
	void ThietLapCamera(Camera);
	void CapNhat(float in_tg);
	void Ve();
	void ThietLapTrangThai(TrangThaiNguoiChoi *in_TrangThaiNguoiChoi);
	void KhiVaCham(ThucThe *in_ThucTheVaCham, KetQuaVaCham in_KetQuaVaCham, PhiaVaCham in_PhiaVaCham);
	void KhiVaChamPhiaDuoi();
	HuongDiChuyen hdcHuongDiChuyen();
	RECT rHCNGioiHan();
	TrangThai ttTrangThai();
	void XuLyBanPhim(std::map<int, bool> in_Keys);
	void OnKeyPressed(int in_Keys);
	void OnKeyUp(int in_Keys);
	// true thì sẽ lật ngược hình
	void LatHinh(bool in_Co);
protected:
	void ThayDoiHoatHinh(TrangThai in_TrangThai);
	
public:
	bool mChoPhepSangTrai;
	bool mChoPhepSangPhai;
protected:
	Camera	*mCamera;
	TrangThaiNguoiChoi *mTrangThaiNguoiChoi;
	HoatHinh *mHoatHinhHienTai;
	HoatHinh *mHoatHinhDangDung;
	HoatHinh *mHoatHinhDangChay;
	HoatHinh *mHoatHinhDangNhay;
	TrangThai mTrangThaiHienTai;
	bool mChoPhepNhay, mLatHinhHieTai;
};

