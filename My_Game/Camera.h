#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
// chỉ có một Camera duy nhất
public:
	static Camera *DuyNhat();
private:
	Camera();
	static Camera *mCamera;

public:
	void KhoiTao(const D3DXVECTOR3& in_ToaDo, int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(const D3DXVECTOR3& in_ToaDo);

#pragma region lấy dữ liệu
	const D3DXVECTOR3& vToaDo() const;
	int iChieuRong() const;
	int iChieuCao() const;
	const RECT& rHCNGioiHan() const;
#pragma endregion

private:
	D3DXVECTOR3 mToaDo; // chính giữa camera
	int mChieuRong;
	int mChieuCao;
};

