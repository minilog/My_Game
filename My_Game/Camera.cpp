#include "Camera.h"
#include <assert.h>

Camera *Camera::mCamera = NULL;

Camera * Camera::DuyNhat()
{
	if (mCamera == NULL)
	{
		mCamera = new Camera();
	}

	return mCamera;
}

Camera::Camera()
{
	mToaDo = D3DXVECTOR3(0, 0, 0);
	mChieuRong = 0;
	mChieuCao = 0;
}

void Camera::KhoiTao(const D3DXVECTOR3& in_ToaDo, int in_ChieuRong, int in_ChieuCao)
{
	mToaDo = in_ToaDo;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

#pragma region các hàm đơn giản

const RECT& Camera::rHCNGioiHan() const
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

const D3DXVECTOR3& Camera::vToaDo() const
{
	return mToaDo;
}

#pragma endregion