#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include <cassert>
class Player {
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
