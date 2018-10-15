#include "Camera.h"

RECT Camera::NhanGioiHanHCN()
{
	RECT lHCN;

	lHCN.left = int(mViTri.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mViTri.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}
