#include "VaChamGame.h"

bool VaChamGame::DaVaCham(RECT in_HCN1, RECT in_HCN2)
{
	if (in_HCN1.left > in_HCN2.right ||
		in_HCN1.right < in_HCN2.left ||
		in_HCN1.top > in_HCN2.bottom ||
		in_HCN1.bottom < in_HCN2.top)
	{
		return false;
	}

	return true;
}

bool VaChamGame::DiemVaHCN(float in_X, float in_Y, RECT in_HCN)
{
	return false;
}

bool VaChamGame::HCNVaHinhTron(RECT in_HCN, int in_TamX, int in_TamY, int in_BanKinh)
{
	return false;
}

KetQuaVaCham VaChamGame::HCNVaHCN(RECT in_HCN1, RECT in_HCN2)
{
	return KetQuaVaCham();
}

PhiaVaCham VaChamGame::NhanPhiaVaCham(ThucThe * in_ThucThe1, KetQuaVaCham in_KetQuaVaCham)
{
	return PhiaVaCham();
}

PhiaVaCham VaChamGame::NhanPhiaVaCham(ThucThe * in_ThucThe1, ThucThe * in_ThucThe2)
{
	return PhiaVaCham();
}
