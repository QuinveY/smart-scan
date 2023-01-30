#include "../inc/BLEController.h"

using namespace SimpleBLE;
using namespace std;

PressureSensors::PressureSensors() {
	
}

PressureSensors::~PressureSensors() {

}

int PressureSensors::Connect() {
	optional<Adapter> adapter_optional = Utils::getAdapter();

	if (!adapter_optional.has_value()) {
		return EXIT_FAILURE;
	}

	Adapter adapter = adapter_optional.value();

	vector<Peripheral> peripherals;

	adapter.set_callback_on_scan_found([&](Peripheral peripheral) {
		cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << endl;
		peripherals.push_back(peripheral);
	});

	adapter.set_callback_on_scan_start([]() { cout << "Scan started." << endl; });
	adapter.set_callback_on_scan_stop([]() { cout << "Scan stopped." << endl; });
	// Scan for 5 seconds and return.
	adapter.scan_for(5000);

	cout << "The following devices were found:" << endl;
	for (size_t i = 0; i < peripherals.size(); i++) {
		cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]" << endl;
	}

	auto selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);
	if (!selection.has_value()) {
		return EXIT_FAILURE;
	}

	auto peripheral = peripherals[selection.value()];
	cout << "Connecting to " << peripheral.identifier() << " [" << peripheral.address() << "]" << endl;
	peripheral.connect();

	cout << "Successfully connected, printing services and characteristics.." << endl;

	// Store all service and characteristic uuids in a vector.
	vector<pair<BluetoothUUID, BluetoothUUID>> uuids;
	for (auto service : peripheral.services()) {
		for (auto characteristic : service.characteristics()) {
			uuids.push_back(make_pair(service.uuid(), characteristic.uuid()));
		}
	}

	cout << "The following services and characteristics were found:" << endl;
	for (size_t i = 0; i < uuids.size(); i++) {
		cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << endl;
	}

	selection = Utils::getUserInputInt("Please select a characteristic to read", uuids.size() - 1);

	if (!selection.has_value()) {
		return EXIT_FAILURE;
	}

	// Subscribe to the characteristic.
	peripheral.notify(uuids[selection.value()].first, uuids[selection.value()].second, [&](ByteArray bytes) {
		cout << "Received: ";
		Utils::print_byte_array(bytes);
	});
}