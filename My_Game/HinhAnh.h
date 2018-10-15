#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "ToanCauGame.h"

// sử dụng để kế thừa cho Hoạt Hình
class HinhAnh
{
public:
	HinhAnh(const char* in_DuongDan);
	~HinhAnh();
protected:
	void KhoiTaoVoiHinhAnh(const char* in_DuongDan);
	bool LaHCN(RECT in_HCN);
public:
	void Ve();
	D3DXIMAGE_INFO NhanThongTinHinhAnh();
	LPDIRECT3DTEXTURE9 NhanKetCauHinhAnh();
	void ThietLapViTri(D3DXVECTOR3 in_ViTri);
	void ThietLapViTri(float x, float y);
	void ThietLapViTri(D3DXVECTOR2 in_ViTri);
	D3DXVECTOR3 NhanViTri();
	void ThietLapChieuRong(int in_ChieuRong);
	int NhanChieuRong();
	void ThietLapChieuCao(int in_ChieuCao);
	int NhanChieuCao();
	void ThietLapHCN(RECT in_HCN);
	void ThietLapTiLe(D3DXVECTOR2 in_TiLe);
	D3DXVECTOR2 NhanTiLe();
	void LatTheoChieuNgang(bool in_Co);
	bool LaLatTheoChieuNgang();
	void LatTheoChieuDoc(bool in_Co);
	bool LaLatTheoChieuDoc();
	void ThietLapGocXoayHinh(float in_GocXoay);
	float NhanGocXoayHinh();
	void ThietLapDoDoi(D3DXVECTOR2 in_DoDoi);
	D3DXVECTOR2 NhanDoDoi();

protected:
	LPD3DXSPRITE            mXuLyHinhAnh;
	D3DXIMAGE_INFO          mThongTinHinhAnh;
	LPDIRECT3DTEXTURE9      mKetCauHinhAnh;		// tải hình ảnh vào đây
	D3DXMATRIX              mMaTran;			// ma trận hỗ trợ cho các phép hình học

	D3DXVECTOR3             mViTri;
	int                     mChieuRong; 
	int						mChieuCao;			// kích thước của Kết Cấu Hình Ảnh
	RECT                    mHCN;				// hình chữ nhật cắt từ Kết Cấu Hình Ảnh
	D3DXVECTOR2             mTiLe;
	bool					mLatTheoChieuNgang;
	bool                    mLatTheoChieuDoc;
	float                   mGocXoayHinh;
	D3DXVECTOR2             mDoDoi;				// Dời hình ảnh theo vị trí hình ảnh + độ dời
};

