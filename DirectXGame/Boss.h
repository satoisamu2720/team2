#pragma once
#include <Model.h>
#include <cassert>
#include<WorldTransform.h>

class Boss {
public:
	void Initialize(Model*model);
	void Update();
	void Draw(const ViewProjection& viewProjection_);

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
};
