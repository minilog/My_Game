#include "Camera.h"

Camera::Camera(int in_ChieuRong, int in_ChieuCao)
{
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
	mToaDo = D3DXVECTOR3(0, 0, 0);
}

#pragma region Cac Ham Don Gian

RECT Camera::rHCNGioiHan() const
{
	RECT lHCN;

	lHCN.left = int(mToaDo.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mToaDo.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}


void Camera::ThietLapToaDo(const D3DXVECTOR3& in_ToaDo)
{
	mToaDo = in_ToaDo;
}

int Camera::iChieuRong() const
{
	return mChieuRong;
}

int Camera::iChieuCao() const
{
	return mChieuCao;
}

D3DXVECTOR3 Camera::vToaDo() const
{
	return mToaDo;
}

#pragma endregion