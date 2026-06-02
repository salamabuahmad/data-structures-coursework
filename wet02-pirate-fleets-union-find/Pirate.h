#ifndef PIRATE_H
#define PIRATE_H

#include <memory>
using namespace std;

class Fleet;

class Pirate {
    private: 
        int m_pirateID;
        int m_rank;
        int m_money;
        weak_ptr<Fleet> m_motherFleet;
    public:
        Pirate(int pirateID, int rank, weak_ptr<Fleet> fleet,int money = 0) : m_pirateID(pirateID), m_rank(rank), m_money(money), m_motherFleet(fleet){}
        ~Pirate() = default;
        Pirate(const Pirate&) = delete;
        Pirate operator= (const Pirate&) = delete;

        int getID() const;
        int getRank() const;
        void setRank(int);
        int getMoney() const;
        void setMoney(int);
        void increaseMoney(int);
        shared_ptr<Fleet> getFleet() const;
        void setFleet(shared_ptr<Fleet>);
};
#endif // PIRRATE