#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	// �s��X�V
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// �s��]��
	TransferMatrix();
}