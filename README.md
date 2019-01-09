## Problem description 
You are the director of Clever and Very Complex Machines (or short: CVCM), a company producing advanced machinery using even more advanced machinery. 

The old production machinery has broken down, so you need to buy new production machines for the company. Your goal is to make as much money as possible during the restructuring period. 

During this period you will be able to buy and sell machines and operate them for profit while CVCM owns them. Due to space restrictions, CVCM can own at most one machine at a time. 

During the restructuring period, there will be several machines for sale. Being an expert in the advanced machines market, you already know the price `P_i` and the availability day `D_i` for each machines `M_i` . 
Note that if you do not buy machine `M_i` on day `D_i` then somebody else will buy it and it will not be available later. 
Needless to say, you cannot buy a machine if CVCM has less money than the price of the machine. If you buy a machine `M_i` on day `D_i` then CVCM can operate it starting on day `D_i` + 1. 
Each day that the machine operates, it produces a profit of `G_i` dollars for the company.

You may decide to sell a machine to reclaim a part of its purchase price any day after you’ve bought it.
Each machine has a resale price `R_i` for which it may be resold to the market. You cannot operate a machine on the day that you sell it, but you may sell a machine and use the proceeds to buy a new machine on the same day. Once the restructuring period ends, CVCM will sell any machine that it still owns. 

Your task is to maximize the amount of money that CVCM makes during the restructuring.

## Input

The input consists of several test cases. Each test case starts with a line containing three positive
integers N , C , and D . 

- N is the number of machines for sale (N ≤ 100), 
- C is the number of dollars with which the company begins the restructuring (C ≤ 100), 
- and D is the number of days that the restructuring lasts ( D ≤ 100).

Each of the next N lines describes a single machine for sale. Each line contains four integers:

- `D_i` : the day on which the machine is for sale
- `P_i` : the dollar price for which it may be bought
- `R_i` : the dollar price for which it may be resold
- `G_i` : the daily profit generated by operating the machine

These numbers satisfy the following conditions:

- 1 ≤ `D_i` ≤ D
- 1 ≤ `R_i` < `P_i` ≤ 100
- 1 ≤ `G_i` ≤ 100

The last test case is followed by a line containing three zeros.

## Output

For each test case, display its case number followed by the largest number of dollars that CVCM can
have at the end of day D + 1 . Follow the format of the sample output.

Example Input | Example Output
-|-
6 10 20 | Case 1: 44

## TODO 

- [ ] Please write an algorithm to solve [this instance](https://github.com/rbaiam/optimization/blob/master/instance.txt) 
- [ ] Please do not use optimization solvers (e.g. Cplex) and implement your own algorithm
- [ ] Please send your code with a small description how to run it against the proposed instance.

It is preferable that you write this algorithm using JAVA. It is OK if you want to use another programming language e.g. C++.

There are different ways to solve the problem highlighted above and the solution you come up with will tell us a lot about your skill as a developer and your ability to solve optimization problems.
