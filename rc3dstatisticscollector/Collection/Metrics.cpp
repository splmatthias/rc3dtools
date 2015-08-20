/*
 * Metrics.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: calli82
 */

#include "Metrics.h"

namespace MetricsCollector
{
	Metrics::Metrics()
	{
		numberOfMetrics = 0;
		timestep = 0;
		metricsBallAt_t = 0;
		cumMetricsBallAt_t = 0;
		goalDifference = 0;
		goalsOwn = 0;
		goalsOpp = 0;
		config = new MetricsConfiguration();
	}

	Metrics::~Metrics()
	{

	}

	double Metrics::calcDistanceToGoalForMetrics(bool own, double x, double y)
	{
		double result = 0;
		if (own)
		{
			result = sqrt((pow((config->fieldLength - x), 2)
					- config->alphaInGoalTimeMetrics * pow((abs(y)-config->goalWidth), 2)));
		}
		else
		{
			result = sqrt((pow((-config->fieldLength - x), 2)
								- config->alphaInGoalTimeMetrics * pow((abs(y)-config->goalWidth), 2)));
		}
		return result;
	}

	void Metrics::collectWeightedBallTimePositionMetrics(double x, double y)
	{
		if(config->collectBallPositionTimeMetrics)
		{
			metricsBallAt_t = config->betaInGoalTimeMetrics * calcDistanceToGoalForMetrics(true,x,y)
					- (1-config->alphaInGoalTimeMetrics) * calcDistanceToGoalForMetrics(false,x,y);
			cumMetricsBallAt_t += metricsBallAt_t;
		}
	}

	void Metrics::increaseTimeStep()
	{
		timestep++;
	}

	void Metrics::collectGoalMetrics(int team)
	{
		if(config->collectGoalMetrics)
		{
			if(team == Own)
				goalsOwn++;
			else if(team == Opp)
				goalsOpp++;
		}
	}

	void Metrics::calcGoalDifference()
	{
		if(config->collectGoalMetrics)
			goalDifference = goalsOwn - goalsOpp;
	}

	void Metrics::collectTimeMetrics(string event)
	{
		if(config->collectTimeMetrics)
		{
			eventsTime[event].push_back(this->timestep);
		}
	}

	void Metrics::collectPositionMetrics()
	{
		// method stub
	}

	void Metrics::collectCustomizedMetrics(double val)
	{
		// method stub
	}

	double Metrics::getBallTimePosValue()
	{
		return this->cumMetricsBallAt_t;
	}

	double Metrics::getGoalOwn()
	{
		return this->goalsOwn;
	}

	double Metrics::getGoalOpp()
	{
		return this->goalsOpp;
	}

	double Metrics::getGoalDifference()
	{
		return this->goalDifference;
	}

	void Metrics::initializeFile()
	{
		ofstream resultsMetricsFile;
		resultsMetricsFile.open("resultsMetrics.csv");
		resultsMetricsFile << "goalOwn;" << "goalOpp;" << "goalDifference;" << "ballPositionTimeMetrics;" << endl;
		resultsMetricsFile.close();
	}

	// will be called after all data has been collected
	void Metrics::writeResults()
	{
		ifstream resultsMetricsFile ("resultsMetrics.csv");
		if(!resultsMetricsFile)
			initializeFile();

		ofstream outResultsMetricsFile;
		outResultsMetricsFile.open("resultsMetrics.csv", std::fstream::app);
		outResultsMetricsFile << goalsOwn << ";" << goalsOpp << ";" << goalDifference << ";" << cumMetricsBallAt_t << ";";
		outResultsMetricsFile << endl;
		outResultsMetricsFile.close();
	 }
}
