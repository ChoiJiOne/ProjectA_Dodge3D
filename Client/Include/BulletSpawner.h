#pragma once

#include "GameObject.h"


/**
 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
 */
class BulletSpawner : public GameObject
{
public:
	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	BulletSpawner() = default;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~BulletSpawner();


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BulletSpawner);


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트를 초기화합니다.
	 * 
	 * @param location 플레이어가 피해야 할 총알을 생성하는 오브젝트의 월드 상 위치입니다. 
	 */
	void Initialize(const Vector3f& location);


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;
};