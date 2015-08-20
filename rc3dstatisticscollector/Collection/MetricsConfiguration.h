/*
 * MetricsConfiguration.h
 *
 *  Created on: Jan 25, 2015
 *      Author: calli82
 */

#ifndef METRICSCONFIGURATION_H_
#define METRICSCONFIGURATION_H_

#include "../Config/Config.h"

namespace MetricsCollector
{
	class MetricsConfiguration
	{
	public:
		MetricsConfiguration();
		virtual ~MetricsConfiguration();

		void readConfigurationFile();

		// read values from configuration file
		bool collectBallPositionTimeMetrics;
		bool collectGoalMetrics;
		bool collectTimeMetrics;
		bool collectPositionMetrics;
		bool collectCustomizedMetrics;

		double weightGoalInPTMetrics;
		double weightTimeInPTMetrics;

		// your customized weights

		// further parametrization of goal and time metrics
		double alphaInGoalTimeMetrics;
		double betaInGoalTimeMetrics;

		// specifications of the field
		double goalWidth;
		double fieldLength;
	};
}

#endif /* METRICSCONFIGURATION_H_ */
