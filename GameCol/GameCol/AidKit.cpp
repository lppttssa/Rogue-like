#include "AidKit.h"
#include "Knight.h"
#include "Fireball.h"

AidKit::AidKit(int h) : GameObject('+'), hp(h) {};

int AidKit::GetAidHp() {
	return hp;
}

int AidKit::Collision(Wall& wall) {
	return 0;
}

int AidKit::Collision(GameObject& gameObj) {
	return gameObj.Collision(*this);
}

int AidKit::Collision(EmptySpace& emptySpace) {
	return 0;
}

int AidKit::Collision(Knight& knight) {
	knight.SetHp(knight.GetHp() + GetAidHp());
	if (knight.GetHp() > knight.GetMaxHp()) {
		knight.SetHp(knight.GetMaxHp());
	}
	return 2; 
}

int AidKit::Collision(Princess& princess) {
	return 0;
}

int AidKit::Collision(Enemy& enemy) {
	return 0;
}

int AidKit::Collision(Fireball& fireball) {
	fireball.SetHp(0);
	return 3;
}
int AidKit::Collision(AidKit& aidKit) {
	return 0;
}