#pragma once

#include <string>
#include <unordered_map>

class Utilities
{
public:
	Utilities();

	const std::string& getEntityDetails(const std::string& id) const;
	const std::string& getInteractiveTileDetails(const std::string& id) const;
	inline const std::string& getEventDetails() const { return m_eventsDetails; }
	

private:
	const std::unordered_map<std::string, std::string> m_entityDetails;
	const std::unordered_map<std::string, std::string> m_interactiveTileDetails;
	const std::unordered_map<std::string, std::string> loadInDetails(const std::string& fileName) const;
	const std::string m_eventsDetails;
};