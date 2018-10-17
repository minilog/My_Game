#pragma once

#include "ThucThe.h"
#include "VaChamGame.h"
#include "KieuDuLieuEnum.h"
#include "ThucThe.h"
#include <map>
class NguoiChoi;

// là 1 lớp giao diện, dùng để trỏ đến Trạng Thái Người Chơi thực sự
class TrangThai
{
protected:
	TrangThai(NguoiChoi *in_NguoiChoi);
public:
	virtual void CapNhat(float in_tg) {}
	virtual void XuLyBanPhim(std::map<int, bool> in_Keys) {}
	virtual void KhiVaCham(ThucThe *in_NguoiVaCham, ePhiaVaCham in_PhiaVaCham, 
		eKetQuaVaCham in_KetQuaVaCham){}
	virtual eTrangThai ttTrangThai() = 0;

protected:
	NguoiChoi *mNguoiChoi;
};

