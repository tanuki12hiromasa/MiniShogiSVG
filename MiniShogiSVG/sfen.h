#pragma once
#include <vector>
#include "kyokumen.h"

class sfen {
public:
	static std::vector<Kyokumen> SFENtoKifu(const std::string& sfen);

};