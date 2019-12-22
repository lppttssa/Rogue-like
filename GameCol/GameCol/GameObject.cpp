#include "GameObject.h"

GameObject::GameObject(char s) : sym(s) {};
GameObject::GameObject() {};


char GameObject::GetSym() {
	return sym;
}

void GameObject::SetSym(char s) {
	sym = s;
}

