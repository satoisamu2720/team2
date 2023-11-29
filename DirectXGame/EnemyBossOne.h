#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "VectraCalculation.h"
#include "AreaItem.h"
#include <cassert>
#include <list>
#include "math.h"
class EnemyBossOne {

	public:
	
	void Initialize(Model* model, Model* modelB, const Vector3& position);


	void Update(int t);

	
	void Draw(ViewProjection view, int t,int h);
	
	Vector3 GetWorldPosition();
	/// <summary>
	///
	/// </summary>

	const WorldTransform& GetItemWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;

	Model* modelEnemyBossOne_[2];

	ViewProjection viewProjection_;

	AreaItem* areaItem_;

};
