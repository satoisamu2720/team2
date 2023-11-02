#include "Boss.h"

void Boss::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);
	 model_= model;

	worldTransform_.Initialize();
	 worldTransform_.scale_ = {0.1f, 0.1f, 0.1f};
}

void Boss::Update() {}

void Boss::Draw(const ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_);
}
