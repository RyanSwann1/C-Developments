#pragma once

#include "Animations/AnimationDetails.h"
#include <string>
#include <utility>
#include <vector>

namespace Utilities
{
    // See http://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
    struct EnumClassHash {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    const std::string& getEntityDetails(const std::string& id);
    const std::string& getInteractiveTileDetails(const std::string& id);
    const std::string& getEventDetails();
    const std::string& getMapDetails();

    const std::vector<std::pair<std::string, AnimationDetails>>& getAnimationDetails(const std::string& owner);
}
