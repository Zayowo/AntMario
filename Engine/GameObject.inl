#pragma once

template<typename ComponentType>
ComponentType* GameObject::GetComponent() {
	for (Component* component : components) {
		if (ComponentType* componentType = dynamic_cast<ComponentType*>(component)) {
			return componentType;
		}
	}

	return nullptr;

}

template<typename ComponentType, typename... Param>
ComponentType* GameObject::AddComponent(Param... parameters)
{
	
	ComponentType* component = new ComponentType(parameters...);
	component->owner = this;
	components.emplace_back(component);
	return component;

}