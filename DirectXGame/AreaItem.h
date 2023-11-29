#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include "math.h"
#include "Player.h"
class AreaItem {



	public:
	///
	///
	///
	///
	///
    void Initialize( Model* model, const Vector3& rotation );

	///
	///
	///
	void Update();

	///
	///
	///
	void Draw(ViewProjection view,int t);
	///
	///
	///
	void OnCollision();

	void Random();

	/// <summary>
	///
	/// </summary>
	
	const WorldTransform& GetItemWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;

	Model* modelAreaItem_;

	ViewProjection viewProjection_ ;
	
	float inputFloat[3]{0, 0, 0};
	
	// キャラクターの移動ベクトル

	Vector3 velocity_ = {0, 0, 0};

	Player* player_;


};


