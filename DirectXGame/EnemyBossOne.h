﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "VectraCalculation.h"
#include "AreaItem.h"
#include <cassert>
#include <list>
#include "math.h"
class EnemyBossOne {

	public:
	
	void Initialize(Model* model, const Vector3& position);


	void Update();

	
	void Draw(ViewProjection view, int t);
	

	/// <summary>
	///
	/// </summary>

	//const WorldTransform& GetItemWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;

	Model* modelEnemyBossOne_;

	ViewProjection viewProjection_;

	AreaItem* areaItem_;

};
