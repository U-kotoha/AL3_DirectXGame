#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>

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

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void AddEnemy(Vector3 pos);

	// 弾リスト取得
	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

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

	// 敵
	std::list<Enemy*> enemy_;
	std::list<EnemyBullet*> bullets_;
	std::stringstream enemyPopCommands;
	Vector3 pos_ = {20.0f, 2.0f, 30.0f};

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// デバッグカメラ
	bool isDebugCamaraActive_ = false;
	DebugCamera* debugCamara_ = nullptr;

	// レールカメラ
	RailCamera* railCamera_ = nullptr;

	bool isWait_ = false;
	int32_t WaitTimer_;
};
