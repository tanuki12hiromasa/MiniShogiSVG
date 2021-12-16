#pragma once
#include "kyokumen.h"

class DrawSVG {
public:
	static void head(std::ostream& stream);
	static void tail(std::ostream& stream);
	static void drawLine(std::ostream& stream, double x1, double y1, double x2, double y2);
	static void drawRect(std::ostream& stream, double x, double y, double width, double height);

	static void drawKomadai(std::ostream& stream, double x, double y, const std::string& daicolor = "fill=\"rgb(255,242,169)\"");
	static void drawShogiBan(std::ostream& stream, double x, double y, const std::string& bancolor = "fill=\"rgb(255,242,169)\"");
	static void drawDanChar(std::ostream& stream, double x, double y);
	static void drawSujiChar(std::ostream& stream, double x, double y);
	static void drawCharKoma(std::ostream& stream, Koma koma, double x, double y);
	static void drawCharKomadai(std::ostream& stream, const std::array<int, 5>&, bool teban, double x, double y, bool myteban = false);

	static void drawKyokumen(std::ostream& stream, const Kyokumen& kyokumen);
	static void drawKyokumenSVG(std::ostream& stream, const Kyokumen& kyokumen);
	static void foutKyokumenSVG(const std::string& path, const Kyokumen& kyokumen);

	//static constexpr double yohaku = 2;
	static constexpr double komaWidth = 58;
	static constexpr double komaHeight = 60;

};
