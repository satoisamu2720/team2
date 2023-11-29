#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "Boss.h"
#pragma once

class EnemyLife {
public:
	///
	///
	///
	///
	///
	void Initialize(Model* model, uint32_t textureHandle);

	///
	///
	///
	void Update();

	///
	///
	///
	void Draw(ViewProjection view,int t);

private:
	WorldTransform worldTransform_[10];
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	const ViewProjection* viewProjection_ = nullptr;
	Boss* boss_;
};

