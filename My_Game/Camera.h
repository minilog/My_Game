	#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
// chỉ có một Camera duy nhất
public:
	static Camera *DuyNhat();
private:
	Camera()
	{
		bool mDaKhoiTao = false;
	}
	static Camera *mDuyNhat;

public:
	void KhoiTao(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(D3DXVECTOR3 in_ToaDo);

#pragma region lấy dữ liệu
	D3DXVECTOR3 vToaDo() const;
	int iChieuRong() const;
	int iChieuCao() const;
	RECT rHCNGioiHan() const;
#pragma endregion

private:
	bool mDaKhoiTao;
	D3DXVECTOR3 mToaDo; // chính giữa camera
	int mChieuRong;
	int mChieuCao;
};

