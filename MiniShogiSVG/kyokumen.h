#pragma once
#include <cstdint>
#include <array>
#include <fstream>
#include <vector>

enum class Koma {
	s_Fu, s_Gin, s_Kaku, s_Hi, s_Kin, s_Ou,
	s_nFu, s_nGin, s_nKaku, s_nHi,
	g_Fu, g_Gin, g_Kaku, g_Hi, g_Kin, g_Ou,
	g_nFu, g_nGin, g_nKaku, g_nHi,
	KomaNum,
	None,
	Nari = s_nFu - s_Fu,
	Sengo = g_Fu - s_Fu,
	Min = s_Fu,
	s_Min = s_Fu, s_Max = s_nHi, s_Num = s_Max + 1,
	g_Min = g_Fu, g_Max = g_nHi, g_Num = KomaNum
};

class Util {
public:
	static bool isSente(Koma);
	static Koma promote(Koma);
	static int capture(Koma);
	static Koma summon(bool, int);
	static Koma usiToKoma(char);
	static int usiToMochiNum(char);
	static std::vector<std::string> Split(const std::string& text, char splitter = ' ');
	static std::string DateTimeString();
};

using Vec2 = std::pair<int, int>;

class Move {
public:
	Move(const std::string& usi);

	Vec2 from;
	Vec2 to;
	bool prom;
	int from_dai;
};

class Kyokumen {
public:
	static Kyokumen emptyKyokumen();
public:
	Kyokumen();
	Kyokumen(const std::array<std::array<Koma, 5>, 5>& bammen, 
		const std::array<int, 5>& s_mochi, const std::array<int, 5>& g_mochi, bool teban);
	Kyokumen(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);
	void proceed(const Move& move);

	std::array<std::array<Koma, 5>, 5> bammen;
	std::array<int, 5> s_mochi, g_mochi;
	bool teban = true;
};


