// primes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "cs477.h"
#include <vector>
#include <thread>

bool is_prime(int n)
{
	auto j = static_cast<int>(sqrt(n));
	for (int i = 2; i <= j; i++)
	{
		if (n % i == 0) return false;
	}
	return true;
}


int main()
{
	int numThrds = 5;
	std::vector<cs477::thread> thrds;
	std::vector<std::vector<int>> primeVect;
	
	for (int i = 0; i < numThrds ; i++)
	{
		thrds.push_back(cs477::create_thread([i, &primeVect]()
		{
			std::vector<int> primeNums;
			for (int j = i; j < 1000000; j+=5) {
				if (is_prime(j)) {
					primeNums.push_back(j);
				}
			}
			primeVect.push_back(primeNums);
		}));
	}

	for (auto && t : thrds) {
		//join the threads
		cs477::join(t);
	}
	
	// Prints all of the primes
	for (auto && prnt : primeVect) {
		for (auto && nums : prnt) {
			printf("\n", nums);
		}
	}
	
	
	//for (int i = 2; i < 100000000; i++)
	//{
	//	if (is_prime(i))
	//	{
	//		std::cout << i << std::endl;
	//	}
	//}
    return 0;
}
