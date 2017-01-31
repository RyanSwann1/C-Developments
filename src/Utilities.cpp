#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <unordered_map>

namespace {
	const std::unordered_map<std::string, std::vector<std::pair<std::string, AnimationDetails>>> loadInAnimationDetails()
	{
		std::unordered_map<std::string, std::vector<std::pair<std::string, AnimationDetails>>> animationDetails;
		std::ifstream file("Animations.txt");
		assert(file.is_open());
	
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '|')
			{
				continue;
			}
	
			std::stringstream keyStream(line);
			
			std::string ownerName, animationName, tileSheetName;
			sf::Vector2f drawLocationSize;
			int startRow = 0, endRow = 0, column = 0, repeatable = 0, reversible = 0;
			float frameTime = 0;
	
			//| Owner | SpriteSheet | Name | StartRow | EndRow | Column | FrameTime | Repeatable | DrawLocationSize | Reversible
			//	Bouncy
	
			keyStream >> ownerName >> tileSheetName >> animationName >> startRow >> endRow >> column >> frameTime >> repeatable >> drawLocationSize.x >> drawLocationSize.y >> reversible;
	
			auto cIter = animationDetails.find(ownerName);
			if (cIter != animationDetails.cend())
			{
				cIter->second.push_back(std::make_pair(animationName, AnimationDetails(animationName, tileSheetName, startRow, endRow, column, frameTime, repeatable, drawLocationSize, reversible)));
			}
			else
			{
				animationDetails.emplace(ownerName, std::vector<std::pair<std::string, AnimationDetails>>
				{
					std::make_pair(animationName, AnimationDetails(animationName, tileSheetName, startRow, endRow, column, frameTime, repeatable, drawLocationSize, reversible))
				});
			}
		}
	
		return animationDetails;
	}
	
	std::unordered_map<std::string, std::string> loadInDetails(const std::string & fileName)
	{
		std::fstream file(fileName);
		assert(file.is_open());
		std::unordered_map<std::string, std::string> container;
	
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '/')
			{
				continue;
			}
			std::stringstream keyStream(line);
			std::string name;
			std::string location;
	
			keyStream >> name >> location;
			std::cout << name << "\n";
			std::cout << location << "\n";
			assert(container.emplace(name, location).second);
		}
	
		return container;
	}

	const std::unordered_map<std::string, std::string> m_entityDetails(loadInDetails("EntityDetails.txt"));
	const std::unordered_map<std::string, std::string> m_interactiveTileDetails(loadInDetails("InteractiveTileDetails.txt"));
	const std::unordered_map<std::string, std::vector<std::pair<std::string, AnimationDetails>>> m_animationDetails(loadInAnimationDetails());
	const std::string m_eventDetails = "Keys.txt";
	const std::string m_mapDetails = "Maps.txt";
}

const std::string & Utilities::getEntityDetails(const std::string & id)
{
	auto cIter = m_entityDetails.find(id);
	assert(cIter != m_entityDetails.cend());

	return cIter->second;	
}

const std::string & Utilities::getInteractiveTileDetails(const std::string & id)
{
	auto cIter = m_interactiveTileDetails.find(id);
	assert(cIter != m_interactiveTileDetails.cend());

	return cIter->second;	
}

const std::vector<std::pair<std::string, AnimationDetails>>& Utilities::getAnimationDetails(const std::string& owner)
{
	auto cIter = m_animationDetails.find(owner);
	assert(cIter != m_animationDetails.cend());
	
	return cIter->second;
}

const std::string& Utilities::getEventDetails() 
{ 
	return m_eventDetails; 
}

const std::string& Utilities::getMapDetails() 
{ 
	return m_mapDetails; 
}


