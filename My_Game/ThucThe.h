#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "KieuDuLieuEnum.h"

// là 1 lớp giao diện, dùng để trỏ đến Thực Thể thực sự
class ThucThe
{
public:
	ThucThe();
protected:
	// thực hiện hàm này trong "tất cả trường hợp" thiết lập vị trí
	virtual void KhiThietLapViTri(D3DXVECTOR3 in_ViTri) {}
public:
	virtual RECT rHCNGioiHan();
	virtual void CapNhat(float in_tg);
	// kiểm soát việc va chạm
	virtual void KhiVaCham(ThucThe *in_NguoiVaCham, eKetQuaVaCham in_KetQuaVaCham, ePhiaVaCham in_PhiaVaCham);
	virtual void ThietLapToaDo(D3DXVECTOR3 in_ViTri);
	virtual void ThietLapToaDo(D3DXVECTOR2 in_ViTri);
	virtual void ThietLapToaDo(float in_X, float in_Y);
	virtual void DiChuyenThem(D3DXVECTOR3 in_ViTri);
	virtual void DiChuyenThem(D3DXVECTOR2 in_ViTri);
	virtual void DiChuyenThem(float in_X, float in_Y);
	virtual D3DXVECTOR3 vToaDo();
	virtual void ThietLapVX(float in_VX);
	virtual float fVX();
	virtual void ThietLapVY(float in_VY);
	virtual float fVY();
	virtual void ThietLapChieuRong(int in_ChieuRong);
	virtual int fChieuRong();
	virtual void ThietLapChieuCao(int in_ChieuCao);
	virtual int fChieuCao();

public:
	eLoaiThucThe mLoaiThucThe;
protected:
	float mX;
	float mY;
	float mVX;
	float mVY;
	int mChieuRong;
	int mChieuCao;
};

