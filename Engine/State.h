#pragma once
#include <functional>
template<typename ContextType>
class State
{
    using Condition = std::function<bool(ContextType)>;
    using _State = State<ContextType>;

public:    
    virtual ~State() = default;

    virtual void Enter(ContextType& contexte) {}
    virtual void Execute(ContextType& contexte) {} // Execute == Update
    virtual void Exit(ContextType& contexte) {}

    void AddTransition(Condition condition, _State* newState);

    State<ContextType>* TryGetNext(ContextType& contexte);

private:
    std::vector<std::pair<Condition, _State*>> transitions;
};

#include "State.inl"