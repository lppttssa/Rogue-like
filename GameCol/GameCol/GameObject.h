#pragma once
//class Enemy;
class Wall;
class EmptySpace;
class Knight;
class Enemy;
class Princess;
class Fireball;
class AidKit;
class GameObject {
	char sym;
public:
	GameObject(char s);
	GameObject();
	virtual int Collision(Enemy& enemy) = 0;
	virtual int Collision(EmptySpace& emptySpace) = 0;
	virtual int Collision(GameObject& obj) = 0;
	virtual int Collision(Wall& wall) = 0;
	virtual int Collision(Knight& knight) = 0;
	virtual int Collision(Princess& princess) = 0;
	virtual int Collision(Fireball& fireball) = 0;
	virtual int Collision(AidKit& aidKit) = 0;

	char GetSym();
	void SetSym(char s);

};