#include "VienGach.h"

void VienGach::KhoiTao(D3DXVECTOR3 in_ToaDo)
{
	// thực ra Animation của viên gạch ko cố định, nó có thể chuyển sang Hoạt Hình gạch bị vỡ
	mHoatHinh = new HoatHinh(cTenFile(), iTongKhuonHinh(), iSoHang(), iSoCot(), fThoiGianThayDoi());

	mHoatHinh->ThietLapToaDo(in_ToaDo);

	ThucThe::ThietLapChieuRong(mHoatHinh->iChieuRong());
	ThucThe::ThietLapChieuCao(mHoatHinh->iChieuCao());
}

void VienGach::CapNhat(float in_tg)
{
	mHoatHinh->CapNhat(in_tg);
}

void VienGach::Ve(D3DXVECTOR2 in_DoDoi)
{
	mHoatHinh->ThietLapDoDoi(in_DoDoi);
	mHoatHinh->Ve();
}

void VienGach::ThietLapToaDo(D3DXVECTOR3 in_ToaDo)
{
	mHoatHinh->ThietLapToaDo(in_ToaDo);
}
