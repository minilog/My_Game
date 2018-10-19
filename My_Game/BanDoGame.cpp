 //bắt đầu từ Game -> Màn Game -> Bản Đồ Game
 //bắt đầu từ Game -> Màn Game -> Người Chơi
#include "BanDoGame.h"
#include "GachBinhThuong.h"
#include "GachVang.h"
#include "Camera.h"

BanDoGame::BanDoGame(char * in_DuongDan)
{
	mBanDo = new Tmx::Map();
	mBanDo->ParseFile(in_DuongDan);
	mChieuRong = mBanDo->GetWidth() * mBanDo->GetTileWidth();
	mChieuCao = mBanDo->GetHeight() * mBanDo->GetTileHeight();
	mChieuRongTile = mBanDo->GetTileWidth();
	mChieuCaoTile = mBanDo->GetTileHeight();
	TaiBanDo(in_DuongDan);
}

void BanDoGame::ThietLapCamera(Camera * in_Camera)
{
	mCamera = in_Camera;
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
				VienGach *lVienGach = nullptr;

				if (lNhomObject->GetName() == "GachBinhThuong")
				{
					lVienGach = new GachBinhThuong(lToaDo);
					lVienGach->mLoaiThucThe = eLoaiThucThe::eVienGachVangBinhThuong;
				}
				else if (lNhomObject->GetName() == "GachVang")
				{
					lVienGach = new GachVang(lToaDo);
					lVienGach->mLoaiThucThe = eLoaiThucThe::eVienGachVangAnDuoc;
				}
				mDanhSachVienGach.push_back(lVienGach);

				if (lVienGach != NULL)
				{
					mCayBonNhanh->ThemThucThe(lVienGach);
				}
			}
		}
		else
		{
			for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
			{
				Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

				ThucThe *lThucThe = new ThucThe();
				lThucThe->ThietLapToaDo(float(lObject->GetX() + lObject->GetWidth() / 2.0f),
					float(lObject->GetY() + lObject->GetHeight() / 2.0f));
				lThucThe->ThietLapChieuRong(lObject->GetWidth());
				lThucThe->ThietLapChieuCao(lObject->GetHeight());
				lThucThe->mLoaiThucThe = eLoaiThucThe::eThucTheTinh;

				mCayBonNhanh->ThemThucThe(lThucThe);
			}
		}
	}
#pragma endregion
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
	D3DXVECTOR2 lDoDoi = D3DXVECTOR2(ToanCauGame::iChieuRong() / 2.0f - mCamera->vToaDo().x,
		ToanCauGame::iChieuCao() / 2.0f - mCamera->vToaDo().y);

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

						//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
						//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

						if (mCamera != NULL)
						{
							RECT objRECT;
							objRECT.left = position.x - tileWidth / 2;
							objRECT.top = position.y - tileHeight / 2;
							objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

							if (!VaChamGame::kqvcHCNVaHCN(mCamera->rHCNGioiHan(), objRECT).DaVaCham)
								continue;
						}

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

	for (int i = 0; i < int(mDanhSachVienGach.size()); i++)
	{
		mDanhSachVienGach[i]->Ve(lDoDoi);
	}

#pragma endregion

}


BanDoGame::~BanDoGame()
{
	delete mBanDo;
	delete mCamera;

	for (int i = 0; i < int(mDanhSachTileSet.size()); i++)
	{
		if (mDanhSachTileSet[i])
			delete mDanhSachTileSet[i];
	}
	mDanhSachTileSet.clear();
	
	for (size_t i = 0; i < mDanhSachVienGach.size(); i++)
	{
		if (mDanhSachVienGach[i])
			delete mDanhSachVienGach[i];
	}
	mDanhSachVienGach.clear();

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
	return (mCamera->rHCNGioiHan().left == 0);
}

bool BanDoGame::bCameraChamBienPhai()
{
	return (mCamera->rHCNGioiHan().right == mChieuRong);
}

bool BanDoGame::bCameraChamBienTren()
{
	return (mCamera->rHCNGioiHan().top == 0);
}

bool BanDoGame::bCameraChamBienDuoi()
{
	return (mCamera->rHCNGioiHan().bottom == mChieuCao);
}

std::map<int, HinhAnh*> BanDoGame::sDanhSachTileSet()
{
	return mDanhSachTileSet;
}

std::vector<VienGach*> BanDoGame::vgDanhSachVienGach()
{
	return mDanhSachVienGach;
}

CayBonNhanh * BanDoGame::cbnCayBonNhanh()
{
	return mCayBonNhanh;
}

#pragma endregion