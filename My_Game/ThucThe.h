#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "KieuDuLieuEnum.h"

class ThucThe
{
public:
	ThucThe()
	{
		mLoaiThucThe = KhongCo;
	}
protected:
	// được gọi khi thiết lập vị trí cho Thực Thể, dùng cho kế thừa
	virtual void KhiThietLapViTri(D3DXVECTOR3 in_ViTri) 
	{}
public:
	virtual RECT NhanGioiHanHCN();
	virtual void CapNhat(float in_tg)
	{
		// vận tốc = pixel / giây;
		mX += mVX * in_tg;
		mY += mVY * in_tg;
	}
	// kiểm sát việc va chạm
	virtual void KhiVaCham(ThucThe *in_NguoiVaCham, KetQuaVaCham in_KetQuaVaCham, PhiaVaCham in_PhiaVaCham)
	{
		mVX = 0;
		mVY = 0;
	}
	virtual void ThietLapViTri(D3DXVECTOR3 in_ViTri)
	{
		mVX = in_ViTri.x;
		mVY = in_ViTri.y;
		KhiThietLapViTri(in_ViTri);
	}
	virtual void ThietLapViTri(D3DXVECTOR2 in_ViTri)
	{
		ThietLapViTri(D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
	}
	virtual void ThietLapViTri(float in_X, float in_Y)
	{
		ThietLapViTri(D3DXVECTOR3(in_X, in_Y, 0));
	}
	virtual void DiChuyenThem(D3DXVECTOR3 in_ViTri)
	{
		ThietLapViTri(NhanViTri() + in_ViTri);
	}
	virtual void DiChuyenThem(D3DXVECTOR2 in_ViTri)
	{
		ThietLapViTri(NhanViTri() + D3DXVECTOR3(in_ViTri.x, in_ViTri.y, 0));
	}
	virtual void DiChuyenThem(float in_X, float in_Y)
	{
		ThietLapViTri(NhanViTri() + D3DXVECTOR3(in_X, in_Y, 0));
	}
	virtual D3DXVECTOR3 NhanViTri()
	{
		return D3DXVECTOR3(mX, mY, 0);
	}
	virtual void ThietLapVX(float in_VX)
	{
		mVX = in_VX;
	}
	virtual float NhanVX()
	{
		return mVX;
	}
	virtual void ThietLapVY(float in_VY)
	{
		mVY = in_VY;
	}
	virtual float NhanVY()
	{
		return mVY;
	}
	virtual void ThietLapChieuRong(float in_ChieuRong)
	{
		mChieuRong = in_ChieuRong;
	}
	virtual float NhanChieuRong()
	{
		return mChieuRong;
	}
	virtual void ThietLapChieuCao(float in_ChieuCao)
	{
		mChieuCao = in_ChieuCao;
	}
	virtual float NhanChieuCao()
	{
		return mChieuCao;
	}

public:
	LoaiThucThe mLoaiThucThe;
protected:
	float mX;
	float mY;
	float mVX;
	float mVY;
	float mChieuRong;
	float mChieuCao;
};

