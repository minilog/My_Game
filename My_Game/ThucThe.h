#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "KieuDuLieuEnum.h"

class ThucThe
{
public:
	ThucThe();
protected:
	// được gọi khi thiết lập vị trí cho Thực Thể, dùng cho kế thừa
	virtual void KhiThietLapViTri(D3DXVECTOR3 in_ViTri);
public:
	virtual RECT NhanGioiHanHCN();
	virtual void CapNhat(float in_tg);
	// kiểm soát việc va chạm
	virtual void KhiVaCham(ThucThe *in_NguoiVaCham, KetQuaVaCham in_KetQuaVaCham, PhiaVaCham in_PhiaVaCham);
	virtual void ThietLapViTri(D3DXVECTOR3 in_ViTri);
	virtual void ThietLapViTri(D3DXVECTOR2 in_ViTri);
	virtual void ThietLapViTri(float in_X, float in_Y);
	virtual void DiChuyenThem(D3DXVECTOR3 in_ViTri);
	virtual void DiChuyenThem(D3DXVECTOR2 in_ViTri);
	virtual void DiChuyenThem(float in_X, float in_Y);
	virtual D3DXVECTOR3 NhanViTri();
	virtual void ThietLapVX(float in_VX);
	virtual float NhanVX();
	virtual void ThietLapVY(float in_VY);
	virtual float NhanVY();
	virtual void ThietLapChieuRong(float in_ChieuRong);
	virtual float NhanChieuRong();
	virtual void ThietLapChieuCao(float in_ChieuCao);
	virtual float NhanChieuCao();

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

