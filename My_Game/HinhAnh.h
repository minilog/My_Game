#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "ToanCauGame.h"

// sử dụng để kế thừa cho Hoạt Hình
class HinhAnh
{
public:
	HinhAnh(const char* in_DuongDan)
	{
		KhoiTaoVoiHinhAnh(in_DuongDan);
	}
	~HinhAnh()
	{
		if (mKetCauHinhAnh != NULL)
		{
			mKetCauHinhAnh->Release();
		}
	}
protected:
	void KhoiTaoVoiHinhAnh(const char* in_DuongDan);
	bool LaHCN(RECT in_HCN)
	{
		if (in_HCN.left == in_HCN.right)
		{
			return false;
		}
		if (in_HCN.top == in_HCN.bottom)
		{
			return false;
		}

		return true;
	}
public:
	void Ve();

	D3DXIMAGE_INFO NhanThongTinHinhAnh()
	{
		return mThongTinHinhAnh;
	}
	LPDIRECT3DTEXTURE9 NhanKetCauHinhAnh()
	{
		return mKetCauHinhAnh;
	}
	void ThietLapViTri(D3DXVECTOR3 in_ViTri)
	{
		mViTri = in_ViTri;
	}
	void ThietLapViTri(float x, float y)
	{
		mViTri = D3DXVECTOR3(x, y, 0);
	}
	void ThietLapViTri(D3DXVECTOR2 in_ViTri)
	{
		ThietLapViTri(in_ViTri.x, in_ViTri.y);
	}
	D3DXVECTOR3 NhanViTri()
	{
		return mViTri;
	}
	void ThietLapChieuRong(int in_ChieuRong)
	{
		mChieuRong = in_ChieuRong;
	}
	int NhanChieuRong()
	{
		return mChieuRong;
	}
	void ThietLapChieuCao(int in_ChieuCao)
	{
		mChieuCao = in_ChieuCao;
	}
	int NhanChieuCao()
	{
		return mChieuCao;
	}
	void ThietLapHCN(RECT in_HCN)
	{
		mHCN = in_HCN;
	}
	void ThietLapTiLe(D3DXVECTOR2 in_TiLe)
	{
		mTiLe = in_TiLe;
	}
	D3DXVECTOR2 NhanTiLe()
	{
		return mTiLe;
	}
	void LatTheoChieuNgang(bool in_Co)
	{
		if (mLatTheoChieuNgang != in_Co)
		{
			mLatTheoChieuNgang = in_Co;
			mTiLe = D3DXVECTOR2(-mTiLe.x, mTiLe.y);
		}
	}
	bool LaLatTheoChieuNgang()
	{
		return mLatTheoChieuNgang;
	}
	void LatTheoChieuDoc(bool in_Co)
	{
		if (mLatTheoChieuDoc != in_Co)
		{
			mLatTheoChieuDoc = in_Co;
			mTiLe = D3DXVECTOR2(mTiLe.x, -mTiLe.y);
		}
	}
	bool LaLatTheoChieuDoc()
	{
		return mLatTheoChieuDoc;
	}
	void ThietLapGocXoayHinh(float in_GocXoay)
	{
		mGocXoayHinh = in_GocXoay;
	}
	float NhanGocXoayHinh()
	{
		return mGocXoayHinh;
	}
	void ThietLapDoDoi(D3DXVECTOR2 in_DoDoi)
	{
		mDoDoi = in_DoDoi;
	}
	D3DXVECTOR2 NhanDoDoi()
	{
		return mDoDoi;
	}

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

