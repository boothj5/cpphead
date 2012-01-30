#ifndef CHOOSERS_H
#define CHOOSERS_H

#include <vector>
#include "card.hpp"
#include "player_helper.hpp"

namespace choose {

void lowestFromSorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void lowestFromUnsorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void highestFromSorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void highestFromUnsorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void randomFromSorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void randomFromUnsorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void burnThenLowestFromSorted(const std::vector<Card>&, const PlayerHelper& helper, 
    std::vector<int>&);

void burnThenLowestFromUnsorted(const std::vector<Card>&, 
    const PlayerHelper& helper, std::vector<int>&);

} // namespace choose

#endif
