#include "ThucThe.h"

ThucThe::ThucThe()
{
	mLoaiThucThe = KhongCo;
}

void ThucThe::CapNhat(float in_tg)
{
	// vận tốc = pixel / giây;
	mX += mVX * in_tg;
	mY += mVY * in_tg;
}

void ThucThe::KhiVaCham(ThucThe * in_NguoiVaCham, KetQuaVaCham in_KetQuaVaCham, PhiaVaCham in_PhiaVaCham)
{
	mVX = 0;
	mVY = 0;
}


void ThucThe::KhiThietLapViTri(D3DXVECTOR3 in_ViTri)
{}





















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

void ThucThe::ThietLapViTri(D3DXVECTOR3 in_ViTri)
{
	mVX = in_ViTri.x;
	mVY = in_ViTri.y;
	KhiThietLapViTri(in_ViTri);
}

void ThucThe::ThietLapViTri(D3DXVECTOR2 in_ViTri)
{
	ThietLapViTri(D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
}

void ThucThe::ThietLapViTri(float in_X, float in_Y)
{
	ThietLapViTri(D3DXVECTOR3(in_X, in_Y, 0));
}

void ThucThe::DiChuyenThem(D3DXVECTOR3 in_ViTri)
{
	ThietLapViTri(NhanViTri() + in_ViTri);
}

void ThucThe::DiChuyenThem(D3DXVECTOR2 in_ViTri)
{
	ThietLapViTri(NhanViTri() + D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
}

void ThucThe::DiChuyenThem(float in_X, float in_Y)
{
	ThietLapViTri(NhanViTri() + D3DXVECTOR3(in_X, in_Y, 0));
}

RECT ThucThe::NhanGioiHanHCN()
{
	RECT lHCN;

	lHCN.left = int(mX - mChieuRong / 2);
	lHCN.right = int(mX + mChieuRong / 2);
	lHCN.top = int(mY - mChieuCao / 2);
	lHCN.bottom = int(mY + mChieuCao / 2);

	return lHCN;
}

D3DXVECTOR3 ThucThe::NhanViTri()
{
	return D3DXVECTOR3(mX, mY, 0);
}

void ThucThe::ThietLapVX(float in_VX)
{
	mVX = in_VX;
}

float ThucThe::NhanVX()
{
	return mVX;
}

void ThucThe::ThietLapVY(float in_VY)
{
	mVY = in_VY;
}

float ThucThe::NhanVY()
{
	return mVY;
}

void ThucThe::ThietLapChieuRong(float in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

float ThucThe::NhanChieuRong()
{
	return mChieuRong;
}

void ThucThe::ThietLapChieuCao(float in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

float ThucThe::NhanChieuCao()
{
	return mChieuCao;
}
