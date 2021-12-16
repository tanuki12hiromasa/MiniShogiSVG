#include <chrono>
#include <sstream>
#include <cassert>
#include "kyokumen.h"

bool Util::isSente(Koma koma) {
	if ((int)koma >= (int)Koma::g_Min) return false;
	else return true;
}
Koma Util::promote(Koma koma) {
	return (Koma)((int)koma + (int)Koma::Nari);
}
int Util::capture(Koma koma) {
	const auto x = (int)koma;
	if (x < (int)Koma::s_Ou) {
		return x;
	}
	else if(x < (int)Koma::g_Fu) {
		return x - (int)Koma::s_nFu;
	}
	else if (x < (int)Koma::g_Ou) {
		return x - (int)Koma::g_Fu;
	}
	else {
		return x - (int)Koma::g_nFu;
	}
}
Koma Util::summon(bool teban, int dai) {
	if (teban) {
		return (Koma)(dai);
	}
	else {
		return (Koma)(dai + (int)Koma::g_Fu);
	}
}

Koma Util::usiToKoma(const char c) {
	switch (c) {
		case 'P': return Koma::s_Fu;
		case 'S': return Koma::s_Gin;
		case 'B': return Koma::s_Kaku;
		case 'R': return Koma::s_Hi;
		case 'G': return Koma::s_Kin;
		case 'K': return Koma::s_Ou;
		case 'p': return Koma::g_Fu;
		case 's': return Koma::g_Gin;
		case 'b': return Koma::g_Kaku;
		case 'r': return Koma::g_Hi;
		case 'g': return Koma::g_Kin;
		case 'k': return Koma::g_Ou;
		default: return Koma::None;
	}
}

int Util::usiToMochiNum(char c) {
	c = std::toupper(c);
	switch (c) {
		case 'P': return 0;
		case 'S': return 1;
		case 'B': return 2;
		case 'R': return 3;
		case 'G': return 4;
		default: return 0;
	}
}

std::vector<std::string> Util::Split(const std::string& text, char splitter) {
	std::vector<std::string> tokens;
	std::stringstream ss(text);
	std::string token;
	while (std::getline(ss, token, splitter)) {
		tokens.push_back(token);
	}
	return tokens;
}

std::string Util::DateTimeString() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string s(30, '\0');
	std::tm ima;
	localtime_s(&ima, &now);
	std::strftime(&s[0], s.size(), "%Y%m%d-%H%M", &ima);
	s.resize(s.find('\0'));
	return s;
}

Move::Move(const std::string& usi) {
	if (usi[1] == '*') {
		switch (usi[0]) {
			case 'P': from_dai = 0; break;
			case 'S': from_dai = 1; break;
			case 'B': from_dai = 2; break;
			case 'R': from_dai = 3; break;
			case 'G': from_dai = 4; break;
			default: from_dai = -1; break;
		}
		from.first = -1;
	}
	else {
		from.first = usi[0] - '1';
		from.second = usi[1] - 'a';
		from_dai = -1;
	}
	to.first = usi[2] - '1';
	to.second = usi[3] - 'a';
	prom = (usi[4] == '+');
}

Kyokumen Kyokumen::emptyKyokumen() {
	return Kyokumen({ std::array<Koma, 5>{Koma::None, Koma::None, Koma::None, Koma::None,Koma::None},
		std::array<Koma, 5>{Koma::None, Koma::None,Koma::None,Koma::None,Koma::None},
		std::array<Koma, 5>{Koma::None,Koma::None,Koma::None,Koma::None, Koma::None},
		std::array<Koma, 5>{Koma::None,Koma::None,Koma::None,Koma::None,Koma::None},
		std::array<Koma, 5>{Koma::None,Koma::None,Koma::None,Koma::None, Koma::None} },
		{ 0,0,0,0,0 }, { 0,0,0,0,0 }, true);
}

Kyokumen::Kyokumen()
	: bammen({std::array<Koma, 5>{Koma::g_Ou, Koma::g_Fu, Koma::None, Koma::None,Koma::s_Hi},
		std::array<Koma, 5>{Koma::g_Kin, Koma::None,Koma::None,Koma::None,Koma::s_Kaku},
		std::array<Koma, 5>{Koma::g_Gin,Koma::None,Koma::None,Koma::None, Koma::s_Gin},
		std::array<Koma, 5>{Koma::g_Kaku,Koma::None,Koma::None,Koma::None,Koma::s_Kin},
		std::array<Koma, 5>{Koma::g_Hi,Koma::None,Koma::None,Koma::s_Fu, Koma::s_Ou}}),
	s_mochi({0,0,0,0,0}),
	g_mochi({0,0,0,0,0})
{}

Kyokumen::Kyokumen(const std::array<std::array<Koma, 5>, 5>& bammen,
	const std::array<int, 5>& s_mochi, const std::array<int, 5>& g_mochi, bool teban) 
	: bammen(bammen), s_mochi(s_mochi), g_mochi(g_mochi), teban(teban)
{}

Kyokumen::Kyokumen(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
	:Kyokumen()
{
	if (*begin == "startpos") {
		return;
	}
	else {
		assert(*begin == "sfen");
		assert(std::distance(begin, end) >= 5);
		//盤面
		std::vector<std::string> usiban(Util::Split(*(begin + 1), '/'));
		int dan = 0;
		for (auto& line : usiban) {
			int suji = 4;
			for (auto c = line.begin(), end = line.end(); c != end; ++c) {
				if ('0' < *c && *c <= '5') {
					for (int num = *c - '0'; num > 0; --num) {
						bammen[suji][dan] = Koma::None;
						--suji;
					}
				}
				else {
					if (*c == '+') {
						++c;
						bammen[suji][dan] = Util::promote(Util::usiToKoma(*c));
					}
					else {
						bammen[suji][dan] = Util::usiToKoma(*c);
					}
					--suji;
				}
			}
			++dan;
		}
		//手番
		teban = (*(begin + 3) == "b");
		//持ち駒
		const auto& mStr = *(begin + 4);
		if (mStr.front() != '-') {
			for (auto c = mStr.begin(), end = mStr.end(); c != end; ++c) {
				unsigned num = 1;
				if (*c == '1') {
					c++;
					num = *c - '0' + 10u;
					c++;
				}
				else if ('1' < *c && *c <= '5') {
					num = *c - '0';
					c++;
				}
				if (std::isupper(*c)) {
					s_mochi[Util::usiToMochiNum(*c)] = num;
				}
				else {
					g_mochi[Util::usiToMochiNum(*c)] = num;
				}
			}
		}
	}
}

void Kyokumen::proceed(const Move& move) {
	if (move.from.first >= 0) {
		const auto cap = bammen[move.to.first][move.to.second];
		bammen[move.to.first][move.to.second] = bammen[move.from.first][move.from.second];
		bammen[move.from.first][move.from.second] = Koma::None;
		if (move.prom == true) bammen[move.to.first][move.to.second] = Util::promote(bammen[move.to.first][move.to.second]);
		if (cap != Koma::None) {
			if (teban) s_mochi[Util::capture(cap)]++;
			else g_mochi[Util::capture(cap)]++;
		}
	}
	else {
		bammen[move.to.first][move.to.second] = Util::summon(teban, move.from_dai);
		if (teban) s_mochi[move.from_dai]--;
		else g_mochi[move.from_dai]--;
	}
	teban = !teban;
}
