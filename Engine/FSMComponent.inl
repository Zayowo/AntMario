#pragma once

template<typename ContextType>
void FSMComponent<ContextType>::Init(State* initial)
{
    current = initial;
    current->Enter(context);
}

template<typename ContextType>
void FSMComponent<ContextType>::Update(float dt)
{
    if (current != nullptr) {
        current->Execute(context);

        auto next = current->TryGetNext(context);

        if (next)
        {
            current->Exit(context);
            current = next;
            current->Enter(context);
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

template<typename ContextType>
ContextType& FSMComponent<ContextType>::GetContext()
{

    return context;

}