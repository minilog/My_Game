#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "KieuDuLieuEnum.h"

// là 1 lớp giao diện, dùng để trỏ đến Đối Tượng thực sự (ngoại trừ các Đối Tượng tĩnh)
class DoiTuong
{
public:
	DoiTuong(D3DXVECTOR3 in_ToaDo, D3DXVECTOR3 in_VanToc,
		int in_ChieuRong, int in_ChieuCao)
	{
		mLoaiDoiTuong = eLoaiDoiTuong::eKhongCo;
		mToaDo = in_ToaDo;
		mVanToc = in_VanToc;
		mChieuRong = in_ChieuRong;
		mChieuCao = in_ChieuCao;
	}
	virtual void CapNhat(float in_tg) {}
	virtual void Ve(D3DXVECTOR2 in_DoDoi) {};
	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong, eKetQuaVaCham in_KetQuaVaCham,
		ePhiaVaCham in_PhiaVaCham) {}
	void ThietLapToaDo(D3DXVECTOR3 in_ToaDo);
	void ThietLapVanToc(D3DXVECTOR3 in_VanToc);
	void ThietLapChieuRong(int in_ChieuRong);
	void ThietLapChieuCao(int in_ChieuCao);
	
	D3DXVECTOR3 vToaDo() const;
	D3DXVECTOR3 vVanToc() const;
	int iChieuRong() const;
	int iChieuCao() const;
	RECT rHCNGioiHan() const;

public:
	eLoaiDoiTuong mLoaiDoiTuong;
protected:
	D3DXVECTOR3 mToaDo;
	D3DXVECTOR3 mVanToc;
	int mChieuRong;
	int mChieuCao;
};

