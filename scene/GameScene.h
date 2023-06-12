#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// テクスチャ
	uint32_t textureHandle_ = 0;

	// モデル
	Model* model_ = nullptr;

	// プレイヤー
	Player* player_ = nullptr;
	float radius_ = 50;

	// 敵
	Enemy* enemy_ = nullptr;
	EnemyBullet* enemybullet_ = nullptr;
	float radius2_ = 50;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Vector3 pos_ = {30.0f, 2.0f, 40.0f};

	// デバッグカメラ
	bool isDebugCamaraActive_ = false;
	DebugCamera* debugCamara_ = nullptr;
};
