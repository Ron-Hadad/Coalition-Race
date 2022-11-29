#include "Agent.h"
#include "Simulation.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : myCoalitionID(agentId), mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    
}

//rule of 5:
Agent::~Agent(){
    if(mSelectionPolicy) delete mSelectionPolicy;
}
Agent::Agent(const Agent &other) : myCoalitionID(other.myCoalitionID), mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone())
{

}

Agent& Agent::operator = (const Agent &other){
    if(this != &other){
        if(mSelectionPolicy) delete mSelectionPolicy;
        myCoalitionID = other.myCoalitionID;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}
Agent::Agent(Agent &&other) : myCoalitionID(other.myCoalitionID), mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy)
{
    other.mSelectionPolicy = nullptr;
}
Agent& Agent::operator = (Agent &&other){
    if(this != &other){
        if(mSelectionPolicy) delete mSelectionPolicy;
        myCoalitionID = other.myCoalitionID;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy;
        other.mSelectionPolicy = nullptr;
    }
    return *this;
};

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

//I added:
void Agent::setAgentID(int newAgentID){
    mAgentId = newAgentID;
}
void Agent::setPartyID(int newPartyID){
    mPartyId = newPartyID;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    int choosenPartyID = mSelectionPolicy->choose(mAgentId,mPartyId, sim);
    if(choosenPartyID != -1){
        sim.getParty(choosenPartyID).getAnOffer(myCoalitionID,mAgentId);   
    }
}



