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
public:
	void ThietLapToaDo(D3DXVECTOR3 in_ToaDo);
	void ThietLapToaDo(float x, float y);
	void ThietLapToaDo(D3DXVECTOR2 in_ToaDo);
	void ThietLapChieuRong(int in_ChieuRong);
	void ThietLapChieuCao(int in_ChieuCao);
	void ThietLapHCN(RECT in_HCN);
	void ThietLapTiLe(D3DXVECTOR2 in_TiLe);
	void ThietLapLatTheoChieuNgang(bool in_Co);
	void ThietLapLatTheoChieuDoc(bool in_Co);
	void ThietLapGocXoayHinh(float in_GocXoay);
	void ThietLapDoDoi(D3DXVECTOR2 in_DoDoi);
	void Ve();

protected:
	bool bLaHCN(RECT in_HCN);
public:
	D3DXIMAGE_INFO iiNhanThongTinHinhAnh();
	LPDIRECT3DTEXTURE9 dtNhanKetCauHinhAnh();
	D3DXVECTOR3 vToaDo();
	int iChieuRong();
	int iChieuCao();
	D3DXVECTOR2 vTiLe();
	bool bLatTheoChieuNgang();
	bool bLatTheoChieuDoc();
	float fGocXoayHinh();
	D3DXVECTOR2 vDoDoi();

protected:
	LPD3DXSPRITE            mXuLyHinhAnh;
	D3DXIMAGE_INFO          mThongTinHinhAnh;
	LPDIRECT3DTEXTURE9      mKetCauHinhAnh;		// tải hình ảnh vào đây
	D3DXMATRIX              mMaTran;			// ma trận hỗ trợ cho các phép hình học
	D3DXVECTOR3             mToaDo;
	int                     mChieuRong; 
	int						mChieuCao;			// kích thước của Kết Cấu Hình Ảnh
	RECT                    mHCN;				// hình chữ nhật cắt từ Kết Cấu Hình Ảnh
	D3DXVECTOR2             mTiLe;
	bool					mLatTheoChieuNgang;
	bool                    mLatTheoChieuDoc;
	float                   mGocXoayHinh;
	D3DXVECTOR2             mDoDoi;				// Dời hình ảnh theo vị trí hình ảnh + độ dời
};

