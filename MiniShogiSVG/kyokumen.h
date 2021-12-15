#pragma once
#include <cstdint>
#include <array>
#include <fstream>

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
	static Kyokumen getStartpos(const std::string& sfen);
	static Kyokumen getLastpos(const std::string& sfen);
public:
	Kyokumen();
	void proceed(const Move& move);

	std::array<std::array<Koma, 5>, 5> bammen;
	std::array<int, 5> s_mochi, g_mochi;
	bool teban = true;
};

class DrawSVG {
public:
	static void head(std::ostream& stream);
	static void tail(std::ostream& stream);
	static void drawLine(std::ostream& stream, double x1, double y1, double x2,double y2);
	static void drawRect(std::ostream& stream, double x, double y, double width, double height);

	static void drawKomadai(std::ostream& stream, double x, double y, const std::string& daicolor = "fill=\"rgb(255,242,169)\"");
	static void drawShogiBan(std::ostream& stream, double x, double y, const std::string& bancolor = "fill=\"rgb(255,242,169)\"");
	static void drawDanChar(std::ostream& stream, double x, double y);
	static void drawSujiChar(std::ostream& stream, double x, double y);
	static void drawCharKoma(std::ostream& stream, Koma koma, double x, double y);
	static void drawPentKoma(std::ostream& stream, Koma koma, double x, double y);
	static void drawCharKomadai(std::ostream& stream, const std::array<int, 5>&, bool teban, double x, double y);
	static void drawGraphicalKomadai(std::ostream& stream, const std::array<int, 5>&, bool teban, double x, double y, const std::string& daicolor = "fill=\"rgb(255,242,169)\"");
	
	static void drawKyokumen(std::ostream& stream, const Kyokumen& kyokumen);

	//static constexpr double yohaku = 2;
	static constexpr double komaWidth = 58;
	static constexpr double komaHeight = 60;

};

