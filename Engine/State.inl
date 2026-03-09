
template<typename ContextType>
void State<ContextType>::AddTransition(Condition condition, Statut* newState)
{
    transitions.emplace_back(std::make_pair(condition, newState));
}

template<typename ContextType>
State<ContextType>* State<ContextType>::TryGetNext(ContextType contexte)
{
    for (auto& transition : transitions)
    {
        if (transition.first(contexte))
            return transition.second;
    }

    return nullptr;
}