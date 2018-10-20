 //bắt đầu từ Game -> Màn Game -> Bản Đồ Game
 //bắt đầu từ Game -> Màn Game -> Người Chơi
#include "BanDoGame.h"
#include "GachBinhThuong.h"
#include "GachVang.h"
#include "Camera.h"
#include "DanhSachDoiTuong.h"
#include "DoiTuong.h"

BanDoGame::BanDoGame(char * in_DuongDan)
{
	mBanDo = new Tmx::Map();
	mBanDo->ParseFile(in_DuongDan);
	mChieuRong = mBanDo->GetWidth() * mBanDo->GetTileWidth();
	mChieuCao = mBanDo->GetHeight() * mBanDo->GetTileHeight();
	mChieuRongTile = mBanDo->GetTileWidth();
	mChieuCaoTile = mBanDo->GetTileHeight();
	Camera::DuyNhat()->ThietLapToaDo(D3DXVECTOR3(Camera::DuyNhat()->iChieuRong() / 2.0f,
		mChieuCao - Camera::DuyNhat()->iChieuCao() / 2.0f, 0.0f));
	TaiBanDo(in_DuongDan);
}

void BanDoGame::TaiBanDo(char * in_DuongDan)
{

#pragma region tao cac TileSet
	for (int i = 0; i < mBanDo->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *lTileSet = mBanDo->GetTileset(i);
		HinhAnh *lHinhAnh = new HinhAnh(lTileSet->GetImage()->GetSource().c_str());
		mDanhSachTileSet.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	}
#pragma endregion

#pragma region Tao Cac Vien Gach Va Cac Object Tinh
	for (int i = 0; i < mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		if (lNhomObject->GetName() == "GachBinhThuong" || lNhomObject->GetName() == "GachVang")
		{
			//đối với các Object động thì chỉ cần lấy Tọa Độ của nó trong Map
			for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
			{
				Tmx::Object *lObject = lNhomObject->GetObjects().at(j);
				
				// lấy tọa độ của Object từ trong Bản Đồ
				D3DXVECTOR3 lToaDo(float(lObject->GetX() + lObject->GetWidth() / 2.0f),
					float(lObject->GetY() - lObject->GetHeight() / 2.0f), float (0.0f));
				
				// tạo viên gạch NULL
				DoiTuong *lDoiTuong = nullptr;

				if (lNhomObject->GetName() == "GachBinhThuong")
				{
					lDoiTuong = new GachBinhThuong(lToaDo);
					lDoiTuong->mLoaiDoiTuong = eLoaiDoiTuong::eVienGachVangBinhThuong;
				}
				else if (lNhomObject->GetName() == "GachVang")
				{
					lDoiTuong = new GachVang(lToaDo);
					lDoiTuong->mLoaiDoiTuong = eLoaiDoiTuong::eVienGachVangAnDuoc;
				}

				if (lDoiTuong != NULL)
				{
					DanhSachDoiTuong::DuyNhat()->DanhSach().push_back(lDoiTuong);
				}
			}
		}
		else
		{
			for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
			{
				Tmx::Object *lObject = lNhomObject->GetObjects().at(j);
				D3DXVECTOR3 lToaDo(float(lObject->GetX() + lObject->GetWidth() / 2.0f),
					float(lObject->GetY() + lObject->GetHeight() / 2.0f), 0.0f);

				DoiTuong * lDoiTuong = new DoiTuong(lToaDo, D3DXVECTOR3(0, 0, 0), lObject->GetWidth(),
						lObject->GetHeight());

				lDoiTuong->mLoaiDoiTuong = eLoaiDoiTuong::eThucTheTinh;

				DanhSachDoiTuong::DuyNhat()->DanhSach().push_back(lDoiTuong);
			}
		}
	}
#pragma endregion
}

void BanDoGame::CapNhat(float in_tg)
{
	for (int i = 0; i < int(DanhSachDoiTuong::DuyNhat()->DanhSach().size()); i++)
	{
		DanhSachDoiTuong::DuyNhat()->DanhSach()[i]->CapNhat(in_tg);
	}
}

