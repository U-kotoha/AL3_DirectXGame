﻿#pragma once

#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	// 衝突時コールバック関数
	void OnCollision();
	
	// ワールド座標
	Vector3 GetWorldPosition();

	// 弾リスト取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	// ワールド
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャ
	uint32_t textureHandle_ = 0;
	// キーボード入力
	Input* input_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;

};
