#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamara_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ
	textureHandle_ = TextureManager::Load("sample.png");

	// モデル
	model_ = Model::Create();

	viewProjection_.Initialize();

	// プレイヤー
	player_ = new Player();
	player_->Initialize(model_, textureHandle_);

	// 敵
	enemy_ = new Enemy();
	enemy_->Initialize(model_, pos_);
	enemy_->SetPlayer(player_);

	// デバッグカメラ
	debugCamara_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 軸方向の表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	// プレイヤー更新
	player_->Update();

	// 敵の更新
	enemy_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_BACKSPACE)) {
		isDebugCamaraActive_ = true;
	}
#endif //_DEBUG

	// デバッグカメラ
	if (isDebugCamaraActive_) {
		debugCamara_->Update();
		viewProjection_.matView = debugCamara_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamara_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// プレイヤー
	player_->Draw(viewProjection_);

	// 敵
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;

	// 自弾リスト
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リスト
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();

		float distance = (posB.x - posA.x) * (posB.x - posA.x) +
		                 (posB.y - posA.y) * (posB.y - posA.y) +
		                 (posB.z - posA.z) * (posB.z - posA.z);

		const float RadiusMix = 10.0f;

		// 球と球の交差判定
		if (distance <= RadiusMix) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
#pragma endregion
}
