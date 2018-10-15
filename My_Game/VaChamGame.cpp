#include "VaChamGame.h"

KetQuaVaCham VaChamGame::HCNVaHCN(RECT in_HCN1, RECT in_HCN2)
{
	KetQuaVaCham lKetQuaVaCham;

	if (!DaVaCham(in_HCN1, in_HCN2))
	{
		lKetQuaVaCham.DaVaCham = false;

		return lKetQuaVaCham;
	}

	lKetQuaVaCham.DaVaCham = true;

	//chon max Left
	lKetQuaVaCham.VungVaCham.left = in_HCN1.left > in_HCN2.left ? in_HCN1.left : in_HCN2.left;
	//chon max right
	lKetQuaVaCham.VungVaCham.right = in_HCN1.right < in_HCN2.right ? in_HCN1.right : in_HCN2.right;
	//chon min bottom
	lKetQuaVaCham.VungVaCham.bottom = in_HCN1.bottom < in_HCN2.bottom ? in_HCN1.bottom : in_HCN2.bottom;
	//chon max top
	lKetQuaVaCham.VungVaCham.top = in_HCN1.top > in_HCN2.top ? in_HCN1.top : in_HCN2.top;

	return lKetQuaVaCham;
}

PhiaVaCham VaChamGame::NhanPhiaVaCham(ThucThe * in_ThucThe1, KetQuaVaCham in_KetQuaVaCham)
{
	float xCenter = in_KetQuaVaCham.VungVaCham.left + (in_KetQuaVaCham.VungVaCham.right - in_KetQuaVaCham.VungVaCham.left) / 2.0f;
	float yCenter = in_KetQuaVaCham.VungVaCham.top + (in_KetQuaVaCham.VungVaCham.bottom - in_KetQuaVaCham.VungVaCham.top) / 2.0f;

	D3DXVECTOR2 cCenter = D3DXVECTOR2(xCenter, yCenter);
	D3DXVECTOR2 eCenter = in_ThucThe1->NhanViTri();

	//lay vector noi tam Entity va CollisionRect
	D3DXVECTOR2 vec = cCenter - eCenter;

	//chuan hoa vector
	D3DXVec2Normalize(&vec, &vec);

	/*
	- neu vector chuan hoa co y > 0 =>nam phia ben tren Entity
	- neu vector chuan hoa co y < 0 =>nam phia ben duoi Entity
	- neu vector chuan hoa co x > 0 => nam phia ben phai Entity
	- neu vector chuan hoa co x < 0 => nam phia ben trai Entity
	*/

	if (vec.y < 0)
	{
		//va cham phia ben tren
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham Tren
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return PhiaVaCham::Tren;
		}
		else if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//goc trong khoang 35 -> 70 phia ben Tren - Phai
			return PhiaVaCham::PhaiBenTren;
		}
		else if (vec.x >= 0.8f)
		{
			return PhiaVaCham::Phai;
		}
		else if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//va cham phia top - left
			return PhiaVaCham::TraiBenTren;
		}
		else
		{
			return PhiaVaCham::Trai;
		}
	}
	else
	{
		//va cham phia ben duoi
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (vec.x <= 0.35f && vec.x >= -0.35)
		{
			return PhiaVaCham::Duoi;
		}
		else if (vec.x > 0.35 && vec.x < 0.8)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return PhiaVaCham::PhaiBenDuoi;
		}
		else if (vec.x >= 0.8)
		{
			return PhiaVaCham::Phai;
		}
		else if (vec.x < -0.35f && vec.x > -0.8f)
		{
			//va cham phia top - left
			return PhiaVaCham::TraiBenDuoi;
		}
		else
		{
			return PhiaVaCham::Trai;
		}
	}

	return PhiaVaCham::KhongXacDinh;
}

PhiaVaCham VaChamGame::NhanPhiaVaCham(ThucThe * in_ThucThe1, ThucThe * in_ThucThe2)
{
	float lW = (in_ThucThe1->NhanChieuRong() + in_ThucThe2->NhanChieuRong()) / 2.0f;
	float lH = (in_ThucThe1->NhanChieuCao() + in_ThucThe2->NhanChieuCao()) / 2.0f;

	float lDx = in_ThucThe1->NhanViTri().x - in_ThucThe2->NhanViTri().y;
	float lDy = in_ThucThe1->NhanViTri().x - in_ThucThe2->NhanViTri().y;

	if (abs(lDx) <= lW && abs(lDy) <= lH)
	{
		/* co va cham*/
		float lWy = lW * lDy;
		float lHx = lH * lDx;

		if (lWy > lHx)
		{
			if (lWy > -lHx)
			{
				/*va cham phia tren e1*/
				return PhiaVaCham::Tren;
			}
			else
			{
				/*va cham phia ben phai e1*/
				return PhiaVaCham::Phai;
			}
		}
		else if (lWy > -lHx)
		{
			/*va cham ben trai e1*/
			return PhiaVaCham::Trai;
		}
		else
		{
			/*va cham phia duoi e1*/
			return PhiaVaCham::Duoi;
		}
	}

	return PhiaVaCham::KhongXacDinh;
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

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
	if (in_X < in_HCN.left ||
		in_X > in_HCN.right ||
		in_Y < in_HCN.top ||
		in_Y > in_HCN.bottom)
	{
		return false;
	}

	return true;
}

bool VaChamGame::HCNVaHinhTron(RECT in_HCN, int in_TamX, int in_TamY, int in_BanKinh)
{
	int lPx = in_TamX;
	int lPy = in_TamY;

	if (lPx < in_HCN.left)
		lPx = in_HCN.left;
	else if (lPx > in_HCN.right)
		lPx = in_HCN.right;

	if (lPy > in_HCN.bottom)
		lPy = in_HCN.bottom;
	else if (lPy < in_HCN.top)
		lPy = in_HCN.top;

	int lDx = lPx - in_TamX;
	int lDy = lPy - in_TamY;

	return (lDx * lDx + lDy * lDy) <= in_BanKinh * in_BanKinh;
}
