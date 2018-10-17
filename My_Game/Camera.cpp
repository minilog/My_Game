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

RECT Camera::rHCNGioiHan()
{
	RECT lHCN;

	lHCN.left = int(mViTri.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mViTri.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}


void Camera::ThietLapToaDo(D3DXVECTOR3 in_ViTri)
{
	mViTri = in_ViTri;
}

void Camera::ThietLapToaDo(float in_X, float in_Y)
{
	ThietLapToaDo(D3DXVECTOR3(in_X, in_Y, 0));
}

int Camera::iChieuRong()
{
	return mChieuRong;
}

int Camera::iChieuCao()
{
	return mChieuCao;
}

D3DXVECTOR3 Camera::vViTri()
{
	return mViTri;
}


