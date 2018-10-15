#include "HinhAnh.h"

void HinhAnh::KhoiTaoVoiHinhAnh(const char * in_DuongDan, RECT in_HCN, int in_ChieuRong, int in_ChieuCao, 
	D3DCOLOR in_MauNen)
{
	mXuLyHinhAnh = ToanCauGame::NhanXuLyHinhAnh(); // lấy xử lý hình ảnh từ Toàn Cầu Game
	mViTri = D3DXVECTOR3(0, 0, 0);
	mHCN = in_HCN;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
	mTrungTamXoayHinh = D3DXVECTOR2(mViTri.x, mViTri.y);
	mGocXoay = 0;
	mTiLe = D3DXVECTOR2(1, 1);
	mLatTheoChieuNgang = false;
	mLatTheoChieuDoc = false;
	mDoDoi = D3DXVECTOR2(0, 0);



}


void HinhAnh::Ve(D3DXVECTOR3 in_ViTri, RECT in_HCN, D3DXVECTOR2 in_TiLe, D3DXVECTOR2 in_DoDoi, 
	float in_GocXoay, D3DXVECTOR2 in_TrungTamXoayHinh, D3DXCOLOR in_MauNen)
{
}
