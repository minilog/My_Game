#pragma once

#include "HoatHinh.h"
#include "ThucThe.h"

// kế thừa từ Thực Thể
// là 1 lớp giao diện, dùng để trỏ đến Viên Gạch thực sự
class VienGach : ThucThe
{
public:
	VienGach() = default;
	void CapNhat(float in_tg);
	void Ve(D3DXVECTOR2 in_DoDoi);
protected:
	void KhoiTao(D3DXVECTOR3 in_ToaDo);
	void ThietLapToaDo(D3DXVECTOR3 in_ToaDo);
	// bắt buộc phải Định Nghĩa các hàm này ở các lớp kế thừa
	virtual const char* cTenFile() = 0;
	virtual int iTongKhuonHinh() = 0;
	virtual int iSoHang() = 0;
	virtual int iSoCot() = 0;
	virtual float fThoiGianThayDoi() = 0;

protected:
	HoatHinh *mHoatHinh;
};

