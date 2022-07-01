#ifndef SOLUTION_H
#define SOLUTION_H

#include "../debug.h"
#include <math.h>
#include <string>
#include <vector>

#include "instance.h"

class Solution {
public:
    int    nbMachines;
    int    initMoney;
    int    nbDays;
    int    currentNbMachines;        // current number of machines bought in the solution
    std::vector<int> chosenMachines; // machines that we choose
    std::vector<int> resaleDays;     // day of resale for each machine. default 0
    std::vector<int> profit;         // profit for every day
    int totalProfit;                 // profit at the end -> what we are looking to maximize
    bool isAcceptable;               // boolean indicating if the solution is acceptable, i.e profit >=0 for every day

public:
    Solution(const Instance &instance) {
        nbMachines = instance.nbMachines;
        initMoney = instance.initMoney;
        nbDays = instance.nbDays;
        currentNbMachines = 0;
        chosenMachines = std::vector<int>(nbMachines, 0);
        resaleDays = std::vector<int>(nbMachines, 0);
        profit   = std::vector<int> (nbDays+1, initMoney); 
        totalProfit = profit.back();
        isAcceptable = true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Solution& s) {
        out << "Solution {" << s.nbMachines  << ", " << s.initMoney << ", " << s.nbDays << ", " << s.currentNbMachines << "}\nChosen machines: ";
        for (const auto& i: s.chosenMachines) out << i << "  ";
        out << "\nResale days: ";
        for (const auto& i: s.resaleDays) out << i << " ";
        out << "\nProfit: \n";
        for (const auto& i: s.profit) out << i << "  ";
        out << "\nIs acceptable ? " << s.isAcceptable;
        out << "\nFinal profit = " << s.totalProfit << "\n\n";
        return out;
    }

    void checkIsAcceptable() {
        isAcceptable = true;
        for (int i=0; i<profit.size(); i++){
            if (profit[i] < 0) {isAcceptable = false;}
        }
    }

    void addMachine(int position, const Instance &instance) {
        // Checking that another machine has not been bought the same day
        for (int j=0; j<nbMachines; j++){
            if (j!= position & chosenMachines[j]==1) {
                if (instance.machines[j].purchaseDay == instance.machines[position].purchaseDay) {
                    #ifdef DEBUG
                    std::cout << "ERROR: another machine has been bought on the same day" << std::endl;
                    #endif
                    return;
                }
            }
        }
        if (position >= nbMachines) {
            #ifdef DEBUG
            std::cout << "ERROR: position must not exceed the total number of machines" << std::endl;
            #endif
        }
        else if (chosenMachines[position] == 1) {
            #ifdef DEBUG
            std::cout << "ERROR: machine already bought" << std::endl;
            #endif
        }
        else {
            Machine machine = instance.machines[position];
            int purchaseDay = machine.purchaseDay;

            // Was there a machine before ?
            int prevDailyProfit = 0;
            int prevResalePrice = 0;
            int prevResaleDay = 0;
            for (int j=position-1; j>=0; j--){
                if (chosenMachines[j] == 1) {
                    prevDailyProfit = instance.machines[j].dailyProfit;
                    prevResalePrice = instance.machines[j].resalePrice;
                    prevResaleDay = resaleDays[j];
                    resaleDays[j] = machine.purchaseDay;
                    break;
                }
            }
            int resaleDay = nbDays;
            for (int j=position+1; j<=nbMachines; j++) {
                if (chosenMachines[j] == 1) {
                    resaleDay = instance.machines[j].purchaseDay;
                    break;
                }
            }
            resaleDays[position] = resaleDay;

            // Modify profit  
            int diffProfit = prevResalePrice - machine.purchasePrice - prevDailyProfit;
            profit[machine.purchaseDay] += diffProfit;
            for (int i=machine.purchaseDay+1; i<resaleDay; i++) {
                diffProfit += machine.dailyProfit - prevDailyProfit;
                profit[i] += diffProfit;
            }
            if (resaleDay<= nbDays) diffProfit +=  machine.resalePrice;
            if (prevResaleDay != 0 ) { 
                diffProfit -= prevResalePrice;
            }
            for (int i=resaleDay; i<=nbDays; i++) profit[i] += diffProfit;
            // the end: updating everything and check acceptability
            chosenMachines[position] = 1;
            currentNbMachines += 1;
            checkIsAcceptable();
            totalProfit = profit.back();
        }
    }

    void destroyMachine(int position, const Instance &instance) {
        if (position >= nbMachines) {
            #ifdef DEBUG
            std::cout << "ERROR: position must not exceed the total number of machines" << std::endl;
            #endif
        }
        else if (chosenMachines[position] == 0) {
            #ifdef DEBUG
            std::cout << "ERROR: machine not already bought" << std::endl;
            #endif
        }
        else {
            Machine machine = instance.machines[position];
            int resaleDay = resaleDays[position];
            resaleDays[position] = 0;

            // Was there a previous machine ?
            int prevDailyProfit = 0;
            int prevResalePrice = 0;
            int prevMachine = 0;
            for (int j=position; j>=0; j--){
                if (chosenMachines[j] == 1) {
                    prevDailyProfit = instance.machines[j].dailyProfit;
                    prevResalePrice = instance.machines[j].resalePrice;
                    prevMachine = j;
                    break;
                }
            }
            if (prevMachine != 0) resaleDays[prevMachine] = resaleDay;

            // Modify profit
            int diffProfit = prevDailyProfit + machine.purchasePrice - prevResalePrice;            
            profit[machine.purchaseDay] += diffProfit;
            for (int i=machine.purchaseDay+1; i<resaleDay; i++) {
                diffProfit += prevDailyProfit - machine.dailyProfit;
                profit[i] += diffProfit;
            }
            if (resaleDay< nbDays) diffProfit +=  prevResalePrice - machine.resalePrice;
            for (int i=resaleDay; i<=nbDays; i++) profit[i] += diffProfit;

            // the end: updating everything and check acceptability
            chosenMachines[position] = 0;
            currentNbMachines -= 1;
            checkIsAcceptable();
            totalProfit = profit.back();
        }
    }
};

#endif