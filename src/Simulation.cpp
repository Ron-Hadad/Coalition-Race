#include "Simulation.h"
using std::vector;
#include <vector>

Simulation::Simulation(Graph graph, vector<Agent> agents) : coalitions(), numOfPartiesJoined(), largestCoalitionMandats(),  mGraph(graph), mAgents(agents) 
{
    // You can change the implementation of the constructor, but not the signature!
    //run on agents and create new coalitions, 
    //counting the number of prties alreadt in 'joined' state
    //cheking for the biggest size of a coalition
    numOfPartiesJoined = mAgents.size();
    largestCoalitionMandats = 0;
    for(unsigned j = 0; j < mAgents.size(); j++){
        Agent iter = mAgents[j];
        int newCoalitionMandats = getParty(iter.getPartyId()).getMandates();
        coalitions.push_back(coalition(iter.getId(), newCoalitionMandats, iter.getPartyId()));
        if(newCoalitionMandats > largestCoalitionMandats){
            largestCoalitionMandats = newCoalitionMandats;
        }
    }
}

void Simulation::step()
{
    // TODO: implement this method
    for(int i = 0; i < mGraph.getNumVertices(); i++){
        Party &p = mGraph.getParty(i);
        p.step(*this);
    }
    for(unsigned j = 0; j < mAgents.size(); j++){
        Agent &a = mAgents[j];
        a.step(*this);
        
    }

}

void Simulation::addPartyToCoalition(int partyJoiningID, int coalitionID, int agentOfferingID){
    //finding the coalition:
    int i = 0;
    while(coalitions[i].myID != coalitionID){
        i++;
    }
    //adding the party to the coalition:
    coalitions[i].partyIDsInCoalition.push_back(partyJoiningID);
    coalitions[i].myMandats = coalitions[i].myMandats + getParty(partyJoiningID).getMandates();
    //cloning the agent + chainging the needed fields:
    int j = 0;
    while(mAgents[j].getId() != agentOfferingID){
        j++;
    }
    Agent clone = mAgents[j];
    clone.setAgentID(mAgents.size());
    clone.setPartyID(partyJoiningID);
    mAgents.push_back(clone);
    //counting one more party in a 'joined' state:
    numOfPartiesJoined++;
    //updating the biggest coalition:
    if(coalitions[i].myMandats > largestCoalitionMandats){
        largestCoalitionMandats = coalitions[i].myMandats;
    }
    
}

bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    if((numOfPartiesJoined == mGraph.getNumVertices()) | (largestCoalitionMandats > 60)){
       return true; 
    }
    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getAgents() 
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int PartyId)
{
    return mGraph.getParty(PartyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    vector<vector<int>> coalitionSumUp;
    unsigned i = 0;
    while(i < coalitions.size()){
        vector<int> coalToAdd = coalitions[i].partyIDsInCoalition;
        coalitionSumUp.push_back(coalToAdd);
        i++;
    }
    
    return coalitionSumUp;
}
