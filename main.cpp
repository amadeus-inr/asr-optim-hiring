#include <algorithm>
#include <iostream>
#include "DataStructures/solution.h"
#include "DataStructures/instance.h"
#include "Algorithm/branchAndCut.h"


void fromTxt(std::vector<Instance>& instances, std::string fileNameBase, const bool verbose = true) {
    std::ifstream infile(fileNameBase);
    std::string line;
    int id = 1;
    int a, b, c;
    int e, f, g, h;
    while (infile >> a >> b >> c) {
        if (a==0 && b==0 && c==0) {break;}
        std::vector<Machine> machines;
        for (int j=0; j<a; j++) {
            infile >> e >> f >> g >> h;
            Machine machine(j, e-1, f, g, h);
            machines.push_back(machine);
        }
        std::sort(machines.begin(), machines.end()); // sorting machines by purchaseDay
        for (int i=0; i<machines.size(); i++) machines[i].id = i;
        Instance instance(id, a, b, c, machines);
        instances.push_back(instance);
        id ++;
    }
}


int main() {
    // Instance reading
    std::vector<Instance> instances;
    std::string filename = "../instance.txt";
    fromTxt(instances, filename);
    // Branch and Bound
    for (const auto& instance: instances) {
        int bp = branchAndBound(instance);
        std::cout << "Case " << instance.id << ": " << bp << std::endl;
    }
    
    /*
    // Example of code for Debuging
    Instance instance = instances[3];
    std::cout << instance;
    Solution solution(instance);
    std::cout << solution;
    solution.addMachine(0, instance);
    std::cout << solution;
    solution.addMachine(3, instance);
    std::cout << solution;
    solution.addMachine(4, instance);
    std::cout << solution;
    solution.destroyMachine(3, instance);
    std::cout << solution;
    */
    

}