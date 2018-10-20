	#pragma once

#include <d3dx9.h>
#include <d3d9.h>

// chỉ có một Camera duy nhất: lớp Single Ton
class Camera
{
private:
	static Camera *mDuyNhat;
	Camera()
	{	// vì là lớp Single Ton nên chưa thể cung cấp tất cả dữ liệu ở Constructure
		bool mDaCungCapDuLieu = false;
	}
public:
	static Camera *DuyNhat();

	// cung cấp dữ liệu: phải thực thi hàm này trước trước khi các hàm khác được thực thi
	void CungCapDuLieu(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(D3DXVECTOR3 in_ToaDo) {
		mToaDo = in_ToaDo;
	}

	D3DXVECTOR3 vToaDo() const;
	int iChieuRong() const;
	int iChieuCao() const;
	RECT rHCNGioiHan() const;

private:
	D3DXVECTOR3 mToaDo; // chính giữa camera
	int mChieuRong;
	int mChieuCao;
};

