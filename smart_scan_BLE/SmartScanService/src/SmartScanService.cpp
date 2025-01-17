#include <chrono>
#include <iomanip>

#include "../inc/Exceptions.h"
#include "../inc/SmartScanService.h"
#include "../inc/DataAcquisition.h"

using namespace SmartScan;

SmartScanService::SmartScanService():  mDataAcq() // Initializer list needed to initialize member classes and values.
{

}

SmartScanService::~SmartScanService()
{
	// Clear all data.
	this->ClearData();
	scans.clear();
}

void SmartScanService::Init()
{
	mDataAcq.Init();
}

void SmartScanService::Init(DataAcqConfig acquisitionConfig) {
	mDataAcq.Init(acquisitionConfig);
}

void SmartScanService::SensorSetup(digitSensor ref, digitSensor tmb, digitSensor ind, digitSensor mid) {
	mDataAcq.SensorConfig(ref, tmb, ind, mid);
}

void SmartScanService::CorrectZOffset(int serialNumber)
{
	mDataAcq.CorrectZOffset(serialNumber);
}

void SmartScanService::SetStopSample(int newStopSample, int id) {
	ScanConfig config;
	config.stopAtSample = newStopSample;
	bool ok = false;
	// Find the scan with the specified id and replace it with new sample.
	for (int s = 0; s < scans.size(); s++) {
		if (scans[s]->mId == id) {
			this->scans.at(s)->SetStopAtSample(newStopSample);
			ok = true;
			break;
		}
	}
	if (!ok) {
		throw ex_smartScan("Scan id not found", __func__, __FILE__);
	}
}

int SmartScanService::HighestSensor(void) {
	int highestIndex = 0;
	std::vector<int> connectedSerials = mDataAcq.GetSerialNumbers();
	std::vector<Point3> measuredPoints;

	// Measure the raw location of each connectod sensor
	for (int i = 0; i < connectedSerials.size(); i++) {
		// Save the position to local vector
		measuredPoints.push_back(mDataAcq.GetSingleSample(connectedSerials.at(i), true));

		//Set the current sensor as the highest if the current index is 0 or it's Z pos is higher than the previous sensor
		if (i == 0 || abs(measuredPoints.at(highestIndex).z) < abs(measuredPoints.at(i).z)) {
			highestIndex = i;
		}
	}
	return connectedSerials.at(highestIndex);
}

std::vector<int> SmartScanService::GetPressureSnapshot() {
	return mDataAcq.ReadPressure();
}

void SmartScanService::NewScan(ScanConfig config) {
	// Check if the filtering precision has no remainder with 180. This is needed to make sure an array can be created with integer indexes in the Scan class.
	if (180%config.filteringPrecision != 0) {
		throw ex_smartScan("180 is not a multiple of the filtering precision", __func__, __FILE__);
	}
	// Give raw data buffer to the scan.
	config.inBuff = mDataAcq.GetRawBuffer();
	this->scans.emplace_back(std::make_shared<Scan>(FindNewScanId(), config));
}

void SmartScanService::DeleteScan()
{
	this->scans.clear();
}

void SmartScanService::DeleteScan(int id) {
	bool ok = false;
	// Find the scan with the specified id and erase it.
	for (int s = 0; s < scans.size(); s++) {
		if (scans[s]->mId == id) {
			this->scans.erase(scans.begin() + s);
			ok = true;
			break;
		}
	}
	if (!ok) {
		throw ex_smartScan("Scan id not found", __func__, __FILE__);
	}
}

void SmartScanService::StartScan() {
	// Start the scan:
	mDataAcq.Start();

	for (int i = 0; i < scans.size(); i++) {
		// Check if reference points have been set;
		if (!this->scans.at(i)->NumRefPoints() && !this->scans.at(i)->NumUsedSensors()) {
			char arg[51];
			// Ugly stuff to put a number into an error string. This can probalby be done easier.
			sprintf_s(arg ,"Cannot start scan %i due to reference points set.", i);
			throw ex_smartScan(arg, __func__, __FILE__);
		}

		scans.at(i)->Run();
	}
}

void SmartScanService::StartScan(int id) {
	bool ok = false;
	char arg[51];
	const char startString[] = "Cannot start scan ";
	const char endString[] = " due to reference points set.";
	char scan[3];
	
	for (int i = 0; i < scans.size(); i++) {
		//Check if current scan is the scan which is requested
		if (this->scans.at(i)->mId == id) {
			// Start data acquisition if not running yet
			if (!mDataAcq.IsRunning()) {
				mDataAcq.Start();
			}

			// Check if reference points have been set;
			if (!this->scans.at(i)->NumRefPoints() && !this->scans.at(i)->NumUsedSensors()) {
				// Ugly stuff to put a number into an error string. This can probalby be done easier.
				sprintf_s(scan, "%d", i);
				strcpy_s(arg, startString);
				strcat_s(arg, scan);
				strcat_s(arg, endString);
				throw ex_smartScan(arg, __func__, __FILE__);
			}
			else {
				ok = true;
				this->scans.at(i)->Run();
			}
		}
	}

	if (!ok) {
		throw ex_smartScan("Scan id not found", __func__, __FILE__);
	}
}

