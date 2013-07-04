#ifndef CGALANDER_H
#define CGALANDER_H

/*! \file CgaLander.h
*	\author Mat Buckland
*	\brief This is the genetic algorithm class to evolve the genomes used in the Lunar Lander project.
*/

#include <vector>
#include <sstream>
#include <algorithm>

#include "defines.h"
#include "CLander.h"
#include "utils.h"

using namespace std;

/// Define our genome structure
struct SGenome
{
	vector<SGene> vecActions;
	double dFitness;

	SGenome():dFitness(0) {}

	SGenome(const int num_actions):dFitness(0)
	{
		//create a random vector of actions
		for(int i = 0; i < num_actions; ++i)
		{
			vecActions.push_back(SGene());
		}
	}

	//overload '<' used for sorting
	friend bool operator<(const SGenome &lhs, const SGenome &rhs)
	{
		return (lhs.dFitness < rhs.dFitness);
	}
};

///	Define our genetic algorithm class
class CgaLander
{
	private:
		//our population of genomes
		vector<SGenome> m_vecPop;
		//size of population
		int m_iPopSize;
		double m_dCrossoverRate;
		double m_dMutationRate;
		//how many actions per chromosome
		int m_iChromoLength;
		int m_iFittestGenome;
		double m_dBestFitness, m_dAverageFitness, m_dWorstFitness, m_dTotalFitness;
		int m_iGeneration;

		void Mutate(vector<SGene> &vecBits);
		void CrossoverMulti(const vector<SGene> &mum, const vector<SGene> &dad,
							vector<SGene> &baby1, vector<SGene> &baby2);
		SGenome& RouletteWheelSelection();
		void GrabNBest(int NBest, const int NumCopies, vector<SGenome> &vecPop);
		void CreateStartPopulation();
		vector<SGenome> Epoch();
		void Reset();
		void CalculateBestWorstAvTot();

	public:
		CgaLander(double cross_rat, double mut_rat, int pop_size,
					int num_actions, int cxClient, int cyClient):m_dCrossoverRate(cross_rat),
																 m_dMutationRate(mut_rat),
																 m_iPopSize(pop_size),
																 m_iChromoLength(num_actions),
																 m_dTotalFitness(0),
																 m_iGeneration(0),
																 m_dAverageFitness(0),
																 m_dWorstFitness(0),
																 m_dBestFitness(0)
		{
			///create the population of genomes
			CreateStartPopulation();
		}

		///takes a population of genomes and performs one epoch.
		///and creates a new population
		void UpdatePop(vector<SGene> &OldPop);

		///accesor method
		int Generation()const {return m_iGeneration;}
		///accesor method
		int FittestGenome()const {return m_iFittestGenome;}
		///accesor method
		double Best()const {return m_dBestFitness;}
		///accesor method
		double Average()const {return m_dAverageFitness;}
		///accesor method
		vector<SGenome> GrabPop()const {return m_vecPop;}
};

#endif