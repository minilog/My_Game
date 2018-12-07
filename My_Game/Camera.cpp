﻿#include "Camera.h"
#include "ToanCauGame.h"

// bắt buộc cung cấp cho Compiler
Vec2 Camera::mToaDo = Vec2(0.0f, 0.0f); 
int Camera::mChieuRong = 0;
int Camera::mChieuCao = 0;
int Camera::mGioiHanTrai = 0;
int Camera::mGioiHanPhai = 769 + 254;
int Camera::mGioiHanTren = 770;
int Camera::mGioiHanDuoi = 770 + 220;

int Camera::mGioiHanTraiTiepTheo = 0;
int Camera::mGioiHanPhaiTiepTheo = 769 + 254;
int Camera::mGioiHanTrenTiepTheo = 770;
int Camera::mGioiHanDuoiTiepTheo = 770 + 220;
int Camera::CheckPoint = 0;


void Camera::set_ToaDo(const Vec2& in_ToaDo) 
{
	switch (CheckPoint)
	{
	case 0:
		if (in_ToaDo.x >= 790.0f && in_ToaDo.x <= 950.0f &&
			in_ToaDo.y >= 800.0f && in_ToaDo.y <= 950.0f)
		{
			mGioiHanTrai = 660;
			mGioiHanTraiTiepTheo = 769;
			mGioiHanTren = mGioiHanTrenTiepTheo = 256;

			CheckPoint++;
		}
		break;

	case 1:
		if (in_ToaDo.x >= 850.0f && in_ToaDo.x <= 950.0f &&
			in_ToaDo.y >= 350.0f && in_ToaDo.y <= 430.0f)
		{
			mGioiHanDuoi = 550;
			mGioiHanDuoiTiepTheo = 256 + mChieuCao;
			mGioiHanPhaiTiepTheo = 2048;

			CheckPoint++;
		}

	case 2:
		if (in_ToaDo.x >= 1650.0f && in_ToaDo.x <= 1700.0f &&
			in_ToaDo.y >= 200.0f && in_ToaDo.y <= 450.0f)
		{
			mGioiHanTrai = 1450;
			mGioiHanTraiTiepTheo = 1536;
			mGioiHanDuoiTiepTheo = 1280;

			CheckPoint++;
		}
		break;

	case 3:
		if (in_ToaDo.x >= 1750.0f && in_ToaDo.x <= 1850.0f &&
			in_ToaDo.y >= 1000.0f && in_ToaDo.y <= 1200.0f)
		{
			mGioiHanPhaiTiepTheo = 2290;

			CheckPoint++;
		}
		break;

	default:
		break;
	}

	mToaDo = in_ToaDo;

	if (mToaDo.x < mGioiHanTrai + mChieuRong / 2.0f)
	{
		mToaDo.x = mGioiHanTrai + mChieuRong / 2.0f;
	}
	if (mToaDo.x > mGioiHanPhai - mChieuRong / 2.0f)
	{
		mToaDo.x = mGioiHanPhai - mChieuRong / 2.0f;
	}
	if (mToaDo.y < mGioiHanTren + mChieuCao / 2.0f)
	{
		mToaDo.y = mGioiHanTren + mChieuCao / 2.0f;
	}
	if (mToaDo.y > mGioiHanDuoi - mChieuCao / 2.0f)
	{
		mToaDo.y = mGioiHanDuoi - mChieuCao / 2.0f;
	}

	for (int k = 0; k < 4; k++)
	{
		if (mGioiHanTrai < mGioiHanTraiTiepTheo)
			mGioiHanTrai++;
		else if (mGioiHanTrai > mGioiHanTraiTiepTheo)
			mGioiHanTrai--;

		if (mGioiHanPhai < mGioiHanPhaiTiepTheo)
			mGioiHanPhai++;
		else if (mGioiHanPhai > mGioiHanPhaiTiepTheo)
			mGioiHanPhai--;

		if (mGioiHanTren < mGioiHanTrenTiepTheo)
			mGioiHanTren++;
		else if (mGioiHanTren > mGioiHanTrenTiepTheo)
			mGioiHanTren--;

		if (mGioiHanDuoi < mGioiHanDuoiTiepTheo)
			mGioiHanDuoi++;
		else if (mGioiHanDuoi > mGioiHanDuoiTiepTheo)
			mGioiHanDuoi--;
	}

}

void Camera::set_KichThuoc(int in_ChieuRong, int in_ChieuCao)
{
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

void Camera::set_GioiHan(int in_Trai, int in_Phai, int in_Tren, int in_Duoi)
{
	mGioiHanTrai = in_Trai;
	mGioiHanPhai = in_Phai;
	mGioiHanTren = in_Tren;
	mGioiHanDuoi = in_Duoi;
}

HCN Camera::get_HCNGioiHan()
{
	return HCN(
		int(mToaDo.x - mChieuRong / 2.0f),
		int(mToaDo.x + mChieuRong / 2.0f),
		int(mToaDo.y - mChieuCao / 2.0f),
		int(mToaDo.y + mChieuCao / 2.0f));
}

HCN Camera::get_HCNGioiHan_MoRong()
{
	return HCN(
		int(mToaDo.x - mChieuRong),
		int(mToaDo.x + mChieuRong),
		int(mToaDo.y - mChieuCao),
		int(mToaDo.y + mChieuCao));
}

int Camera::get_ChieuRong()
{
	return mChieuRong;
}

int Camera::get_ChieuCao()
{
	return mChieuCao;
}

Vec2 Camera::get_ToaDo()
{
	return mToaDo;
}
