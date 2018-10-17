#pragma once

#include <Windows.h>

class ThoiGianGame
{
public:
	static ThoiGianGame* NhanTruongHop(); // Kiểu dữ liệu là 1 lớp, ko cần ghi kiểu dữ liệu phía trước hàm
	void BatDauDem();
	float fThoiGianDemDuoc();

private:
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
	static ThoiGianGame *mTruongHop;
};
