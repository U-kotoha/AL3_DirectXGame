#include "Player.h"
#include "assert.h"

void Player::Initialize(Model* model, uint32_t textureHandle) 
{ 
	//NULLチェック
	assert(model);

	//受け渡し
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールド初期化
	worldTransform_.Initialize();
}

void Player::Update() 
{ 
	//行列転送
	worldTransform_.TransferMatrix(); 
}

void Player::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}