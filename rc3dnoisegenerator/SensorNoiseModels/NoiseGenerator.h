/*
 * NoiseGenerator.h
 *
 *  Created on: Dec 1, 2014
 *      Author: calli82
 */

#ifndef NOISEGENERATOR_H_
#define NOISEGENERATOR_H_

#include "JointNoise.h"
#include "NoiseConfiguration.h"
#include "SensorNoise.h"
#include "VirtualVisionNoiseModel.h"
#include "CommunicationNoise.h"
#include <vector>
#include <string>

using namespace std;

namespace Sim3DNoiseLib
{
	class NoiseGenerator
	{
	public:
		NoiseGenerator();
		virtual ~NoiseGenerator();

		// ------------ SENSORS AND JOINTS ---------------
		// functions for noise application called from outside
		double applyGyroNoise(string axis, double val);
		double applyAccNoise(string dir, double val);
		double applyForceNoise(string dir, double val);
		double applyJointsNoise(int joint, double val);

		// ------------- VISION ---------------
		// false positives for ball and goalposts within the methods as they are only one
		vector<double> applyVisionBallNoise(vector<double> percept);
		vector<double> applyVisionGoalNoise(string post, vector<double> percept);
		vector<double> applyVisionRobotsNoise(vector<double> percept);
		vector<double> applyFieldLinesNoise(vector<double> percept);

		// this method generates a number of false positives and sends it back to the simulator.
		// the simulator decides which of them should be sent or not.
		// number of FP depend on conditions
		vector<double> spawnFalsePositiveFieldLine(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ);
		vector<double> spawnFalsePositiveRobot(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ);
		vector<double> spawnFalsePositiveGoal(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ);
		vector<double> spawnFalsePositiveBall(vector<double> limitsX, vector<double> limitsY, vector<double> limitsZ);

		// ------------- COMMUNICATION ---------------
		// neccessary noise
		SensorNoise* sensorNoise;
		JointNoise* jointNoise;
		CommunicationNoise* commNoise;
		VirtualVisionNoiseModel* virtualVisionNoise;
		NoiseConfiguration* noiseConfiguration;

		vector<double> defaultPercept;
	};
}

#endif /* NOISEGENERATOR_H_ */
