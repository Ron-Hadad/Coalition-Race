#include "coalition.h"

coalition::coalition(int ID, int numOfMandats, int firstPartyId) : myID(ID), myMandats(numOfMandats), partyIDsInCoalition()
{
    partyIDsInCoalition.push_back(firstPartyId);
}
