#pragma once
//class Enemy;
class Wall;
class EmptySpace;
class Knight;
class Enemy;
class Princess;
class GameObject {
	char sym;
public:
	GameObject(char s);
	GameObject();
	//virtual bool Collision(Enemy& enemy) = 0;
	virtual bool Collision(EmptySpace& emptySpace) = 0;
	virtual bool Collision(GameObject& obj) = 0;
	virtual bool Collision(Wall& wall) = 0;
	virtual bool Collision(Knight& knight) = 0;
	virtual bool Collision(Princess& princess) = 0;

	char GetSym();
	void SetSym(char s);
};