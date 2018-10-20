#include "Camera.h"

// bắt buộc cung cấp cho Compiler 1 static Camera
Camera *Camera::mDuyNhat = NULL; 

Camera * Camera::DuyNhat()
{
	if (mDuyNhat == NULL)
	{
		mDuyNhat = new Camera();
	}
	return mDuyNhat;
}

void Camera::CungCapDuLieu(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao)
{
	mToaDo = in_ToaDo;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

#pragma region các hàm đơn giản

RECT Camera::rHCNGioiHan() const
{
	RECT lHCN;
	lHCN.left = int(mToaDo.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mToaDo.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
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