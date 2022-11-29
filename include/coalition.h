#include <vector>
using std::vector;

class coalition{   
    public:
        coalition(int ID, int mandats, int firstPartyId);
        int myID;
        int myMandats;
        vector<int> partyIDsInCoalition;
};