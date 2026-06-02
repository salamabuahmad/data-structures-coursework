#ifndef PIRRATES
#define PIRRATES
#include "wet1util.h"
#include <memory>
using namespace std;

class Ship;

class Pirate {
    private: 
        int m_pirateID;
        int m_treasure;
        int m_key;
        shared_ptr<Ship> m_motherShip;

    public:
        Pirate(int pirateID, shared_ptr<Ship> motherShip, int treasure = 0) : m_pirateID(pirateID) , m_motherShip(motherShip), m_treasure(treasure), m_key(0){};
        ~Pirate() = default;
        Pirate(const Pirate&) = delete;
        Pirate operator= (const Pirate&) = delete;

        int getPirateID() const;
        int getKey() const;
        void setKey(int);
        int getPirateTreasure() const;
        void setPirateTreasure(int);
        void increaseTreasure(int);
        shared_ptr<Ship> getMotherShip() const;
        void setMotherShip(shared_ptr<Ship>);



};

// remove get treasure pointer


#endif // PIRRATES