#include "HinhAnh.h"

HinhAnh::HinhAnh(const char * in_DuongDan)
{
	KhoiTaoVoiHinhAnh(in_DuongDan);
}

void HinhAnh::KhoiTaoVoiHinhAnh(const char * in_DuongDan)
{
	mXuLyHinhAnh = ToanCauGame::sXuLyHinhAnh();
	D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
	mToaDo = D3DXVECTOR3(0, 0, 0);
	mChieuRong = mThongTinHinhAnh.Width;
	mChieuCao = mThongTinHinhAnh.Height;;
	mHCN.left = 0;
	mHCN.right = mChieuRong;
	mHCN.top = 0;
	mHCN.bottom = mChieuCao;
	mTiLe = D3DXVECTOR2(1, 1);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mGocXoayHinh = 0.0f;
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
	D3DXVECTOR2 lTrungTamTiLe = D3DXVECTOR2(mToaDo.x, mToaDo.y);
	D3DXVECTOR2 lTrungTamXoayHinh = D3DXVECTOR2(mToaDo.x, mToaDo.y);
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
		&mToaDo,
		D3DCOLOR_ARGB(255, 255, 255, 255)); // những pixel nào có màu trắng thì sẽ tô màu này lên

	mXuLyHinhAnh->SetTransform(&lMaTranCu); // thiết lập lại Ma Trận Cũ để Xử Lý Hình Ảnh chỉ áp dụng Transform với class này
}

HinhAnh::~HinhAnh()
{
	if (mKetCauHinhAnh != NULL)
	{
		mKetCauHinhAnh->Release();
	}
}

void HinhAnh::ThietLapLatTheoChieuDoc(bool in_Co)
{
	if (mLatTheoChieuDoc != in_Co)
	{
		mLatTheoChieuDoc = in_Co;
		mTiLe = D3DXVECTOR2(mTiLe.x, -mTiLe.y);
	}
}

void HinhAnh::ThietLapLatTheoChieuNgang(bool in_Co)
{
	if (mLatTheoChieuNgang != in_Co)
	{
		mLatTheoChieuNgang = in_Co;
		mTiLe = D3DXVECTOR2(-mTiLe.x, mTiLe.y);
	}
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

bool HinhAnh::bLaHCN(RECT in_HCN)
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

D3DXIMAGE_INFO HinhAnh::iiNhanThongTinHinhAnh()
{
	return mThongTinHinhAnh;
}

LPDIRECT3DTEXTURE9 HinhAnh::dtNhanKetCauHinhAnh()
{
	return mKetCauHinhAnh;
}

void HinhAnh::ThietLapToaDo(D3DXVECTOR3 in_ToaDo)
{
	mToaDo = in_ToaDo;
}

void HinhAnh::ThietLapToaDo(float x, float y)
{
	mToaDo = D3DXVECTOR3(x, y, 0);
}

void HinhAnh::ThietLapToaDo(D3DXVECTOR2 in_ToaDo)
{
	ThietLapToaDo(in_ToaDo.x, in_ToaDo.y);
}

D3DXVECTOR3 HinhAnh::vToaDo()
{
	return mToaDo;
}

void HinhAnh::ThietLapChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

int HinhAnh::iChieuRong()
{
	return mChieuRong;
}

void HinhAnh::ThietLapChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

int HinhAnh::iChieuCao()
{
	return mChieuCao;
}

void HinhAnh::ThietLapHCN(RECT in_HCN)
{
	mHCN = in_HCN;
}

void HinhAnh::ThietLapTiLe(D3DXVECTOR2 in_TiLe)
{
	mTiLe = in_TiLe;
}

D3DXVECTOR2 HinhAnh::vTiLe()
{
	return mTiLe;
}

bool HinhAnh::bLatTheoChieuNgang()
{
	return mLatTheoChieuNgang;
}

bool HinhAnh::bLatTheoChieuDoc()
{
	return mLatTheoChieuDoc;
}

void HinhAnh::ThietLapGocXoayHinh(float in_GocXoay)
{
	mGocXoayHinh = in_GocXoay;
}

float HinhAnh::fGocXoayHinh()
{
	return mGocXoayHinh;
}

void HinhAnh::ThietLapDoDoi(D3DXVECTOR2 in_DoDoi)
{
	mDoDoi = in_DoDoi;
}

D3DXVECTOR2 HinhAnh::vDoDoi()
{
	return mDoDoi;
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
