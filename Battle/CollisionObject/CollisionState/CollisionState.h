#pragma once

class CollisionObject;

/*

-------------------�X�e�[�g����-------------------------------
Bridge�p�^�[���Ŏ���
���������Ƃ��̏�������Ԃɂ���ĕω�������B


*/

class CollisionState {
public:
	virtual void Judge(CollisionObject* HitObj, CollisionObject* me);/*ID�ɂ�锻��*/
protected:
	virtual void CollisionAlly(CollisionObject* HitObj, CollisionObject* me);
	virtual void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me);
};

class NormalCollisionState :public CollisionState {
};

/*�v���C���[�ƒe���Փ˂����ꍇ�A�v���C���[��HP�����炷*/
class PlayerCollisionState : public CollisionState {
public:
	PlayerCollisionState(float *HP);
	void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) override;

private:
	float *HP;
};