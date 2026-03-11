#pragma once

template<typename ContextType>
void FSMComponent<ContextType>::Init(State* initial)
{
    current = initial;
    current->Enter(contexte);
}

template<typename ContextType>
void FSMComponent<ContextType>::Update(float dt)
{
    if (current != nullptr) {
        current->Execute(contexte);

        auto next = current->TryGetNext(contexte);

        if (next)
        {
            current->Exit(contexte);
            current = next;
            current->Enter(contexte);
        }

    }

}

template<typename ContextType>
template<typename StateType>
StateType* FSMComponent<ContextType>::CreateState()
{
    StateType* state = new StateType();
    states.push_back(state);

    return state;
}