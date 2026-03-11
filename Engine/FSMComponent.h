#pragma once
#include "Component.h"
#include "State.h"
#include <vector>

template<typename ContextType>
class FSMComponent : public Component {
    using State = State<ContextType>;

public:
    void Init(State* initial);
    void Update(float dt) override;

    template<typename StateType>
    StateType* CreateState();

private:
    std::vector<State*> states;
    ContextType context;
    State* current = nullptr;
	
};

#include "FSMComponent.inl"