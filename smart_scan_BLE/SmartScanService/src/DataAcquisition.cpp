#include <iomanip>
#include <ctime>
#include <cstdio>

#include "../inc/DataAcquisition.h"
#include "../inc/Exceptions.h"

using namespace SmartScan;

DataAcqConfig::DataAcqConfig() 
{

}

DataAcqConfig::DataAcqConfig(short int transmitterID, double measurementRate, double powerLineFrequency, double maximumRange, double frameRotations[3])
	: transmitterID { transmitterID }, measurementRate { measurementRate }, powerLineFrequency { powerLineFrequency }, maximumRange { maximumRange }
{
	for (int i = 0; i < 3; i ++) {
		this->frameRotations[i] = frameRotations[i]; // Copy the array.
	}
}

DataAcq::DataAcq() :  mTSCtrl()
{
}

DataAcq::~DataAcq()
{
    // Delete all raw data when this object is removed.
	this->Stop(true);
}

void DataAcq::Init()
{
	mTSCtrl.Init();
	mTSCtrl.SelectTransmitter(mConfig.transmitterID);
	mTSCtrl.SetPowerlineFrequency(mConfig.powerLineFrequency);
	mTSCtrl.SetMeasurementRate(mConfig.measurementRate);
	mTSCtrl.SetMaxRange(mConfig.maximumRange);
	mTSCtrl.SetMetric();
	mTSCtrl.SetReferenceFrame(mConfig.transmitterID, mConfig.frameRotations);
	mTSCtrl.SetSensorFormat();

	//pressureGloves.SetDelayInMillis(mConfig.measurementRate);

	// Get sensor info from TrakStar object.
	mPortNumBuff = mTSCtrl.GetAttachedPorts();
	mSerialBuff = mTSCtrl.GetAttachedSerials();

    // Initialize raw data buffer.
	for (int i = 0; i < mPortNumBuff.size(); i++) {
		mRawBuff.push_back(std::vector<Point3>());
	}
}

void DataAcq::Init(DataAcqConfig acquisitionConfig)
{
	// Copy config and run init.
	this->mConfig = acquisitionConfig;
	this->Init();
}

void DataAcq::SensorConfig(digitSensor ref, digitSensor tmb, digitSensor ind, digitSensor mid) {
	// Save sensor serials
	mConfig.reference = ref;
	mConfig.thumb = tmb;
	mConfig.index = ind;
	mConfig.middle = mid;

	// Remove reference sensor from sensor vector, and save connected ports
	if (mConfig.reference.serial >= 0) {
		bool foundSensor = false;
		for(int i = 0; i < mSerialBuff.size(); i++) {

			if (mSerialBuff[i] == mConfig.reference.serial) {
				mConfig.reference.port = mPortNumBuff[i];
				mSerialBuff.erase(mSerialBuff.cbegin()+i);
				mPortNumBuff.erase(mPortNumBuff.cbegin()+i);
				mRawBuff.pop_back();
				foundSensor = true;
				i--; // Vector will shrink once reference serial is remove, yet some serial might still be present
			}
			else if (mSerialBuff[i] == mConfig.thumb.serial) {
				mConfig.thumb.port = mPortNumBuff[i];
			}
			else if (mSerialBuff[i] == mConfig.index.serial) {
				mConfig.index.port = mPortNumBuff[i];
			}
			else if (mSerialBuff[i] == mConfig.middle.serial) {
				mConfig.middle.port = mPortNumBuff[i];
			}
		}

		// Throw an error if the user specified a reference sensor serial number that is not attached.
		if (!foundSensor) {
			throw ex_acq("Could not find the reference sensor specified.", __func__, __FILE__);
		}
		// Set the reference sensor to use rotation matrices instead of Euler angles.
		mTSCtrl.SetRefSensorFormat(mConfig.reference.port);
	}

}

void DataAcq::CorrectZOffset(int serialNumber)
{
	// Get a raw Z coordinate sample and take the height of the transmitter casing into account.
    Point3 rawSample = this->GetSingleSample(serialNumber, true);
    Point3 zOnly = Point3(0.0, 0.0, Z_CASE_OFFSET - rawSample.z, rawSample.r);

	// Rotate that Z offset with the roll rotation of the sensor.
    this->AngleCorrect(&zOnly);

	// Set the offset.
	mTSCtrl.SetSensorOffset(FindPortNum(serialNumber), zOnly);
}

void DataAcq::Start()
{
	// Check whether trak star controller has been initialised.
//	if (!mRawBuff.size()) {
//		throw ex_acq("Data acquisition is not initialized.", __func__, __FILE__);
//	}

	// Check if the DataAcquisition thread is already running.
	if (this->mRunning)	{
		return;
	}

    // Create a new DataAcquisition thread.
	try	{
		this->pAcquisitionThread = std::make_unique<std::thread>(&DataAcq::DataAcquisition, this);
	}
	catch (...)	{
		throw ex_acq("Unnable to start data-acquisition thread.", __func__, __FILE__);
	}

	// Let it gooooo, let it gooo.
	this->pAcquisitionThread->detach();

	mRunning = true;
}

