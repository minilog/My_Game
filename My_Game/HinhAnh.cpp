#include "HinhAnh.h"

/* Hàm này khởi tạo các Chỉ số ban đầu */
void HinhAnh::KhoiTaoVoiHinhAnh(const char * in_DuongDan, RECT in_HCN, int in_ChieuRong, int in_ChieuCao, 
	D3DCOLOR in_MauNen)
{
	mXuLyHinhAnh = ToanCauGame::NhanXuLyHinhAnh();
	D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
	mViTri = D3DXVECTOR3(0, 0, 0);

	if (in_ChieuRong)
	{
		mChieuRong = in_ChieuRong;
	}
	else
	{
		if (LaHCN(in_HCN))
		{
			mChieuRong = in_HCN.right - in_HCN.left;
		}
		else
		{
			mChieuRong = mThongTinHinhAnh.Width;
		}
	}

	if (in_ChieuCao)
	{
		mChieuCao = in_ChieuCao;
	}
	else
	{
		if (LaHCN(in_HCN))
		{
			mChieuCao = in_HCN.bottom - in_HCN.top;

		}
		else
		{
			mChieuCao = mThongTinHinhAnh.Height;
		}
	}

	if (LaHCN(in_HCN))
	{
		mHCN = in_HCN;
	}
	else
	{
		mHCN.left = 0;
		mHCN.right = mChieuRong;
		mHCN.top = 0;
		mHCN.bottom = mChieuCao;
	}

	mTrungTamXoayHinh = D3DXVECTOR2(mViTri.x, mViTri.y);
	mGocXoay = 0;
	mTiLe = D3DXVECTOR2(1, 1);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mDoDoi = D3DXVECTOR2(0, 0);

	LPDIRECT3DDEVICE9 lThietBi;
	mXuLyHinhAnh->GetDevice(&lThietBi);

	D3DXCreateTextureFromFileExA(
		lThietBi,
		in_DuongDan,
		mThongTinHinhAnh.Width,
		mThongTinHinhAnh.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		in_MauNen,
		&mThongTinHinhAnh,
		NULL,
		&mKetCauHinhAnh);
}

void HinhAnh::Ve(D3DXVECTOR3 in_ViTri, RECT in_HCN, D3DXVECTOR2 in_TiLe, D3DXVECTOR2 in_DoDoi, 
	float in_GocXoay, D3DXVECTOR2 in_TrungTamXoayHinh, D3DXCOLOR in_MauNen)
{
	D3DXVECTOR3 
}
