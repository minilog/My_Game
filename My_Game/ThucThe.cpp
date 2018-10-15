#include "ThucThe.h"

RECT ThucThe::NhanGioiHanHCN()
{
	RECT lHCN;

	lHCN.left = int(mX - mChieuRong / 2);
	lHCN.right = int(mX + mChieuRong / 2);
	lHCN.top = int(mY - mChieuCao / 2);
	lHCN.bottom = int(mY + mChieuCao / 2);

	return lHCN;
}
