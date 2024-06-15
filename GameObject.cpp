#include "GameObject.h"

int GameObject::idNow = 0;

int GameObject::getId() {
	return m_id;
}

GameObject::GameObject() {
	m_id = idNow++;
}