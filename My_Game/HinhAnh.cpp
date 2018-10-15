#include "HinhAnh.h"

void HinhAnh::KhoiTaoVoiHinhAnh(const char * in_DuongDan)
{
	mXuLyHinhAnh = ToanCauGame::NhanXuLyHinhAnh();
	D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
	mViTri = D3DXVECTOR3(0, 0, 0);
	mChieuRong = mThongTinHinhAnh.Width;
	mChieuCao = mThongTinHinhAnh.Height;;
	mHCN.left = 0;
	mHCN.right = mChieuRong;
	mHCN.top = 0;
	mHCN.bottom = mChieuCao;
	mTiLe = D3DXVECTOR2(1, 1);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mGocXoayHinh = 0;
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
		NULL,
		&mThongTinHinhAnh,
		NULL,
		&mKetCauHinhAnh);
}

void HinhAnh::Ve()
{
	D3DXVECTOR2 lTrungTamTiLe = D3DXVECTOR2(mViTri.x, mViTri.y);
	D3DXVECTOR2 lTrungTamXoayHinh = D3DXVECTOR2(mViTri.x, mViTri.y);
	D3DXVECTOR3 lTrungTam = D3DXVECTOR3(float(mChieuRong / 2), float(mChieuCao / 2), float(0));

	D3DXMatrixTransformation2D(
		&mMaTran,
		&lTrungTamTiLe, 0, &mTiLe,
		&lTrungTamXoayHinh, mGocXoayHinh,
		&mDoDoi);
	D3DXMATRIX lMaTranCu;

	mXuLyHinhAnh->GetTransform(&lMaTranCu);
	mXuLyHinhAnh->SetTransform(&mMaTran);

	mXuLyHinhAnh->Draw(
		mKetCauHinhAnh,
		&mHCN,
		&lTrungTam,
		&mViTri,
		D3DCOLOR_ARGB(255, 255, 255, 255)); // những pixel nào có màu trắng thì sẽ tô màu này lên

	mXuLyHinhAnh->SetTransform(&lMaTranCu); // thiết lập lại Ma Trận Cũ để Xử Lý Hình Ảnh chỉ áp dụng Transform với class này
}

//void HinhAnh::KhoiTaoVoiHinhAnh(
//		const char * in_DuongDan, 
//		int in_ChieuRong, int in_ChieuCao, 
//		RECT in_HCN,
//		D3DCOLOR in_MauNen)
//	{
//		/* Quy tắc lấy giá trị mặc định trước khi lấy thông tin tham số */
//		mXuLyHinhAnh = ToanCauGame::NhanXuLyHinhAnh();
//		D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
//		mViTri = D3DXVECTOR3(0, 0, 0);
//		mChieuRong = mThongTinHinhAnh.Width;
//		if (in_ChieuRong)
//		{
//			mChieuRong = in_ChieuRong;
//		}
//		else if (LaHCN(in_HCN))
//		{
//			mChieuRong = in_HCN.right - in_HCN.left;
//		}
//		mChieuCao= mThongTinHinhAnh.Height;;
//		if (in_ChieuCao)
//		{
//			mChieuCao = in_ChieuCao;
//		}
//		else if (LaHCN(in_HCN))
//		{
//			mChieuCao = in_HCN.bottom - in_HCN.top;
//		}
//		mHCN.left = 0;
//		mHCN.right = mChieuRong;
//		mHCN.top = 0;
//		mHCN.bottom = mChieuCao;
//		if (LaHCN(in_HCN))
//		{
//			mHCN = in_HCN;
//		}
//		mTiLe = D3DXVECTOR2(1, 1);
//		mLatTheoChieuNgang = false;
//		mLatTheoChieuDoc = false;
//		mGocXoayHinh = 0;
//		mDoDoi = D3DXVECTOR2(0, 0);
//	
//		LPDIRECT3DDEVICE9 lThietBi;
//		mXuLyHinhAnh->GetDevice(&lThietBi);
//		D3DXCreateTextureFromFileExA(
//			lThietBi,
//			in_DuongDan,
//			mThongTinHinhAnh.Width,
//			mThongTinHinhAnh.Height,
//			1,
//			D3DUSAGE_DYNAMIC,
//			D3DFMT_UNKNOWN,
//			D3DPOOL_DEFAULT,
//			D3DX_DEFAULT,
//			D3DX_DEFAULT,
//			in_MauNen,
//			&mThongTinHinhAnh,
//			NULL,
//			&mKetCauHinhAnh);
//	}

//void HinhAnh::Ve(
//	D3DXVECTOR3 in_ViTri, 
//	RECT in_HCN, 
//	D3DXVECTOR2 in_TiLe,
//	float in_GocXoay, 
//	D3DXVECTOR2 in_DoDoi, 
//	D3DXCOLOR in_MauNen)
//{
//	/* Quy tắc lấy giá trị mặc định trước khi lấy thông tin tham số */
//	D3DXVECTOR3 lViTri = mViTri;
//	if (in_ViTri != D3DXVECTOR3())
//	{
//		lViTri = in_ViTri;
//	}
//	RECT lHCN = mHCN;
//	if (LaHCN(in_HCN))
//	{
//		lHCN = in_HCN;
//	}
//	D3DXVECTOR2 lTrungTamTiLe = D3DXVECTOR2(mViTri.x, mViTri.y);
//	D3DXVECTOR2 lTiLe = mTiLe;
//	if (in_TiLe != D3DXVECTOR2())
//	{
//		lTiLe = in_TiLe;
//	}
//	D3DXVECTOR2 lTrungTamXoayHinh =	D3DXVECTOR2(mViTri.x, mViTri.y);
//	float lGocXoay = mGocXoayHinh;
//	if (in_GocXoay)
//	{
//		lGocXoay = in_GocXoay;
//	}
//	D3DXVECTOR2 lDoDoi = mDoDoi;
//	if (in_DoDoi != D3DXVECTOR2())
//	{
//		lDoDoi = in_DoDoi;
//	}
//
//	D3DXVECTOR3 lTrungTam = D3DXVECTOR3(float(mChieuRong / 2), float(mChieuCao / 2), float(0));
//
//	D3DXMatrixTransformation2D(
//		&mMaTran,
//		&lTrungTamTiLe, 0, &lTiLe,
//		&lTrungTamXoayHinh, lGocXoay,
//		&lDoDoi);
//	D3DXMATRIX lMaTranCu;
//
//	mXuLyHinhAnh->GetTransform(&lMaTranCu);
//	mXuLyHinhAnh->SetTransform(&mMaTran);
//
//	mXuLyHinhAnh->Draw(
//		mKetCauHinhAnh,
//		&lHCN,
//		&lTrungTam,
//		&lViTri,
//		in_MauNen); // những pixel nào có màu trắng thì sẽ tô màu này lên
//
//	mXuLyHinhAnh->SetTransform(&lMaTranCu); // thiết lập lại Ma Trận Cũ để Xử Lý Hình Ảnh chỉ áp dụng Transform với class này
//}
