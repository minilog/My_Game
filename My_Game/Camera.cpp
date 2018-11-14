#include "Camera.h"
#include "ToanCauGame.h"

// bắt buộc cung cấp cho Compiler
Vec2 Camera::mToaDo = Vec2(0.0f, 0.0f); 
int Camera::mChieuRong = 0;
int Camera::mChieuCao = 0;
int Camera::mGioiHanTrai = -9999;
int Camera::mGioiHanPhai = 9999;
int Camera::mGioiHanTren = -9999;
int Camera::mGioiHanDuoi = 9999;

void Camera::set_ToaDo(const Vec2& in_ToaDo) 
{
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
		int(mToaDo.y + mChieuCao / 2.0f));;
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
