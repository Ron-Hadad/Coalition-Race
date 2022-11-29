#include "JoinPolicy.h"
#include <iterator>
#include "Simulation.h"

pair<int, int> MandatesJoinPolicy::choose(Simulation &s,vector <pair<int, int>> offers){
    pair<int, int> choosenPair = offers[0];
    unsigned i = 0;
    while(i < offers.size()){
        if(s.coalitions[choosenPair.first].myMandats < s.coalitions[offers[i].first].myMandats ){
            choosenPair = offers[i];
        }
        i++;
    }
    return(choosenPair);
}

JoinPolicy* MandatesJoinPolicy::clone(){ return new MandatesJoinPolicy() ; }
JoinPolicy* LastOfferJoinPolicy::clone(){ return new LastOfferJoinPolicy() ; }

pair<int, int> LastOfferJoinPolicy::choose(Simulation &s,vector <pair<int, int>> offers){
    pair<int, int> choosenPair = offers.back();
    return(choosenPair);
}