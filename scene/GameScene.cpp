#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 弾の解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	delete model_;
	delete player_;
	delete debugCamara_;
	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
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

	AddEnemy(pos_);//0,3,50

	// デバッグカメラ
	debugCamara_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 軸方向の表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 弾の更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// プレイヤー更新
	player_->Update();

	enemy_.remove_if([](Enemy* enemy) {
		if (enemy->GetIsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// 敵の更新
	for (Enemy* enemy : enemy_) {
		enemy->Update();
	}

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
	
	// 弾の描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}

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

void GameScene::LoadEnemyPopDate() {

	std::ifstream file;
	file.open("./Resources./enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyPopDate() {



	std::string line;

	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			(Vector3(x, y, z));
		}

		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());



			break;
		}
	}
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { 
	
	bullets_.push_back(enemyBullet); 
}

void GameScene::AddEnemy(Vector3 pos) {
	// 敵
	Enemy* obj = new Enemy;
	obj->Initialize(model_, pos);
	obj->SetPlayer(player_);
	obj->SetGameScene(this);

	enemy_.push_back(obj);
}
