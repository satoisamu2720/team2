#include "AreaItem.h"
#include<time.h>

void AreaItem::Initialize(Model* model, const Vector3& position) {
	assert(model);
	modelAreaItem_ = model;
	worldTransform_.Initialize();
	//viewProjection_.translation_ = position;
	worldTransform_.translation_ = position;
	
}

void AreaItem::Update() {
	// 行列更新
	//Random();
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

void AreaItem::Random() {
	//場所ランダムにする
	time_t currentTime = time(nullptr);
	srand((unsigned int)currentTime);
	

	worldTransform_.translation_.x = (float)(rand() % 1600 - 800); // ランダムな数字今1-6
	    worldTransform_.translation_.y = 0;
	worldTransform_.translation_.z = (float)(rand() % 1600-800); // ランダム
}
