#include "HinhAnh.h"
#include "ToanCauGame.h"

HinhAnh::HinhAnh(const char * in_DuongDan)
{
	mXuLyHinhAnh = ToanCauGame::get_XuLyHinhAnh();
	D3DXGetImageInfoFromFileA(in_DuongDan, &mThongTinHinhAnh);
	mToaDo = Vec2(0, 0);
	mChieuRong = mThongTinHinhAnh.Width;
	mChieuCao = mThongTinHinhAnh.Height;
	mHCN = HinhChuNhat(0, mChieuRong, 0, mChieuCao);
	mTiLe = D3DXVECTOR2(1.0f, 1.0f);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mGocXoayHinh = 0;
	mDoDoi = Vec2(0, 0);

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

HinhAnh::~HinhAnh()
{
	if (mKetCauHinhAnh != NULL)
	{
		mKetCauHinhAnh->Release();
	}
}

void HinhAnh::Ve()
{
	D3DXVECTOR2 lTrungTamTiLe = D3DXVECTOR2(float(mToaDo.x), float(mToaDo.y));
	D3DXVECTOR2 lTrungTamXoayHinh = D3DXVECTOR2(float(mToaDo.x), float(mToaDo.y));
	D3DXVECTOR2 lTiLe = D3DXVECTOR2(float(mTiLe.x), float(mTiLe.y));
	D3DXVECTOR2 lDoDoi = D3DXVECTOR2(float(mDoDoi.x), float(mDoDoi.y));

	D3DXMatrixTransformation2D(
		&mMaTran,
		&lTrungTamTiLe, 
		0, 
		&lTiLe,
		&lTrungTamXoayHinh, 
		float(mGocXoayHinh),
		&lDoDoi);
	D3DXMATRIX lMaTranCu;

	mXuLyHinhAnh->GetTransform(&lMaTranCu);
	mXuLyHinhAnh->SetTransform(&mMaTran);

	RECT lHCN;
	lHCN.left = long(mHCN.Trai);
	lHCN.right = long(mHCN.Phai);
	lHCN.top = long(mHCN.Tren);
	lHCN.bottom = long(mHCN.Duoi);
	D3DXVECTOR3 lTrungTam = D3DXVECTOR3(float(mChieuRong / 2.0f), float(mChieuCao / 2.0f), float(0));
	D3DXVECTOR3 lToaDo = D3DXVECTOR3(float(mToaDo.x), float(mToaDo.y), 0.0f);

	mXuLyHinhAnh->Draw(
		mKetCauHinhAnh,
		&lHCN,
		&lTrungTam,
		&lToaDo,
		D3DCOLOR_ARGB(255, 255, 255, 255)); // những pixel nào có màu trắng thì sẽ tô màu này lên

	mXuLyHinhAnh->SetTransform(&lMaTranCu); // thiết lập lại Ma Trận Cũ để Xử Lý Hình Ảnh chỉ áp dụng Transform với class này
}










/////////////////////////////
/*  Các thủ tục SET - GET  */
void HinhAnh::set_LatTheoChieuDoc(bool in_Co)
{
	if (mLatTheoChieuDoc != in_Co)
	{
		mLatTheoChieuDoc = in_Co;
		mTiLe.y = -mTiLe.y;
	}
}

void HinhAnh::set_LatTheoChieuNgang(bool in_Co)
{
	if (mLatTheoChieuNgang != in_Co)
	{
		mLatTheoChieuNgang = in_Co;
		mTiLe.x = -mTiLe.x;
	}
}

D3DXIMAGE_INFO HinhAnh::get_ThongTinHinhAnh() const
{
	return mThongTinHinhAnh;
}

LPDIRECT3DTEXTURE9 HinhAnh::get_KetCauHinhAnh()
{
	return mKetCauHinhAnh;
}

Vec2 HinhAnh::get_ToaDo() const
{
	return mToaDo;
}

void HinhAnh::set_ToaDo(const Vec2& in_ToaDo)
{
	mToaDo = in_ToaDo;
}

void HinhAnh::set_ChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

int HinhAnh::get_ChieuRong()
{
	return mChieuRong;
}

void HinhAnh::set_ChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

int HinhAnh::get_ChieuCao()
{
	return mChieuCao;
}

void HinhAnh::set_HCN(const HinhChuNhat& in_HCN)
{
	mHCN = in_HCN;
}

void HinhAnh::set_TiLe(const D3DXVECTOR2& in_TiLe)
{
	mTiLe = in_TiLe;
}

D3DXVECTOR2 HinhAnh::get_TiLe() const
{
	return mTiLe;
}

bool HinhAnh::get_LatTheoChieuNgang()
{
	return mLatTheoChieuNgang;
}

bool HinhAnh::get_LatTheoChieuDoc()
{
	return mLatTheoChieuDoc;
}

void HinhAnh::set_GocXoayHinh(int in_GocXoay)
{
	mGocXoayHinh = in_GocXoay;
}

int HinhAnh::get_GocXoayHinh()
{
	return mGocXoayHinh;
}

void HinhAnh::set_DoDoi(const Vec2& in_DoDoi)
{
	mDoDoi = in_DoDoi;
}

Vec2 HinhAnh::get_DoDoi() const
{
	return mDoDoi;
}

