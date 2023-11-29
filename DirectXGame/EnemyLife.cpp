#include "EnemyLife.h"
#include <cassert>

void EnemyLife::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	for (int i = 0; i < 10; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_.y = 20;
		worldTransform_[i].translation_.z = 100.0f;
		worldTransform_[i].scale_ = {2,2,2};
	worldTransform_[0].translation_.x = -40;
		worldTransform_[1].translation_.x = -30;
	worldTransform_[2].translation_.x = -20;
		worldTransform_[3].translation_.x = -10;
	worldTransform_[4].translation_.x = 0;
		worldTransform_[5].translation_.x = 10;
	worldTransform_[6].translation_.x = 20;
		worldTransform_[7].translation_.x = 30;
		worldTransform_[8].translation_.x = 40;
	worldTransform_[9].translation_.x = 50;

	}
}

void EnemyLife::Update() { 
	
	for (int i = 0; i < 10; i++) {
		worldTransform_[i].UpdateMatrix(); 
	}
}
	

void EnemyLife::Draw(ViewProjection view,int l) { 
		if (l >= 10) {
		model_->Draw(worldTransform_[0], view, textureHandle_);
		}
		if (l >= 9){
		model_->Draw(worldTransform_[1], view, textureHandle_);
		}
		if (l >= 8) {
		model_->Draw(worldTransform_[2], view, textureHandle_);
		}
		if (l >= 7) {
		model_->Draw(worldTransform_[3], view, textureHandle_);
		}
		if (l >= 6) {
		model_->Draw(worldTransform_[4], view, textureHandle_);
		}
		if (l >= 5) {
		model_->Draw(worldTransform_[5], view, textureHandle_);
		}
		if (l >= 4) {
		model_->Draw(worldTransform_[6], view, textureHandle_);
		}
		if (l >= 3) {
		model_->Draw(worldTransform_[7], view, textureHandle_);
		}
		if (l >= 2) {
		model_->Draw(worldTransform_[8], view, textureHandle_);
		}
		if (l >= 1) {
		model_->Draw(worldTransform_[9], view, textureHandle_);
		}
	   
}