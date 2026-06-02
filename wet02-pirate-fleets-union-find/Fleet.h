#ifndef FLEET_H
#define FLEET_H

#include "wet2util.h"
#include "HashTable.h"
#include <memory>
#include "Pirate.h"
using namespace std;


class Fleet{
    private:
        int m_fleetID;
        int m_shipsAmount;
        int m_piratesAmount;
        int m_fleetCounter;
        int m_rankDifference;
        shared_ptr<HashTable<int,shared_ptr<Pirate>>> m_pirateHash;
        shared_ptr<Fleet> m_motherFleet;

    public:
        Fleet(int fleetID): m_fleetID(fleetID), m_shipsAmount(1), m_piratesAmount(0), m_fleetCounter(0), m_rankDifference(0),m_pirateHash(make_shared<HashTable<int,shared_ptr<Pirate>>>()), m_motherFleet(nullptr){}
        ~Fleet() = default;
        Fleet(const Fleet&) = delete;
        Fleet operator= (const Fleet&) = delete;

        int getID() const;
        int getShipsAmount() const;
        void addShips(int);
        int getPiratesAmount() const;
        void addMultiplePirates(int);
        void addPirate(shared_ptr<Pirate>);
        shared_ptr<Fleet> getMotherFleet() const;
        void setMotherFleet(shared_ptr<Fleet>);
        int getCounter() const;
        void setCounter(int);
        int getRankDifference() const;
        void increaseRankDifference(int);
        bool isUsed() const;
 
};



// if getMotherFleet != nullptr, then the Fleet doesn't exist!


#endif // FLEET