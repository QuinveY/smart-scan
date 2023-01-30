#pragma once

// BLE library
#include <simpleble/Utils.h>
#include <simpleble/SimpleBLE.h> 

// Standard Includes
#include <vector>
#include <stdlib.h>

// Custom includes
#include "DirDef.h"
#include "Point3.h"

// Definitions
#define UUID_PRESSURE	"00000002-0f8e-467a-a542-98fb7a3c85d6" 
#define GLOVE_NAME		"Sendance-"

struct PressurePoint {
	int meas = 0;
	long int timeInMillis = 0;
};

class PressureSensors {
public:
	// Constructor
	PressureSensors(void);
	
	// Deconstructor
	~PressureSensors(void);
	
	// Connecting and scan protocol
	int Connect(void);

	// Connect to a specific macAddress
	// Arguments:	macAddres - mac address of device to connect 
	int Connect(std::string macAddress);

	// Calibrate the sensors offset
	// Argument:	index - index to calibrate from string
	void OffsetCalibration(int index);

	// Return the latest point of data in an unaltered string
	std::string GetData(void);

	// Get the latest point of a specific index
	int GetLatestPoint(int index);

	// Get the latest point of a specific index
	// Arguments:	indeces - indeces to retreive data from
	vector<int> GetLatestPoint(const vector<int> indeces);

private:
	int startTime = 0;
	SimpleBLE::Adapter adapter;
	std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> measUUID;
	std::vector<std::string> measBuf;
	std::vector<std::vector<PressurePoint>> sortMeasBuf;
	SimpleBLE::Peripheral pressureGlove;
};