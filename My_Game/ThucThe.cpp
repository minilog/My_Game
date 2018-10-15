#include "ThucThe.h"

RECT ThucThe::NhanGioiHanHCN()
{
	RECT lHCN;

	lHCN.left = mX - mChieuRong / 2;
	lHCN.right = mX + mChieuRong / 2;
	lHCN.top = mY - mChieuCao / 2;
	lHCN.bottom = mY + mChieuCao / 2;

	return lHCN;
}
