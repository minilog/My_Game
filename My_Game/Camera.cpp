#include "Camera.h"
#include <assert.h>

Camera *Camera::mDuyNhat = NULL;

Camera * Camera::DuyNhat()
{
	if (mDuyNhat == NULL)
	{
		mDuyNhat = new Camera();
	}

	return mDuyNhat;
}

void Camera::KhoiTao(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao)
{
	mDaKhoiTao = true;
	mToaDo = in_ToaDo;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

#pragma region các hàm đơn giản

RECT Camera::rHCNGioiHan() const
{
	assert(mDaKhoiTao == true);

	RECT lHCN;
	lHCN.left = int(mToaDo.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mToaDo.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}

void Camera::ThietLapToaDo(D3DXVECTOR3 in_ToaDo)
{
	assert(mDaKhoiTao == true);

	mToaDo = in_ToaDo;
}

int Camera::iChieuRong() const
{
	assert(mDaKhoiTao == true);

	return mChieuRong;
}

int Camera::iChieuCao() const
{
	assert(mDaKhoiTao == true);

	return mChieuCao;
}

D3DXVECTOR3 Camera::vToaDo() const
{
	assert(mDaKhoiTao == true);

	return mToaDo;
}

#pragma endregion