#ifndef INSTANCE_H
#define INSTANCE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "machine.h"

class Instance {
public:
    int id;
    int nbMachines;
    int initMoney;
    int nbDays;
    std::vector<Machine> machines;

public:
    Instance(int id, int nbMachines, int initMoney,int nbDays,  std::vector<Machine> machines) :
        id(id),
        nbMachines(nbMachines),
        nbDays(nbDays),
        initMoney(initMoney),
        machines(machines){
    }

    friend std::ostream& operator<<(std::ostream& out, const Instance& i) {
        out << "Instance{" << i.id << ", " << i.nbMachines  << ", " << i.initMoney << ", " << i.nbDays << "}\nMachines\n";
        for (const auto& machine: i.machines) out << machine << "\n";
        return out;
    }

};
#endif