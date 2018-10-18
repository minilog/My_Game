#include "ThucThe.h"

ThucThe::ThucThe()
{
	mLoaiThucThe = eKhongCo;
}

void ThucThe::CapNhat(float in_tg)
{
	// vận tốc = pixel / giây;
	mX += mVX * in_tg;
	mY += mVY * in_tg;
}

void ThucThe::KhiVaCham(ThucThe * in_NguoiVaCham, eKetQuaVaCham in_KetQuaVaCham, ePhiaVaCham in_PhiaVaCham)
{
	mVX = 0;
	mVY = 0;
}



















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

void ThucThe::ThietLapToaDo(D3DXVECTOR3 in_ViTri)
{
	mVX = in_ViTri.x;
	mVY = in_ViTri.y;
	KhiThietLapViTri(in_ViTri);
}

void ThucThe::ThietLapToaDo(D3DXVECTOR2 in_ViTri)
{
	ThietLapToaDo(D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
}

void ThucThe::ThietLapToaDo(float in_X, float in_Y)
{
	ThietLapToaDo(D3DXVECTOR3(in_X, in_Y, 0));
}

void ThucThe::DiChuyenThem(D3DXVECTOR3 in_ViTri)
{
	ThietLapToaDo(vToaDo() + in_ViTri);
}

void ThucThe::DiChuyenThem(D3DXVECTOR2 in_ViTri)
{
	ThietLapToaDo(vToaDo() + D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
}

void ThucThe::DiChuyenThem(float in_X, float in_Y)
{
	ThietLapToaDo(vToaDo() + D3DXVECTOR3(in_X, in_Y, 0));
}

RECT ThucThe::rHCNGioiHan()
{
	RECT lHCN;

	lHCN.left = int(mX - mChieuRong / 2);
	lHCN.right = int(mX + mChieuRong / 2);
	lHCN.top = int(mY - mChieuCao / 2);
	lHCN.bottom = int(mY + mChieuCao / 2);

	return lHCN;
}

D3DXVECTOR3 ThucThe::vToaDo()
{
	return D3DXVECTOR3(mX, mY, 0);
}

void ThucThe::ThietLapVX(float in_VX)
{
	mVX = in_VX;
}

float ThucThe::fVX()
{
	return mVX;
}

void ThucThe::ThietLapVY(float in_VY)
{
	mVY = in_VY;
}

float ThucThe::fVY()
{
	return mVY;
}

void ThucThe::ThietLapChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

int ThucThe::fChieuRong()
{
	return mChieuRong;
}

void ThucThe::ThietLapChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

int ThucThe::fChieuCao()
{
	return mChieuCao;
}
