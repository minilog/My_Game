#include "Camera.h"
#include "ToanCauGame.h"

// bắt buộc cung cấp cho Compiler
Vec2 Camera::mToaDo = Vec2(0, 0); 
int Camera::mChieuRong = 0;
int Camera::mChieuCao = 0;
int Camera::mGioiHanTrai = -9999;
int Camera::mGioiHanPhai = 9999;
int Camera::mGioiHanTren = -9999;
int Camera::mGioiHanDuoi = 9999;

void Camera::set_ToaDo(const Vec2& in_ToaDo) 
{
	mToaDo = in_ToaDo;

	if (mToaDo.x < mGioiHanTrai + mChieuRong / 2)
	{
		mToaDo.x = mGioiHanTrai + mChieuRong / 2;
	}
	if (mToaDo.x > mGioiHanPhai - mChieuRong / 2)
	{
		mToaDo.x = mGioiHanPhai - mChieuRong / 2;
	}
	if (mToaDo.y < mGioiHanTren + mChieuCao / 2)
	{
		mToaDo.y = mGioiHanTren + mChieuCao / 2;
	}
	if (mToaDo.y > mGioiHanDuoi - mChieuCao / 2)
	{
		mToaDo.y = mGioiHanDuoi - mChieuCao / 2;
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

HinhChuNhat Camera::get_HCNGioiHan()
{
	return HinhChuNhat(
		mToaDo.x - mChieuRong / 2,
		mToaDo.x + mChieuRong / 2,
		mToaDo.y - mChieuCao / 2,
		mToaDo.y + mChieuCao / 2);;
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
