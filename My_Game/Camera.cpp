#include "Camera.h"

Camera::Camera(int in_ChieuRong, int in_ChieuCao)
{
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
	mViTri = D3DXVECTOR3(0, 0, 0);
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

RECT Camera::NhanGioiHanHCN()
{
	RECT lHCN;

	lHCN.left = int(mViTri.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mViTri.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}


void Camera::ThietLapViTri(D3DXVECTOR3 in_ViTri)
{
	mViTri = in_ViTri;
}

void Camera::ThietLapViTri(float in_X, float in_Y)
{
	ThietLapViTri(D3DXVECTOR3(in_X, in_Y, 0));
}

int Camera::NhanChieuRong()
{
	return mChieuRong;
}

int Camera::NhanChieuCao()
{
	return mChieuCao;
}

D3DXVECTOR3 Camera::NhanViTri()
{
	return mViTri;
}


