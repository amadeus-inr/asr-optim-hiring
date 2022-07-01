#ifndef MACHINE_H
#define MACHINE_H
#include <vector>

class Machine {
public:
    int id;
    int purchaseDay;
    int purchasePrice;
    int resalePrice;
    int dailyProfit;

public:
    Machine(int id, int purchaseDay, int purchasePrice, int resalePrice, int dailyProfit) :
        id(id),
        purchaseDay(purchaseDay),
        purchasePrice(purchasePrice),
        resalePrice(resalePrice),
        dailyProfit(dailyProfit){
    }

    friend std::ostream& operator<<(std::ostream& out, const Machine& m) {
        return out << "Machine{" << m.id << ", " << m.purchaseDay  << ", " << m.purchasePrice << ", " << m.resalePrice << ", " << m.dailyProfit << "}";
    }

    bool operator < (const Machine& m) const {
        return (purchaseDay < m.purchaseDay);
    }
};
#endif