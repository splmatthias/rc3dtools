/*
 * Metrics.h
 *
 *  Created on: Jan 22, 2015
 *      Author: calli82
 */

#ifndef METRICS_H_
#define METRICS_H_

#include "MetricsConfiguration.h"
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <map>

using namespace std;

namespace MetricsCollector
{
	class Metrics
	{
	public:
		Metrics();
		virtual ~Metrics();

		void increaseTimeStep();

		void collectWeightedBallTimePositionMetrics(double, double);
		void collectGoalMetrics(int team);
		void collectTimeMetrics(string event);

		void collectCustomizedMetrics(double val);
		void collectPositionMetrics();

		double calcDistanceToGoalForMetrics(bool own, double x, double y);
		void calcGoalDifference();

		double getBallTimePosValue();
		double getGoalOwn();
		double getGoalOpp();
		double getGoalDifference();

		void initializeFile();
		void writeResults();

	private:
		double metricsBallAt_t;
		double cumMetricsBallAt_t;

		int numberOfMetrics;
		long timestep;

		// metrics for goal collection
		int goalsOwn;
		int goalsOpp;
		int goalDifference;

		enum goalOn{Own=0,
					Opp=1,
					Unknown=2};

		map<string,vector<long> > eventsTime;

		MetricsConfiguration* config;

	};
}

#endif /* METRICS_H_ */
