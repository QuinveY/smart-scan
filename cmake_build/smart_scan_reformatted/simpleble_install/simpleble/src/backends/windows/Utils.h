#pragma once

#include <cstdint>
#include <exception>
#include <string>

#include <optional>
#include "simpleble/SimpleBLE.h"
#include <simpleble/Adapter.h>

#include <simpleble/Exceptions.h>
#include <simpleble/Types.h>

#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Storage.Streams.h"
#include "winrt/base.h"

using namespace winrt::Windows;
using namespace winrt::Windows::Storage::Streams;

constexpr uint32_t TEN_SECONDS_IN_MSECS = 10000;

namespace SimpleBLE {
void initialize_winrt();

std::string _mac_address_to_str(uint64_t mac_address);
uint64_t _str_to_mac_address(std::string mac_address);

winrt::guid uuid_to_guid(const std::string& uuid);
std::string guid_to_uuid(const winrt::guid& guid);

ByteArray ibuffer_to_bytearray(const IBuffer& buffer);
IBuffer bytearray_to_ibuffer(const ByteArray& array);

template <typename async_t>
static auto async_get(async_t const& async) {
    if (async.Status() == Foundation::AsyncStatus::Started) {
        wait_for_completed(async, TEN_SECONDS_IN_MSECS);
    }
    try {
        return async.GetResults();
    } catch (const winrt::hresult_error& err) {
        throw SimpleBLE::Exception::WinRTException(err.code().value, winrt::to_string(err.message()));
    } catch (const std::exception& err) {
        throw SimpleBLE::Exception::BaseException(err.what());
    }
}

}  // namespace SimpleBLE
namespace Utils {

std::optional<SimpleBLE::Adapter> getAdapter();

/**
 * @brief Function to get a user input as size_t, it's used in all examples to select an index
 *
 * @param line the text asking for something to the user
 * @param max the maximum value that can be written
 *
 * @return the value or empty optional
 */
std::optional<std::size_t> getUserInputInt(const std::string& line, std::size_t max);

/**
 * @brief Pretty print a ByteArray
 */
void print_byte_array(const SimpleBLE::ByteArray& bytes);
}  // namespace Utils