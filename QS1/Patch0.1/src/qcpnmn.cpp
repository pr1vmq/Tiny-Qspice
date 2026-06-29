#include "../Headers/qcpnmn.h"
#include <string>
#include <ranges>
#include <format>
#include <numeric>
#include <stdexcept>
#include <charconv>
#include <array>

constexpr std::array<char, 16> HEX_DIGITS{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

namespace qcpnManager {
	/*
	  @brief Encodes a standard string into a hexadecimal string.
	 */
	std::string stringToHex(const std::string& input) {
		if (input.empty()) return {};

		std::string result;
		// C++23 zero-initialization bypass for maximum performance
		result.resize_and_overwrite(input.length() * 2, [&input](char* buf, size_t size) noexcept -> size_t {
			size_t p = 0;
			const auto* src = reinterpret_cast<const unsigned char*>(input.data());
			const auto* end = src + input.length();

			// High/low nibble extraction via bit shifting and masking
			while (src < end) {
				unsigned char byte = *src++;
				buf[p++] = HEX_DIGITS[byte >> 4];
				buf[p++] = HEX_DIGITS[byte & 0x0F];
			}
			return size;
		});

		return result;
	}

	/*
		@brief Decodes a hexadecimal string back into a standard string.
	 	@throws std::invalid_argument If the input length is odd or contains invalid hex characters.
	 */
	std::string hexToString(const std::string& input) {
		if (input.length() % 2 != 0) {
			throw std::invalid_argument("Hex string length must be even.");
		}
		if (input.empty()) return {};

		std::string result;
		// Direct internal buffer write to prevent overhead
		result.resize_and_overwrite(input.length() / 2, [&input](char* buf, size_t size) -> size_t {
			const char* src = input.data();
			const char* end = src + input.length();
			size_t p = 0;

			// Fast allocation-free parsing using std::from_chars
			while (src < end) {
				uint8_t byte_val = 0;
				auto [ptr, ec] = std::from_chars(src, src + 2, byte_val, 16);
				
				if (ec != std::errc{}) {
					throw std::invalid_argument("Invalid hexadecimal character detected.");
				}

				buf[p++] = static_cast<char>(byte_val);
				src += 2;
			}
			return size;
		});

		return result;
	}

	bool versionVerification(const std::string& currentVersion, const std::string& inputVersion) {
		return currentVersion == inputVersion;
	}

	bool formatVerification(const std::string& currentFormat, const std::string& inputFormat) {
		return currentFormat == inputFormat;
	}
	
	bool structureVerification(const std::string& inputStructData);
	bool metadataVerification(const std::string& inputMetadata);
	bool hexPayloadVerification(const std::string& inputHexPayload);
	bool symbolVerification(const std::string& inputSymbol);

	bool writterComponentSpecData(
		const std::string& title,
		const std::string& version,
		const std::string& metadata,
		const std::string& rawData,
		const std::string& symbolData);

	bool readerComponentSpecData(
		const std::string& title,
		const std::string& version,
		const std::string& metadata,
		const std::string& rawData,
		const std::string& symbolData);
}