void DataAcq::Stop(bool clearData)
{
	// Wait a bit for the other threads to finish.
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
	// Clear button state and raw buffer.
    if (clearData) {
		for (int i = 0; i < mRawBuff.size(); i++) {
			button_obj.ClearMyButton();
			mRawBuff.at(i).clear();
		}
	}

	mRunning = false;
}

const bool DataAcq::IsRunning() const
{
	return mRunning;
}

const std::vector<std::vector<Point3>>* DataAcq::GetRawBuffer()
{
	return &mRawBuff;
}

Point3 DataAcq::GetSingleSample(int sensorSerial, bool raw)
{
	// Check whether trak star controller has been initialised.
	if (!mRawBuff.size()) {
		throw ex_acq("Data acquisition is not initialized.", __func__, __FILE__);
	}

	// Create empty reference point for later use.
	Point3Ref refMatrix;

	// Make Point3 obj to get the position info of the trackStar device.
	Point3 rawPoint = mTSCtrl.GetRecord(FindPortNum(sensorSerial)); 

	// Check if raw data is requested.
	if (raw) {
		//this->angleCorrect(&rawPoint);
	}
	// Check if a reference sensor is defined.
	else if (mConfig.reference.port > -1) {
		refMatrix = mTSCtrl.GetRefRecord(mConfig.reference.port);
		ReferenceCorrect(&refMatrix, &rawPoint);
	}

	return rawPoint;
}

const int DataAcq::NumAttachedBoards() const
{
	return mTSCtrl.NumAttachedBoards();
} 

const int DataAcq::NumAttachedTransmitters() const
{
	return mTSCtrl.NumAttachedTransmitters();
} 

const int DataAcq::NumAttachedSensors(bool includeRef) const
{
	// Add + 1 since the reference sensor is removed from the sensor list.
	if (includeRef && mConfig.reference.port > -1) {
		return (const int)mPortNumBuff.size() + 1;
	}
	return (const int)mPortNumBuff.size();
} 

const std::vector<int> DataAcq::GetSerialNumbers(void) {
	return mSerialBuff;
}

bool DataAcq::BLEConnect(std::string macAddress) {
	// Try and connect to the gloves
	if (pressureGloves.ConnectToGlove(macAddress) == EXIT_SUCCESS) {
		// Return true if it succeeds
		return true;
	}
	// Return false if it fails
	return false;
}

bool DataAcq::BLEConnected(void)
{
	return pressureGloves.IsConnected();
}

std::string DataAcq::BLEAddress(void) {
	return pressureGloves.GetMacAddress();
}

std::vector<int> DataAcq::ReadPressure(void) {
	std::vector<int> vectorizedData;
	std::string rawData = pressureGloves.GetData();

	// Find major seperators
	size_t startMeas = rawData.find(READ_START);
	size_t timeEnd = rawData.find(READ_TIME) - 1;
	size_t stopMeas = rawData.find(READ_STOP);

	// Save the time
	vectorizedData.push_back(atoi(rawData.substr((startMeas + 1), (timeEnd - startMeas)).c_str()));

	// Initialize vectorization
	size_t start = timeEnd + 2;
	size_t stop = rawData.find(READ_SEPERATOR, start);
	bool allIsMeasured = false;
	size_t crntIndex = 1;

	// Keep going until no more seperators can be found
	do {
		// Save integer at found location
		vectorizedData.push_back(atoi(rawData.substr(start, (stop + 1 - start)).c_str()));
		
		// Update the start index
		start = stop + 2;

		// Find new stop index
		stop = rawData.find(READ_SEPERATOR, stop + 2) - 1;

		// Go to next vector element
		crntIndex++;
	} while (rawData.find(READ_SEPERATOR, stop - 1) != std::string::npos);

	vectorizedData.push_back(atoi(rawData.substr(start, (stopMeas - start)).c_str()));
	return vectorizedData;
}

int DataAcq::ReadPressureSingle(int index) {
	return ReadPressure().at(index);
}

void DataAcq::RegisterRawDataCallback(std::function<void(const std::vector<Point3>&)> callback)
{
	mRawDataCallback = callback;
}

int DataAcq::FindPortNum(int serialNumber)
{
	// Initialize to an irrealistic number.
	int portNum = -1;

    for (int i = 0; i < mSerialBuff.size(); i++) {
        if(mSerialBuff[i] == serialNumber) {
			portNum = mPortNumBuff[i];
            break;	// Break if serial number has been found.  
        }
    }

	// Throw an error if the serial number cannot be found.
	if (portNum == -1) {
		throw ex_acq("Could not find requested sensor serial number.", __func__, __FILE__);
	}

    return portNum;
}

int DataAcq::FindBuffNum(int serialNumber)
{
	// Initialize to an irrealistic number.
	int bufNum = -1;

    for (int i = 0; i < mSerialBuff.size(); i++) {
        if(mSerialBuff[i] == serialNumber) {
			bufNum = i;
            break; // Break if serial number has been found.
        }
    }

	// Throw an error if the serial number cannot be found.
	if (bufNum == -1) {
		throw ex_acq("Could not find requested sensor serial number.", __func__, __FILE__);
	}

    return bufNum;
}

