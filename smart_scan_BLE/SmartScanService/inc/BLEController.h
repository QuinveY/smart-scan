#pragma once

// BLE library
#include <simpleble/Utils.h>
#include <simpleble/SimpleBLE.h> 

// Standard Includes
#include <vector>
#include <stdlib.h>

// Definitions
#define UUID_PRESSURE	"00000002-0f8e-467a-a542-98fb7a3c85d6" // Pressure result characteristic
#define UUID_SAMPLING	"00000003-0f8e-467a-a542-98fb7a3c85d6" // Sampling speed characteristic (in ms, if 0 only on change)
#define UUID_ADV		"00001530-1212-EFDE-1523-785FEABCD123" // UUID which is advertised, used for connecting
#define GLOVE_NAME		"Sendance-Gloves_Right"				   // Name
#define READ_START		'['
#define READ_TIME		';'
#define READ_SEPERATOR	','
#define READ_STOP		']'

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
	int ConnectToGlove(std::string MacAddress);

	// Return MAC address of connected glove
	std::string GetMacAddress(void);

	// Return true if a glove has been connected
	bool IsConnected(void);

	// Return the latest point of data in an unaltered string
	std::string GetData(void);

	// Set the measurement speed of the pressure gloves
	void SetDelayInMillis(int delayInMillis);

private:
	int startTime = 0;
	SimpleBLE::Adapter adapter;
	std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> measUUID;
	std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> sampleSpeedUUID;
	SimpleBLE::Peripheral peripheral;
};