void SmartScanService::ClearData() {
	mDataAcq.Stop(true);
	
	for (int i = 0; i < scans.size(); i++) {
		scans.at(i)->Stop(true);
	}
}

Point3 SmartScanService::GetSingleSample(int sensorSerial, bool raw) {
	return mDataAcq.GetSingleSample(sensorSerial, raw);
}

bool SmartScanService::IsSerialConnected(int serialNumber) {
	// Get all connected serial IDs
	std::vector<int> serials = mDataAcq.GetSerialNumbers();

	// Check if requested ID is present
	for (int i = 0; i < serials.size(); i++) {
		if (serials.at(i) == serialNumber) {
			return true;
		}
	}
	
	// If no serials matched, return a false
	return false;
}

bool SmartScanService::ConnectToGlove(std::string macAddress)
{
	return mDataAcq.BLEConnect(macAddress);
}

bool SmartScanService::IsPressureConnected(void)
{
	return mDataAcq.BLEConnected();
}

std::string SmartScanService::ConnectedMacAddr(void) {
	return mDataAcq.BLEAddress();
}

void SmartScanService::StopScan() {
	mDataAcq.Stop();

	for (int i = 0; i < scans.size(); i++) {
		scans.at(i)->Stop();
		/*CURRENTLY BEING TESTED, NOT READY FOR USE*/
		//scans.at(i)->OutlierFiltering();
	}
}

bool SmartScanService::StopScan(int id) {
	//Check if there is another scan still running
	int i = 0;
	bool scanRunning = false;
	bool ok = false;

	// Find the scan with the specified id and erase it.
	for (int s = 0; s < scans.size(); s++) {
		do {
			if (this->scans.at(i)->IsRunning() && this->scans.at(i)->mId != id) {
				scanRunning = true;
			}
			i++;
		} while (i < this->scans.size() && !scanRunning);

		//Only stop the data acquisition if no other scans are using it

		if (this->scans.at(s)->mId == id) {
			if (!scanRunning) {
				mDataAcq.Stop();
			}

			this->scans.at(s)->Stop();
			ok = true;
			/*CURRENTLY BEING TESTED, NOT READY FOR USE*/
			//scans.at(i)->OutlierFiltering();
			break;
		}
	}
	return ok;
}

const std::vector<std::shared_ptr<Scan>>& SmartScanService::GetScansList() const {
	return scans;
}

const int SmartScanService::NumAttachedBoards() const {
	return mDataAcq.NumAttachedBoards();
}

const int SmartScanService::NumAttachedTransmitters() const {
	return mDataAcq.NumAttachedTransmitters();
}

const int SmartScanService::NumAttachedSensors(bool includeRef) const {
	return mDataAcq.NumAttachedSensors(includeRef);
}

int SmartScanService::NumOfScans(void) {
	return (int)this->scans.size();
}

void SmartScanService::ExportCSV(const std::string filename, int scanId, const bool raw) {
	try {
		if (raw) {
			csvExport.ExportPoint3Raw(mDataAcq.GetRawBuffer(), filename);
		}
		else {
			// Copy the scan buffer into a temporary vector and export that.
			// This is done because the scan data is stored in a 3D array so its not that nice to work with.
			std::vector<Point3> temp;
			scans.at(scanId)->CopyOutputBuffer(&temp);
			csvExport.ExportPoint3(&temp, filename);
		}
	}
	catch(ex_export e) {
		throw e;
	}
	catch (...) {
		throw ex_smartScan("Could not export data.", __func__, __FILE__);
	}
}

void SmartScanService::ExportPointCloud(const std::string filename, int scanId, const bool raw) {
	try {
		if (raw) {
			csvExport.ExportPoint3RawCloud(mDataAcq.GetRawBuffer(), filename);
		}
		else {
			// Copy the scan buffer into a temporary vector and export that.
			// This is done because the scan data is stored in a 3D array so its not that nice to work with.
			std::vector<Point3> temp;
			scans.at(scanId)->CopyOutputBuffer(&temp);
			csvExport.ExportPoint3Cloud(&temp, filename);
		}
	}
	catch(ex_export e) {
		throw e;
	}
	catch (...) {
		throw ex_smartScan("Could not export data.", __func__, __FILE__);
	}
}

void SmartScanService::RegisterRawDataCallback(std::function<void(const std::vector<SmartScan::Point3>&)> callback) {
	mDataAcq.RegisterRawDataCallback(callback);
}

const int SmartScanService::FindNewScanId() const {
	int newId = 0;
	bool taken = false;
	bool found = false;

	do {
		taken = false;

		for (int scn = 0; scn < scans.size(); scn++) {
			if (newId == scans[scn]->mId) {
				taken = true;
			}
		}

		if (!taken) { 
			return newId;
		}
		else {
			newId++;
		}
	} while (true);
}

const bool SmartScanService::IdExists(const int scanId) const {
	for (int scn = 0; scn < scans.size(); scn++) {
		if (scanId == scans[scn]->mId) {
			return true;
		}
	}
	return false;
}