void DataAcq::DataAcquisition()
{
    // Store the current time.
	double time = 0;
	auto startSampling = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> endSampleTime = startSampling;

	// Create empty reference point for later use.
	Point3Ref refMatrix;

	while (mRunning) {
		// Store time and calculate the elapsed time since last sample.
		auto startSampleTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = startSampleTime - endSampleTime;

		if (elapsedTime.count() >= 1 / mConfig.measurementRate) {
            time += elapsedTime.count();

			// Check if a reference sensor is defined.
			if (mConfig.reference.port > -1) {
				refMatrix = mTSCtrl.GetRefRecord(mConfig.reference.port);
			}

            for (int i = 0; i < mPortNumBuff.size(); i++) {
                // Make Point3 obj to get the position info of the trackStar device
				Point3 raw = mTSCtrl.GetRecord(mPortNumBuff[i]); 

				// Check and store the buttonstate
				button_obj.UpdateButtonState(raw.button); 
				raw.buttonState = button_obj.GetButtonState();

				// Add total measurement time to point3.
				raw.time = time;

				// Append sensor data and pressure
				raw.locPort = mPortNumBuff[i];
				if (mConfig.thumb.port == mPortNumBuff[i]) {
					raw.locSerial = mConfig.thumb.serial;
					raw.pressure = ReadPressureSingle(mConfig.thumb.index) - mConfig.thumb.pressureOffset;
				}
				else if (mConfig.index.port == mPortNumBuff[i]) {
					raw.locSerial = mConfig.index.serial;
					raw.pressure = ReadPressureSingle(mConfig.index.index) - mConfig.index.pressureOffset;
				}
				else if (mConfig.middle.port == mPortNumBuff[i]) {
					raw.locSerial = mConfig.middle.serial;
					raw.pressure = ReadPressureSingle(mConfig.middle.index) - mConfig.middle.pressureOffset;
				}

				// Correct point for reference sensor
				if (mConfig.reference.port > -1) {
					ReferenceCorrect(&refMatrix, &raw);
				}

				mRawBuff[i].push_back(raw);
		    }			

			// Print the acquired data
			if (mRawDataCallback) {
				std::vector<Point3> sampleRow;
				for (int i = 0; i < mRawBuff.size(); i++) {
					sampleRow.push_back(mRawBuff.at(i).back());
				}
				mRawDataCallback(sampleRow);
			}

			// Store current time and calculate duration of the samples
			endSampleTime = std::chrono::steady_clock::now();
		}
    }
}

void DataAcq::ReferenceCorrect(Point3Ref* refPoint, Point3* sensorPoint)
{
	// Check the orientation of the current point.
	sensorPoint->x = sensorPoint->x - refPoint->x;
	sensorPoint->y = sensorPoint->y - refPoint->y;
	sensorPoint->z = sensorPoint->z - refPoint->z;

	// Multiply current point with reference sensor rotation matrix.
	double x_new = sensorPoint->x*refPoint->m[0][0]+sensorPoint->y*refPoint->m[1][0]+sensorPoint->z*refPoint->m[2][0];
	double y_new = sensorPoint->x*refPoint->m[0][1]+sensorPoint->y*refPoint->m[1][1]+sensorPoint->z*refPoint->m[2][1];
	double z_new = sensorPoint->x*refPoint->m[0][2]+sensorPoint->y*refPoint->m[1][2]+sensorPoint->z*refPoint->m[2][2];

	// Store result.
	sensorPoint->x = x_new;
	sensorPoint->y = y_new;
	sensorPoint->z = z_new;
}

void DataAcq::AngleCorrect(Point3* sensorPoint)
{
	// Use the azimuth to calculate the rotation around the z-axis.
	//double x_new = sensorPoint->x * cos(sensorPoint->r.z * CONV_TO_RAD) + sensorPoint->y * sin(sensorPoint->r.z * CONV_TO_RAD);
	//double y_new = sensorPoint->y * cos(sensorPoint->r.z * CONV_TO_RAD) - sensorPoint->x * sin(sensorPoint->r.z * CONV_TO_RAD);

	// Use the elevation to calculate the rotation around the y-axis.
	//sensorPoint->x = x_new * cos(sensorPoint->r.y * CONV_TO_RAD) - sensorPoint->z * sin(sensorPoint->r.y * CONV_TO_RAD);
	//double z_new = sensorPoint->z * cos(sensorPoint->r.y * CONV_TO_RAD) + x_new * sin(sensorPoint->r.y * CONV_TO_RAD);

	// Use the roll difference to calculate the rotation around the x-axis.
	double y_new = sensorPoint->y * cos(sensorPoint->r.x * CONV_TO_RAD) + sensorPoint->z * sin(sensorPoint->r.x * CONV_TO_RAD);
	double z_new = sensorPoint->z * cos(sensorPoint->r.x * CONV_TO_RAD) - sensorPoint->y * sin(sensorPoint->r.x * CONV_TO_RAD);

    sensorPoint->y = y_new;
    sensorPoint->z = z_new;
}