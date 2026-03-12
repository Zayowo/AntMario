#pragma once
#include <functional>
template<typename ContextType>
class State
{
    using Condition = std::function<bool(ContextType&)>;
    using _State = State<ContextType>;

public:    
    virtual ~State() = default;

    virtual void Enter(ContextType& context) {}
    virtual void Execute(ContextType& context, float dt) {} // Execute == Update
    virtual void Exit(ContextType& context) {}

    void AddTransition(Condition condition, _State* newState);

    State<ContextType>* TryGetNext(ContextType& context);

private:
    std::vector<std::pair<Condition, _State*>> transitions;
};

#include "State.inl"