#include "sfen.h"

std::vector<Kyokumen> SFENtoKifu(const std::string& sfen) {
	std::vector<Kyokumen> kifu;
	const auto tokens = Util::Split(sfen, ' ');
	auto begin = (tokens[0] == "position") ? (tokens.begin() + 1) : tokens.begin();
	Kyokumen kyokumen(begin, tokens.end());
	kifu.push_back(kyokumen);
	const auto moves_begin = (*begin == "startpos") ? (begin + 2) : (begin + 6);
	if (moves_begin == tokens.end()) return kifu;
	for (auto it = moves_begin + 1; it != tokens.end(); it++) {
		Move move(*it);
		kyokumen.proceed(move);
		kifu.push_back(kyokumen);
	}
	return kifu;
}