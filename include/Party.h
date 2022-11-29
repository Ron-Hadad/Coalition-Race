#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;
using namespace std;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    //rule of 5:
    virtual ~Party();   //destructor
    Party(const Party &other);    // copy constructor
    Party& operator = (const Party &other);    // copy assignment operator
    Party(Party &&other);   //move constructor
    Party& operator = (Party &&other);    //move assignment operator

    //offers collector:
    vector <pair<int, int>> offers ;
    //function for adding an offer:
    void getAnOffer(int agentOfferingCoalitionID, int agentOfferingID);



    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    //timer:
    int timer;
};
