#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

#include "coalition.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getParty(int PartyId);
    const vector<vector<int>> getPartiesByCoalitions() const;

    //I added:
    vector<Agent> &getAgents();
    vector<coalition> coalitions;
    void addPartyToCoalition(int partyJoiningID, int colitionID, int agentOfferingID);
    int numOfPartiesJoined;
    int largestCoalitionMandats;

private:
    Graph mGraph;
    vector<Agent> mAgents;
};
