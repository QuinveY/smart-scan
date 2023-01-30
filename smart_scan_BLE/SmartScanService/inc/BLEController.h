#pragma once

#include <vector>
#include <stdlib.h>

#include "ini.h"
#include "DirDef.h"
#include "Point3.h"

#include <simpleble/Utils.h>
#include <simpleble/SimpleBLE.h>

struct PressurePoint {
	int meas = 0;
	long int timeInMillis = 0;
};

class PressureSensors {
public:
	PressureSensors();
	~PressureSensors();
	int Connect();
	int Connect(std::string macAddress);
	std::vector<int> GetData();
	int GetLatestPoint(int index);

private:
	int startTime = 0;
	std::vector<std::string> notifyStringBuf;
	std::vector<std::vector<PressurePoint>> measurements;
};