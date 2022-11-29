#pragma once
#include <vector>
using std::vector;
using namespace std;
class Simulation;


class JoinPolicy {
    public: 
    virtual pair<int, int> choose(Simulation &s,vector <pair<int, int>> offers) = 0;
    virtual~JoinPolicy() = default;
    virtual JoinPolicy* clone() = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public: pair<int, int> choose(Simulation &s,vector <pair<int, int>> offers);
    JoinPolicy* clone();
    
};

class LastOfferJoinPolicy : public JoinPolicy {
    public: pair<int, int> choose(Simulation &s,vector <pair<int, int>> offers);
    JoinPolicy* clone();
};