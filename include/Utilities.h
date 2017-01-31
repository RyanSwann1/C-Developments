#pragma once

#include "Animations/AnimationDetails.h"
#include <string>
#include <utility>
#include <vector>

namespace Utilities
{
	const std::string& getEntityDetails(const std::string& id);
	const std::string& getInteractiveTileDetails(const std::string& id);
	const std::string& getEventDetails();
	const std::string& getMapDetails();

	const std::vector<std::pair<std::string, AnimationDetails>>& getAnimationDetails(const std::string& owner);
};
