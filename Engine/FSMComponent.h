#pragma once
#include "Component.h"
#include "State.h"
#include <vector>

template<typename ContextType>
class FSMComponent : public Component {
    using Status = State<ContextType>;

public:
    template<typename StateType>
    StateType* CreateState();

    void Init(Status* initial, ContextType contexte);
    void Update(ContextType contexte);

private:
    std::vector<Status*> states;

    Status* current = nullptr;
	
};

#include "FSMComponent.inl"