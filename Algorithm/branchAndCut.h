#include <algorithm>
#include <math.h>
#include "../DataStructures/instance.h"
#include "../DataStructures/solution.h"

int recursiveSolve(Solution sol, int i, int bestKnownProfit, const Instance &instance) {
    int bestProfit = bestKnownProfit;
    Solution sol2 = sol;
    sol2.addMachine(i, instance);
    if (i<instance.nbMachines-1){
        if (sol2.isAcceptable == 0) { //non acceptable: in that case we cut the branch
            bestProfit = std::max(bestKnownProfit, sol.totalProfit);
            bestProfit = std::max(bestProfit, recursiveSolve(sol, i+1,bestKnownProfit, instance));
        }
        else {
            bestProfit = std::max({bestKnownProfit, sol.totalProfit, sol2.totalProfit});
            bestProfit = std::max({bestProfit, recursiveSolve(sol, i+1,bestKnownProfit, instance), recursiveSolve(sol2, i+1,bestKnownProfit, instance)});
        }
    }
    else {
        if (sol2.isAcceptable == 0) bestProfit = std::max(bestKnownProfit, sol.totalProfit);
        else bestProfit = std::max({bestKnownProfit, sol.totalProfit, sol2.totalProfit});
    }
    return bestProfit;
}

int branchAndBound(const Instance &instance) {
    Solution solution(instance);
    int bestProfit = recursiveSolve(solution, 0, 0, instance);
    return bestProfit;
}