#include "SelectionPolicy.h"
#include "Simulation.h"

SelectionPolicy* MandatesSelectionPolicy::clone(){ return new MandatesSelectionPolicy() ; }
SelectionPolicy* EdgeWeightSelectionPolicy::clone(){ return new EdgeWeightSelectionPolicy() ; }

int MandatesSelectionPolicy::choose(int mAgentId, int agentPartyID, Simulation &s)
{   
    int maxMandats = 0;
    int choosenPartyID = -1;

    int numOfParties = s.getGraph().getNumVertices();
    for(int i = 0; i < numOfParties; i++){
        //if its not me and we do have a connection::
        int edgeWeight = s.getGraph().getEdgeWeight(agentPartyID, i);
        bool notJoined = (s.getParty(i).getState() != Joined);
        if((i != agentPartyID) & (edgeWeight != 0) & notJoined){
            unsigned j = 0;
            bool notOfferedBefore = true;
            while((j<s.getParty(i).offers.size()) & (notOfferedBefore))
            {
               if(((s.getParty(i).offers[j].first) == (s.getAgents()[mAgentId].myCoalitionID))){
                    notOfferedBefore = false;
               }
               j++;
            }
            int iMandats = s.getParty(i).getMandates();
            if((iMandats > maxMandats) & (notOfferedBefore)){
                    maxMandats = iMandats;
                    choosenPartyID = i;
            }
        }    
        
    }
    return(choosenPartyID);
}

int EdgeWeightSelectionPolicy::choose(int mAgentId, int agentPartyID, Simulation &s)
{
    int maxWeight = 0;
    int choosenPartyID = -1;

    int numOfParties = s.getGraph().getNumVertices();
    for(int i = 0; i < numOfParties; i++){
        //if its not me :
        bool notJoined = (s.getParty(i).getState() != Joined);
        if((i != agentPartyID) & notJoined){
            unsigned j = 0;
            bool notOfferedBefore = true;
            while((j<s.getParty(i).offers.size()) & (notOfferedBefore))
            {
               if(((s.getParty(i).offers[j].first) == (s.getAgents()[mAgentId].myCoalitionID))){
                    notOfferedBefore = false;
               }
               j++;
            }
            int edgeWeight = s.getGraph().getEdgeWeight(agentPartyID, i);
            if((edgeWeight > maxWeight) & (notOfferedBefore)){
                maxWeight = edgeWeight;
                choosenPartyID = i;
            }
        }    
        
    }
    return(choosenPartyID);
}
