#include "AreaItem.h"

void AreaItem::Initialize(Model* model, const Vector3& position) {
	assert(model);
	modelAreaItem_ = model;
	worldTransform_.Initialize();
	//viewProjection_.translation_ = position;
	worldTransform_.translation_ = position;
	
}

void AreaItem::Update() {
	// 行列更新
	worldTransform_.UpdateMatrix();
	//worldTransform_.translation_ = Add(worldTransform_.translation_, viewProjection_.translation_);
	
}





void AreaItem::Draw(ViewProjection view,int t) { 
	if (t == 1) {
		modelAreaItem_->Draw(worldTransform_, view);
	}
}

void AreaItem::OnCollision() { 
		
}
