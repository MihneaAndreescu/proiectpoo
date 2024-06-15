#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectUpdateInfo.h"
#include <memory>

class GameObject : public sf::Drawable {
private:
	static int idNow;
	int m_id;
public:
	void dummy() {

	}
	GameObject();
	int getId();
	virtual void update(ObjectUpdateInfo m_drawInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects = {}) = 0;
	virtual void prepDraw() = 0;
};

