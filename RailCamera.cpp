﻿#include "RailCamera.h"
#include "ImGuiManager.h"

void RailCamera::Initialize(Vector3 trans, Vector3 rot) {

	worldTransform_.Initialize();
	worldTransform_.translation_ = trans;
	worldTransform_.rotation_ = rot;

	// ビュープロジェクション初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update() {

	Vector3 move{0.0f, 0.0f, 0.0f};
	Vector3 rot{0.0f, 0.001f, 0.0f};

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z -= move.z;

	worldTransform_.rotation_.x += rot.x;
	worldTransform_.rotation_.y += rot.y;
	worldTransform_.rotation_.z += rot.z;

	worldTransform_.UpdateMatrix();

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();

	ImGui::Begin("Camera");
	float sliderTrans3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("Camera.Translation", sliderTrans3, -20.0f, 20.0f);
	worldTransform_.translation_ = {sliderTrans3[0], sliderTrans3[1], sliderTrans3[2]};
	float sliderRot3[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	ImGui::SliderFloat3("Camera.Rotation", sliderRot3, -20.0f, 20.0f);
	worldTransform_.rotation_ = {sliderRot3[0], sliderRot3[1], sliderRot3[2]};
	ImGui::End();
}
