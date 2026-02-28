#pragma once
#include "Component.h"
#include <tuple>
#include <string>


class Entity
{
	friend class EntityManager;
	std::tuple<cTransform, cSprite, cAnimation, cBoundingBox, cInput, cGravity> m_components;
	std::string m_tag;
	bool m_isActive;
	int m_id;

	Entity(std::string tag, int id) {
		m_tag = tag;
		m_id = id;
		m_isActive = true;
	}

public:
	void destroy();
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	};
	template <typename T>
	bool hasComponent() const { return std::get<T>(m_components).has;};
	template <typename T>
	T& getComponent() { return std::get<T>(m_components); };
	template <typename T>
	void removeComponent() {
		auto& component = getComponent<T>();
		component.has = false;
	};
	std::string& getTag();
	int getID();
};

