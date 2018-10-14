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

