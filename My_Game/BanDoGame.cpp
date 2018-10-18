 //bắt đầu từ Game -> Màn Game -> Bản Đồ Game
 //bắt đầu từ Game -> Màn Game -> Người Chơi
#include "BanDoGame.h"
#include "GachBinhThuong.h"
#include "GachVang.h"

BanDoGame::BanDoGame(char * in_DuongDan)
{
	mBanDo = new Tmx::Map();
	mBanDo->ParseFile(in_DuongDan);
	mChieuRong = mBanDo->GetWidth() * mBanDo->GetTileWidth();
	mChieuCao = mBanDo->GetHeight() * mBanDo->GetTileHeight();
	mChieuRongTile = mBanDo->GetTileWidth();
	mChieuCaoTile = mBanDo->GetTileHeight();
	mCamera = new Camera(ToanCauGame::iChieuRong(), ToanCauGame::iChieuCao());
	TaiBanDo(in_DuongDan);
}

void BanDoGame::TaiBanDo(char * in_DuongDan)
{
#pragma region tao Cay Bon Nhanh
	RECT lR;
	lR.left = 0;
	lR.top = 0;
	lR.right = this->iChieuRong();
	lR.bottom = this->iChieuCao();
	mCayBonNhanh = new CayBonNhanh(0, lR);
#pragma endregion

#pragma region tao cac TileSet
	for (int i = 0; i < mBanDo->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *lTileSet = mBanDo->GetTileset(i);
		HinhAnh *lHinhAnh = new HinhAnh(lTileSet->GetImage()->GetSource().c_str());
		mDanhSanhTileSet.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	}
#pragma endregion

#pragma region Tao Cac Vien Gach
	for (int i = 0; i < mBanDo->GetNumLayers(); i++)
	{
		// xét từng lớp hình ảnh tạo nên Bản Đồ
		const Tmx::TileLayer *lLopHinhAnh = mBanDo->GetTileLayer(i);
		
		if (lLopHinhAnh->IsVisible())
		{
			continue;
		}
		if (lLopHinhAnh->GetName() == "brick" || lLopHinhAnh->GetName() == "coin")
		{
			for (int m = 0; m < lLopHinhAnh->GetHeight(); m++)
			{
				for (int n = 0; n < lLopHinhAnh->GetWidth(); n++)
				{
					if (lLopHinhAnh->GetTileTilesetIndex(n, m) != -1)
					{
						D3DXVECTOR3 lToaDo(float(n * mChieuRongTile + mChieuRongTile / 2.0f),
							float(m * mChieuCaoTile + mChieuCaoTile / 2.0f), float(0.0f));
						VienGach *lVienGach = nullptr;
						if (lLopHinhAnh->GetName() == "brick")
						{
							lVienGach = new GachBinhThuong(lToaDo);
							lVienGach->mLoaiThucThe = eLoaiThucThe::eVienGachVangBinhThuong;
						}
						else
						{
							lVienGach = new GachVang(lToaDo);
							lVienGach->mLoaiThucThe = eLoaiThucThe::eVienGachVangAnDuoc;
						}

						mDanhSachVienGach.push_back(lVienGach);
						if (lVienGach)
						{
							mCayBonNhanh->ThemThucThe(lVienGach);
						}
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Tao Cac Vat The Tinh
	for (int i = 0; i < mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomVatThe = mBanDo->GetObjectGroup(i);
		
		for (int j = 0; j < lNhomVatThe->GetNumObjects(); j++)
		{
			Tmx::Object *lVatThe = lNhomVatThe->GetObjects().at(j);

			ThucThe *lThucThe = new ThucThe();
			lThucThe->ThietLapToaDo(float(lVatThe->GetX() + lVatThe->GetWidth() / 2.0f),
				float(lVatThe->GetY() + lVatThe->GetHeight() / 2.0f));
			lThucThe->ThietLapChieuRong(lVatThe->GetWidth());
			lThucThe->ThietLapChieuCao(lVatThe->GetHeight());
			lThucThe->mLoaiThucThe = eLoaiThucThe::eThucTheTinh;

			mCayBonNhanh->ThemThucThe(lThucThe);
		}
	}
#pragma endregion

	//chú ý
	//thêm thực thể = các object là các hình ảnh cụ thể thì 
	//lThucThe->ThietLapToaDo(lVatThe->GetX() + lVatThe->GetWidth() / 2,
	//lVatThe->GetY() - lVatThe->GetHeight() / 2);
}

void BanDoGame::CapNhat(float in_tg)
{
	for (int i = 0; i < int(mDanhSachVienGach.size()); i++)
	{
		mDanhSachVienGach[i]->CapNhat(in_tg);
	}
}

void BanDoGame::Ve()
{

}

BanDoGame::~BanDoGame()
{
}

Tmx::Map * BanDoGame::bdBanDo()
{
	return nullptr;
}

int BanDoGame::iChieuRong()
{
	return 0;
}

int BanDoGame::iChieuCao()
{
	return 0;
}

int BanDoGame::iChieuRongTile()
{
	return 0;
}

int BanDoGame::iChieuCaoTile()
{
	return 0;
}

RECT BanDoGame::rHCNGioiHanBanDo()
{
	return RECT();
}

bool BanDoGame::bCaMeraChamBienTrai()
{
	return false;
}

bool BanDoGame::bCameraChamBienPhai()
{
	return false;
}

bool BanDoGame::bCameraChamBienTren()
{
	return false;
}

bool BanDoGame::bCameraChamBienDuoi()
{
	return false;
}

std::map<int, HinhAnh*> BanDoGame::sDanhSachTileSet()
{
	return std::map<int, HinhAnh*>();
}

std::vector<VienGach*> BanDoGame::vgDanhSachVienGach()
{
	return std::vector<VienGach*>();
}

CayBonNhanh * BanDoGame::cbnCayBonNhanh()
{
	return nullptr;
}
