#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : offers(), mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(2) 
{
    // You can change the implementation of the constructor, but not the signature!
}
//rule of 5:

//destructor
Party:: ~Party(){
    if(mJoinPolicy) delete mJoinPolicy;
}

//copy constructor
Party::Party(const Party &other) : offers(), mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), timer(other.timer){
    
}

//copy assignment operator
Party& Party::operator= (const Party &other){
    if(this != &other){
        if(mJoinPolicy) delete mJoinPolicy;
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        mJoinPolicy = other.mJoinPolicy->clone();
    }
    return *this;
}

//move constructor
Party::Party(Party &&other) : offers(), mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), timer(other.timer){
    other.mJoinPolicy = nullptr;
}

//move assignment operator
Party& Party::operator = (Party &&other){
    if(this != &other){
        if(mJoinPolicy) delete mJoinPolicy;
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        this->mJoinPolicy = other.mJoinPolicy;
        mState = other.mState;
    }
    return *this;
};

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
    if(mState == CollectingOffers){
        timer = 2;
    }
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    // TODO: implement this method
    if(mState == CollectingOffers){
        //if count == 0 then accept an offer
        if(timer == 0){
            pair<int,int> choosenPair = mJoinPolicy->choose(s, offers);
            mState = Joined;
            int coalitionIDChosen = choosenPair.first;
            int AgentIDChosen = choosenPair.second;
            s.addPartyToCoalition(mId, coalitionIDChosen, AgentIDChosen); 
        }
        timer--;
    }

}

void Party::getAnOffer(int agentOfferingCoalitionID, int agentOfferingID){
    offers.push_back(make_pair(agentOfferingCoalitionID, agentOfferingID));
    if(getState() == Waiting){
        setState(CollectingOffers);
    }

}
