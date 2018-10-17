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
	bool bLaHCN(RECT in_HCN);
public:
	void Ve();
	D3DXIMAGE_INFO iiNhanThongTinHinhAnh();
	LPDIRECT3DTEXTURE9 dtNhanKetCauHinhAnh();
	void ThietLapViTri(D3DXVECTOR3 in_ViTri);
	void ThietLapViTri(float x, float y);
	void ThietLapViTri(D3DXVECTOR2 in_ViTri);
	D3DXVECTOR3 vViTri();
	void ThietLapChieuRong(int in_ChieuRong);
	int iChieuRong();
	void ThietLapChieuCao(int in_ChieuCao);
	int iChieuCao();
	void ThietLapHCN(RECT in_HCN);
	void ThietLapTiLe(D3DXVECTOR2 in_TiLe);
	D3DXVECTOR2 vTiLe();
	void ThietLapLatTheoChieuNgang(bool in_Co);
	bool bLatTheoChieuNgang();
	void ThietLapLatTheoChieuDoc(bool in_Co);
	bool bLatTheoChieuDoc();
	void ThietLapGocXoayHinh(float in_GocXoay);
	float fGocXoayHinh();
	void ThietLapDoDoi(D3DXVECTOR2 in_DoDoi);
	D3DXVECTOR2 vDoDoi();

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

