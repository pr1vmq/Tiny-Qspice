#pragma once
#include <string>
#include <ranges>
#include <format>
#include <numeric>

namespace qcpnManager {
	std::string stringToHex(const std::string& input);
	std::string hexToString(const std::string& input);

	bool versionVerification(const std::string& currentVersion, const std::string& inputVersion);
	bool formatVerification(const std::string& inputFormatName);
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