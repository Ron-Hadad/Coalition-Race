#pragma once
class Simulation;

class SelectionPolicy 
{
    public: 
        virtual int choose(int mAgentId, int agentPartyID, Simulation &s) = 0;
        virtual~SelectionPolicy() = default;
        virtual SelectionPolicy* clone() = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
    public:
        int choose(int mAgentId, int agentPartyID, Simulation &s) ;
        SelectionPolicy* clone();
};


class EdgeWeightSelectionPolicy: public SelectionPolicy
{ 
    public:
        int choose(int mAgentId, int agentPartyID, Simulation &s) ;
        SelectionPolicy* clone();
};

