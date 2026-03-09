#pragma once

template<typename ContextType>
template<typename StateType>
StateType* FSMComponent<ContextType>::CreateState()
{
    StateType* state = new StateType();
    states.push_back(state);

    return state;
}


template<typename ContextType>
void FSMComponent<ContextType>::Init(Status* initial, ContextType contexte)
{
    current = initial;
    current->Enter(contexte);
}

template<typename ContextType>
void FSMComponent<ContextType>::Update(ContextType contexte)
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