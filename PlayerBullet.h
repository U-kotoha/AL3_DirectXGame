#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="pos">初期座標</param>
	void Initialize(Model* model, const Vector3& pos);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュープロダクション</param>
	void Draw(ViewProjection& view);

private:
	// ワールド変換
	WorldTransform world_;
	// モデル
	Model* model_;
	// テクスチャハンドル
	uint32_t texturehandle_;
};
