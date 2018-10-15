#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "ToanCauGame.h"

// sử dụng để kế thừa cho Hoạt Hình
class HinhAnh
{
public:
	HinhAnh() = default;

	HinhAnh(const char* in_DuongDan, RECT in_HCN = RECT(), int in_ChieuRong = NULL, 
		int in_ChieuCao = NULL, D3DCOLOR in_MauNen = NULL);

	~HinhAnh();

	void Ve(D3DXVECTOR3 in_ViTri = D3DXVECTOR3(), RECT in_HCN = RECT(), D3DXVECTOR2 in_TiLe = D3DXVECTOR2(), 
		D3DXVECTOR2 in_DoDoi = D3DXVECTOR2(), float in_GocXoay = 0, D3DXVECTOR2 in_TrungTamXoayHinh = D3DXVECTOR2(), 
		D3DXCOLOR in_MauNen = D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 NhanKetCauHinhAnh();

	D3DXIMAGE_INFO NhanThongTinHinhAnh();



	void ThietLapChieuRong(int in_ChieuRong);

	int NhanChieuRong();

	void ThietLapChieuCao(int in_ChieuCao);

	int NhanChieuCao();



protected:
	void KhoiTaoVoiHinhAnh(const char* in_DuongDan, RECT in_HCN = RECT(), int in_ChieuRong = NULL, 
		int in_ChieuCao = NULL, D3DCOLOR in_MauNen = NULL);

	bool LaHCN(RECT in_HCN);

protected:
	LPDIRECT3DTEXTURE9      mKetCauHinhAnh;		// tải hình ảnh vào đây
	LPD3DXSPRITE            mXuLyHinhAnh;
	D3DXIMAGE_INFO          mThongTinHinhAnh;
	D3DXMATRIX              mMaTran;			// ma trận hỗ trợ cho các phép hình học

	D3DXVECTOR3             mViTri;
	RECT                    mHCN;				// hình chữ nhật cắt từ Kết Cấu Hình Ảnh
	int                     mChieuRong; 
	int						mChieuCao;			// kích thước của Kết Cấu Hình Ảnh
	bool                    mLatTheoChieuDoc;
	bool					mLatTheoChieuNgang;
	float                   mGocXoay;
	D3DXVECTOR2             mTrungTamXoayHinh;
	D3DXVECTOR2             mTiLe;
	D3DXVECTOR2             mDoDoi;				// Dời hình ảnh theo vị trí hình ảnh + độ dời
};

