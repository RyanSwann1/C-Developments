#pragma once

#include "Animations\AnimationDetails.h"
#include <string>
#include <unordered_map>
#include <vector>
//http://stackoverflow.com/questions/9321/how-do-you-create-a-static-class-in-c/9348#9348
//http://gameprogrammingpatterns.com/service-locator.html#how-is-the-service-located

//Change this to a namespace - doesn't need to be a class and have an individual lifetime that is tied to a specific object
class Utilities
{
public:
	static const std::string& getEntityDetails(const std::string& id);
	static const std::string& getInteractiveTileDetails(const std::string& id);
	static const std::string& getEventDetails() { return m_eventDetails; }
	static const std::string& getMapDetails() { return m_mapDetails; }

	static const std::vector<std::pair<std::string, AnimationDetails>>& getAnimationDetails(const std::string& owner);

private:
	Utilities() {}
	static const std::unordered_map<std::string, std::string> m_entityDetails;
	static const std::unordered_map<std::string, std::string> m_interactiveTileDetails;
	static const std::unordered_map<std::string, std::vector<std::pair<std::string, AnimationDetails>>> m_animationDetails;
	static const std::string m_eventDetails;
	static const std::string m_mapDetails;

	static std::unordered_map<std::string, std::string> loadInDetails(const std::string& fileName);
	static const std::unordered_map<std::string, std::vector<std::pair<std::string, AnimationDetails>>> loadInAnimationDetails();
};