#pragma once

#include <vector>
#include "SelectionPolicy.h"


class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    //rule of 5:
    virtual ~Agent();   //destructor
    Agent(const Agent &other);    // copy constructor
    Agent& operator = (const Agent &other);    // copy assignment operator
    Agent(Agent &&other);   //move constructor
    Agent& operator = (Agent &&other);    //move assignment operator

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);

    // I added:
    int myCoalitionID;
    void setAgentID(int newAgentID);
    void setPartyID(int newPartyID);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
