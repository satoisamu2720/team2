#include "Skydome.h"

void Skydome::Initialize(Model* model) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.9f, 0.9f, 0.9f};
	worldTransform_.UpdateMatrix();
}

void Skydome::Update() { 
	
}

void Skydome::Draw(ViewProjection& view) { 
	model_->Draw(worldTransform_, view); }