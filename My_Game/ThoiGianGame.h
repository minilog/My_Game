#pragma once

#include <Windows.h>

class ThoiGianGame
{
public:
	static ThoiGianGame* NhanTruongHop(); // Kiểu dữ liệu là 1 lớp, ko cần ghi kiểu dữ liệu phía trước hàm
	void BatDauDem();

public:
	float fThoiGianDemDuoc();

private:
	static ThoiGianGame *mTruongHop;
	LARGE_INTEGER mBatDau, mKetThuc, mTyLeThoiGian;
};
