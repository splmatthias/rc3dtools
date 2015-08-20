/*
 * MetricsConfiguration.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: calli82
 */

#include "MetricsConfiguration.h"

namespace MetricsCollector
{
	MetricsConfiguration::MetricsConfiguration()
	{
		collectGoalMetrics = false;
		collectTimeMetrics = false;
		collectBallPositionTimeMetrics = false;
		collectPositionMetrics = false;

		// your customized metrics
		collectCustomizedMetrics = false;

		weightGoalInPTMetrics = 0.5;
		weightTimeInPTMetrics = 0.5;

		alphaInGoalTimeMetrics = 0.5;
		betaInGoalTimeMetrics= 0.5;

		goalWidth = 0;
		fieldLength = 0;

		readConfigurationFile();
	}

	MetricsConfiguration::~MetricsConfiguration()
	{

	}

	void MetricsConfiguration::readConfigurationFile()
	{
		Config cfg("metricsConfiguration");

		// add validity check and messages
		collectGoalMetrics = cfg.getValue("collectGoalMetrics", false);
		collectTimeMetrics = cfg.getValue("collectTimeMetrics", false);
		collectBallPositionTimeMetrics = cfg.getValue("collectBallPositionTimeMetrics", false);
		collectPositionMetrics = cfg.getValue("collectPositionMetrics", false);
		collectCustomizedMetrics = cfg.getValue("collectCustomizedMetrics", false);

		weightGoalInPTMetrics = cfg.getValue("weightGoalInPTMetrics", 0.5);
		weightTimeInPTMetrics = cfg.getValue("weightTimeInPTMetrics", 0.5);

		// further parameters
		alphaInGoalTimeMetrics = cfg.getValue("alphaInGoalTimeMetrics", 0.5);
		betaInGoalTimeMetrics= cfg.getValue("betaInGoalTimeMetrics", 0.5);

		goalWidth = cfg.getValue("alphaInGoalTimeMetrics", 1.5);
		fieldLength = cfg.getValue("alphaInGoalTimeMetrics", 9.0);
	}
}
