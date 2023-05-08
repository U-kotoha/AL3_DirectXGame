#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ViewProjection.h"

/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet {
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="pos">�������W</param>
	void Initialize(Model* model, const Vector3& pos);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�v���_�N�V����</param>
	void Draw(ViewProjection& view);

private:
	// ���[���h�ϊ�
	WorldTransform world_;
	// ���f��
	Model* model_;
	// �e�N�X�`���n���h��
	uint32_t texturehandle_;
};
