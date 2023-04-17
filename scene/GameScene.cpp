#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	delete sprite_;
	delete model_; 
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャ
	textureHandle_ = TextureManager::Load("sample.png");

	//スプライト
	sprite_ = Sprite::Create(textureHandle_, {100, 450});

	//モデル
	model_ = Model::Create();

	//行列初期化
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//サウンド
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	audio_->PlayWave(soundDataHandle_);
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	//ライン
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	//デバッグカメラ
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	//軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() 
{ 
	//スプライト移動
	Vector2 position = sprite_->GetPosition();
	position.x += 1.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);

	//サウンド
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
	}

	//デバッグ
	ImGui::Begin("Debug");
	ImGui::Text("Ubukata Kotoha %d.%d.%d", 2023, 4, 17);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
	//デモウィンドウ
	ImGui::ShowDemoWindow();

	// デバッグカメラ
	debugCamera_->Update();
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
	
	//ライン
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {50, 50, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

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

	//モデル
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//スプライト
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
