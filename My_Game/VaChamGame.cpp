﻿#include "VaChamGame.h"

KetQuaVaCham VaChamGame::HCNVaHCN(RECT in_HCN1, RECT in_HCN2)
{
	KetQuaVaCham lKetQuaVaCham;

	if (!DaVaCham(in_HCN1, in_HCN2))
	{
		lKetQuaVaCham.DaVaCham = false;

		return lKetQuaVaCham;
	}

	lKetQuaVaCham.DaVaCham = true;

	// vùng va chạm hình chữ nhật
	lKetQuaVaCham.VungVaCham.left = in_HCN1.left > in_HCN2.left ? in_HCN1.left : in_HCN2.left;
	lKetQuaVaCham.VungVaCham.right = in_HCN1.right < in_HCN2.right ? in_HCN1.right : in_HCN2.right;
	lKetQuaVaCham.VungVaCham.bottom = in_HCN1.bottom < in_HCN2.bottom ? in_HCN1.bottom : in_HCN2.bottom;
	lKetQuaVaCham.VungVaCham.top = in_HCN1.top > in_HCN2.top ? in_HCN1.top : in_HCN2.top;

	return lKetQuaVaCham;
}

PhiaVaCham VaChamGame::NhanPhiaVaCham(ThucThe * in_ThucThe1, KetQuaVaCham in_KetQuaVaCham)
{
	float lTrungTamVaChamX = in_KetQuaVaCham.VungVaCham.left + (in_KetQuaVaCham.VungVaCham.right - in_KetQuaVaCham.VungVaCham.left) / 2.0f;
	float lTrungTamVaChamY = in_KetQuaVaCham.VungVaCham.top + (in_KetQuaVaCham.VungVaCham.bottom - in_KetQuaVaCham.VungVaCham.top) / 2.0f;

	D3DXVECTOR2 lTrungTamVaCham = D3DXVECTOR2(lTrungTamVaChamX, lTrungTamVaChamY);
	D3DXVECTOR2 lTrungTamThucThe = in_ThucThe1->NhanViTri();

	// lấy vector nối từ Thực Thể đến Vùng Va Chạm
	D3DXVECTOR2 lVec = lTrungTamVaCham - lTrungTamThucThe;

	// chuẩn hóa Vector
	D3DXVec2Normalize(&lVec, &lVec);

	/*
	- nếu vector chuẩn hóa có y > 0 => nằm phía bên trên Thực Thể
	- nếu vector chuẩn hóa có y < 0 => nằm phía bên dưới Thực Thể
	- nếu vector chuẩn hoá có x > 0 => nam phia ben phai Entity
	- neu vector chuan hoa co x < 0 => nam phia ben trai Entity
	*/

	if (lVec.y < 0)
	{
		// va chạm phía bên trên
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham Tren
		if (lVec.x <= 0.35f && lVec.x >= -0.35f)
		{
			return PhiaVaCham::Tren;
		}
		else if (lVec.x > 0.35f && lVec.x < 0.8f)
		{
			//goc trong khoang 35 -> 70 phia ben Tren - Phai
			return PhiaVaCham::PhaiBenTren;
		}
		else if (lVec.x >= 0.8f)
		{
			return PhiaVaCham::Phai;
		}
		else if (lVec.x < -0.35f && lVec.x >= -0.8f)
		{
			// va chạm phía Trên - Trái
			return PhiaVaCham::TraiBenTren;
		}
		else
		{
			return PhiaVaCham::Trai;
		}
	}
	else
	{
		// va chạm phía bên dưới
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (lVec.x <= 0.35f && lVec.x >= -0.35)
		{
			return PhiaVaCham::Duoi;
		}
		else if (lVec.x > 0.35 && lVec.x < 0.8)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return PhiaVaCham::PhaiBenDuoi;
		}
		else if (lVec.x >= 0.8)
		{
			return PhiaVaCham::Phai;
		}
		else if (lVec.x < -0.35f && lVec.x > -0.8f)
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
		/* có va chạm */
		float lWy = lW * lDy;
		float lHx = lH * lDx;

		if (lWy > lHx)
		{
			if (lWy > -lHx)
			{
				/*va cham phia tren Thực Thể 1*/
				return PhiaVaCham::Tren;
			}
			else
			{
				/*va chạm phía bên phải Thực Thể 1*/
				return PhiaVaCham::Phai;
			}
		}
		else if (lWy > -lHx)
		{
			/*va chạm phía bên trái Thực Thể 1*/
			return PhiaVaCham::Trai;
		}
		else
		{
			/*va chạm phía bên dưới Thực Thể 1*/
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
