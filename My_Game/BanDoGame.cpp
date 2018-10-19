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

#pragma region Ve TileSet
	for (int i = 0; i < mBanDo->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *lLopHinhAnh = mBanDo->GetTileLayer(i);

		if (!lLopHinhAnh->IsVisible())
		{
			continue;
		}

		for (int m = 0; m < lLopHinhAnh->GetHeight(); m++)
		{
			for (int n = 0; n < lLopHinhAnh->GetWidth(); n++)
			{
				// Kiểm tra xem Ảnh Lát Gạch (có tọa độ trong Bản Đồ) này có cần vẽ lên hay không
				D3DXVECTOR3 lToaDo(float(n * mChieuRongTile + mChieuRongTile / 2.0f),
					float(m * mChieuCaoTile + mChieuCaoTile / 2.0f), float(0.0f));
				if (mCamera != NULL)
				{
					RECT objRECT;
					objRECT.left = long(lToaDo.x - mChieuRongTile / 2.0f);
					objRECT.top = long(lToaDo.y - mChieuCaoTile / 2.0f);
					objRECT.right = objRECT.left + mChieuRongTile;
					objRECT.bottom = objRECT.top + mChieuCaoTile;

					if (!VaChamGame::kqvcHCNVaHCN(mCamera->rHCNGioiHan(), objRECT).DaVaCham)
						continue;
				}

				int lViTriIndexCuaTileSet = lLopHinhAnh->GetTileTilesetIndex(n, m);
				if (lViTriIndexCuaTileSet != -1)
				{
					// từ vị trí Index của TileSet ta lấy ra hình ảnh của nó
					HinhAnh* lHinhAnh = mDanhSachTileSet[lViTriIndexCuaTileSet];
					int lSoTileChieuNgangCuaTileSet = lHinhAnh->iChieuRong() / mChieuRongTile;

					int lViTriCuaTileTrongTileSet = lLopHinhAnh->GetTileId(n, m);

					int lX = lViTriCuaTileTrongTileSet / lSoTileChieuNgangCuaTileSet;
					int lY = lViTriCuaTileTrongTileSet - lX * lSoTileChieuNgangCuaTileSet;

					RECT lHCN;
					lHCN.left = lX * mChieuRongTile;
					lHCN.right = lHCN.left + mChieuRongTile;
					lHCN.top = lY * mChieuCaoTile;
					lHCN.bottom = lHCN.top + mChieuCaoTile;

					lHinhAnh->ThietLapToaDo(lToaDo);
					lHinhAnh->ThietLapChieuRong(mChieuRongTile);
					lHinhAnh->ThietLapChieuCao(mChieuCaoTile);
					lHinhAnh->ThietLapHCN(lHCN);
					lHinhAnh->ThietLapDoDoi(lDoDoi);
					lHinhAnh->Ve();
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