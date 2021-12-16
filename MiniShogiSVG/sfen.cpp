#include "sfen.h"

std::vector<Kyokumen> sfen::SFENtoKifu(const std::string& sfen) {
	std::vector<Kyokumen> kifu;
	const auto tokens = Util::Split(sfen, ' ');
	auto begin = (tokens[0] == "position") ? (tokens.begin() + 1) : tokens.begin();
	Kyokumen kyokumen(begin, tokens.end());
	kifu.push_back(kyokumen);
	auto moves_begin = begin; 
	if (*begin == "startpos") {
		if (tokens.size() <= 2) return kifu;
		moves_begin += 2;
	}
	else {
		if(tokens.size() <= 6) return kifu;
		moves_begin += 6;
	}
	for (auto it = moves_begin; it != tokens.end(); it++) {
		if (*it == "resign") break;
		Move move(*it);
		kyokumen.proceed(move);
		kifu.push_back(kyokumen);
	}
	return kifu;
}