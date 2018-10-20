#include "Camera.h"
#include <assert.h>

// bắt buộc cung cấp cho Compiler 1 static Camera
Camera *Camera::mDuyNhat = new Camera(); 

Camera * Camera::DuyNhat()
{
	return mDuyNhat;
}

void Camera::CungCapDuLieu(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao)
{
	mToaDo = in_ToaDo;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
	mDaCungCapDuLieu = true;
}

#pragma region các hàm đơn giản

RECT Camera::rHCNGioiHan() const
{
	assert(mDaCungCapDuLieu == true);

	RECT lHCN;
	lHCN.left = int(mToaDo.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mToaDo.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}

int Camera::iChieuRong() const
{
	assert(mDaCungCapDuLieu == true);

	return mChieuRong;
}

int Camera::iChieuCao() const
{
	assert(mDaCungCapDuLieu == true);

	return mChieuCao;
}

D3DXVECTOR3 Camera::vToaDo() const
{
	assert(mDaCungCapDuLieu == true);

	return mToaDo;
}

#pragma endregion