void BanDoGame::Ve()
{
	D3DXVECTOR2 lDoDoi = D3DXVECTOR2(ToanCauGame::iChieuRong() / 2.0f - Camera::DuyNhat()->vToaDo().x,
		ToanCauGame::iChieuCao() / 2.0f - Camera::DuyNhat()->vToaDo().y);

// Copy Code
#pragma region Ve TileSet
	for (size_t i = 0; i < mBanDo->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mBanDo->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		for (size_t j = 0; j < mBanDo->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mBanDo->GetTileset(j);

			RECT sourceRECT;

			int tileWidth = mBanDo->GetTileWidth();
			int tileHeight = mBanDo->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

					if (Camera::DuyNhat() != NULL)
					{
						RECT objRECT;
						objRECT.left = position.x - tileWidth / 2;
						objRECT.top = position.y - tileHeight / 2;
						objRECT.right = objRECT.left + tileWidth;
						objRECT.bottom = objRECT.top + tileHeight;

						if (!VaChamGame::kqvcHCNVaHCN(Camera::DuyNhat()->rHCNGioiHan(), objRECT).DaVaCham)
							continue;
					}

					if (layer->GetTileTilesetIndex(n, m) == j)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						HinhAnh* lHinhAnh = mDanhSachTileSet[j];

						lHinhAnh->ThietLapToaDo(position);
						lHinhAnh->ThietLapChieuRong(mChieuRongTile);
						lHinhAnh->ThietLapChieuCao(mChieuCaoTile);
						lHinhAnh->ThietLapHCN(sourceRECT);
						lHinhAnh->ThietLapDoDoi(lDoDoi);
						lHinhAnh->Ve();
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Ve Cac Vien Gach

	for (int i = 0; i < int(DanhSachDoiTuong::DuyNhat()->DanhSach().size()); i++)
	{
		DanhSachDoiTuong::DuyNhat()->DanhSach()[i]->Ve(lDoDoi);
	}

#pragma endregion

}


BanDoGame::~BanDoGame()
{
	delete mBanDo;

	for (int i = 0; i < int(mDanhSachTileSet.size()); i++)
	{
		if (mDanhSachTileSet[i])
			delete mDanhSachTileSet[i];
	}
	mDanhSachTileSet.clear();
	
	for (size_t i = 0; i < DanhSachDoiTuong::DuyNhat()->DanhSach().size(); i++)
	{
		eLoaiDoiTuong lLoai = DanhSachDoiTuong::DuyNhat()->DanhSach()[i]->mLoaiDoiTuong;
		if (lLoai != eLoaiDoiTuong::eMario)
			delete DanhSachDoiTuong::DuyNhat()->DanhSach()[i];
	}
	DanhSachDoiTuong::DuyNhat()->DanhSach().clear();

	//mCayBonNhanh->DonDep();
	//delete mCayBonNhanh;
}


#pragma region Cac Ham Don Gian
Tmx::Map * BanDoGame::bdBanDo()
{
	return mBanDo;
}

int BanDoGame::iChieuRong()
{
	return mChieuRong;
}

int BanDoGame::iChieuCao()
{
	return mChieuCao;
}

int BanDoGame::iChieuRongTile()
{
	return mChieuRongTile;
}

int BanDoGame::iChieuCaoTile()
{
	return mChieuCaoTile;
}

RECT BanDoGame::rHCNGioiHanBanDo()
{
	RECT lHCN;
	lHCN.left = lHCN.top = 0;
	lHCN.right = mChieuRong;
	lHCN.bottom = mChieuCao;

	return lHCN;
}

bool BanDoGame::bCaMeraChamBienTrai()
{
	return (Camera::DuyNhat()->rHCNGioiHan().left == 0);
}

bool BanDoGame::bCameraChamBienPhai()
{
	return (Camera::DuyNhat()->rHCNGioiHan().right == mChieuRong);
}

bool BanDoGame::bCameraChamBienTren()
{
	return (Camera::DuyNhat()->rHCNGioiHan().top == 0);
}

bool BanDoGame::bCameraChamBienDuoi()
{
	return (Camera::DuyNhat()->rHCNGioiHan().bottom == mChieuCao);
}

std::map<int, HinhAnh*> BanDoGame::sDanhSachTileSet()
{
	return mDanhSachTileSet;
}

#pragma endregion