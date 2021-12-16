#include "DrawSVG.h"


void DrawSVG::head(std::ostream& stream) {
	stream << "<?xml version=\"1.0\"?>\n"
		<< R"***(<svg 
	id="svg"
	xmlns = "http://www.w3.org/2000/svg"
    width="400"
    height="350"
    viewBox="0 0 400 350"
    preserveAspectRatio="xMidYMid meet">
)***";
}

void DrawSVG::tail(std::ostream& stream) {
	stream << "</svg>" << std::endl;
}

void DrawSVG::drawLine(std::ostream& stream, double x1, double y1, double x2, double y2) {
	stream << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\""
		<< " stroke=\"black\" stroke-width=\"0.5\" />\n";
}

void DrawSVG::drawRect(std::ostream& stream, double x, double y, double width, double height) {
	stream << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\""
		<< " fill=\"rgb(255,242,169)\" stroke=\"black\" stroke-width=\"1\" />\n";
}

void DrawSVG::drawShogiBan(std::ostream& stream, const double x, const double y, const std::string& bancolor) {
	//下地
	//{
	//	const double width = yohaku + komaWidth * 5 + yohaku;
	//	const double height = yohaku + komaHeight * 5 + yohaku;
	//	stream << "";
	//}

	//外枠
	stream << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << komaWidth * 5 << "\" height=\"" << komaHeight * 5 << "\""
		<< " " << bancolor << " stroke=\"black\" stroke-width=\"2\" />\n";
	//格子
	for (int xi = 1; xi < 5; xi++) {
		stream << "<line x1=\"" << x + komaWidth * xi << "\" y1=\"" << y << "\" "
			<< "x2=\"" << x + komaWidth * xi << "\" y2=\"" << y + komaHeight * 5 << "\""
			<< " stroke=\"black\" stroke-width=\"1\" />\n";
	}
	for (int yi = 1; yi < 5; yi++) {
		stream << "<line x1=\"" << x << "\" y1=\"" << y + komaHeight * yi << "\" "
			<< "x2=\"" << x + komaWidth * 5 << "\" y2=\"" << y + komaHeight * yi << "\""
			<< " stroke=\"black\" stroke-width=\"1\" />\n";
	}
}

void DrawSVG::drawKomadai(std::ostream& stream, double x, double y, const std::string& daicolor) {
	stream << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << komaWidth * 2 << "\" height=\"" << komaHeight * 4 << "\""
		<< " " << daicolor << " stroke=\"black\" stroke-width=\"1\" />\n";
}

void DrawSVG::drawDanChar(std::ostream& stream, double x, double y) {
	for (int i = 0; i < 5; i++) {
		stream << "<text x=\"" << x << "\" y=\"" << y + komaHeight * i << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "style=\"font-size: 18px; fill: #000000;\">\n";
		switch (i)
		{
			case 0: stream << u8"一"; break;
			case 1: stream << u8"二"; break;
			case 2: stream << u8"三"; break;
			case 3: stream << u8"四"; break;
			case 4: stream << u8"五"; break;
		}
		stream << "\n</text>\n";
	}
}

void DrawSVG::drawSujiChar(std::ostream& stream, double x, double y) {
	for (int i = 0; i < 5; i++) {
		stream << "<text x=\"" << x + komaWidth * (4LL - i) << "\" y=\"" << y << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "style=\"font-size: 18px; fill: #000000;\">\n";
		switch (i)
		{
			case 0: stream << u8"１"; break;
			case 1: stream << u8"２"; break;
			case 2: stream << u8"３"; break;
			case 3: stream << u8"４"; break;
			case 4: stream << u8"５"; break;
		}
		stream << "\n</text>\n";
	}
}

void DrawSVG::drawCharKoma(std::ostream& stream, Koma koma, double x, double y) {
#if 1 //chrome用レイアウト
	if (Util::isSente(koma)) {
		stream << "<text x=\"" << x << "\" y=\"" << y << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "style=\"font-size: 50px; fill: #000000;\">\n";
	}
	else {
		stream << "<text x=\"" << x << "\" y=\"" << y << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "transform=\"rotate(180 " << x << "," << y - 2 << ")\" "
			<< "style=\"font-size: 50px; fill: #000000;\">\n";
	}
#else //パワポ用レイアウト(調整できてない)
	if (Util::isSente(koma)) {
		stream << "<text x=\"" << x << "\" y=\"" << y + 17 << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "style=\"font-size: 50px; fill: #000000;\">\n";
	}
	else {
		stream << "<text x=\"" << x << "\" y=\"" << y + 17 << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"middle\" dominant-baseline=\"central\" "
			<< "transform=\"rotate(180 " << x << "," << y << ")\" "
			<< "style=\"font-size: 50px; fill: #000000;\">\n";
	}
#endif
	switch (koma)
	{
		case Koma::s_Fu:
		case Koma::g_Fu:
			stream << u8"歩";
			break;
		case Koma::s_Gin:
		case Koma::g_Gin:
			stream << u8"銀";
			break;
		case Koma::s_Kaku:
		case Koma::g_Kaku:
			stream << u8"角";
			break;
		case Koma::s_Hi:
		case Koma::g_Hi:
			stream << u8"飛";
			break;
		case Koma::s_Kin:
		case Koma::g_Kin:
			stream << u8"金";
			break;
		case Koma::s_Ou:
			stream << u8"王";
			break;
		case Koma::g_Ou:
			stream << u8"玉";
			break;
		case Koma::s_nFu:
		case Koma::g_nFu:
			stream << u8"と";
			break;
		case Koma::s_nGin:
		case Koma::g_nGin:
			stream << u8"全";
			break;
		case Koma::s_nKaku:
		case Koma::g_nKaku:
			stream << u8"馬";
			break;
		case Koma::s_nHi:
		case Koma::g_nHi:
			stream << u8"龍";
			break;
	}

	stream << "\n</text>\n";
}



void DrawSVG::drawCharKomadai(std::ostream& stream, const std::array<int, 5>& mochi, bool teban, double x, double y) {
	//☖☗

	if (teban) {
		stream << "<text x=\"" << x << "\" y=\"" << y << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"end\" "
			<< "dominant-baseline=\"text-after-edge\" "
			<< "writing-mode=\"tb\" "
			<< "style=\"font-size: 22px; fill: #000000;\">\n";
		stream << u8"☗先手 ";
	}
	else {
		stream << "<text x=\"" << x << "\" y=\"" << y << "\" "
			<< "font-family=\"serif\" "
			<< "text-anchor=\"start\" "
			<< "dominant-baseline=\"text-after-edge\" "
			<< "writing-mode=\"tb\" "
			<< "style=\"font-size: 22px; fill: #000000;\">\n";
		stream << u8"☖後手 ";
	}
	bool anykoma = false;
	if (mochi[0] == 1) { stream << u8"歩"; anykoma = true; }
	if (mochi[0] == 2) { stream << u8"歩二"; anykoma = true; }
	if (mochi[1] == 1) { stream << u8"銀"; anykoma = true; }
	if (mochi[1] == 2) { stream << u8"銀二"; anykoma = true; }
	if (mochi[4] == 1) { stream << u8"金"; anykoma = true; }
	if (mochi[4] == 2) { stream << u8"金二"; anykoma = true; }
	if (mochi[2] == 1) { stream << u8"角"; anykoma = true; }
	if (mochi[2] == 2) { stream << u8"角二"; anykoma = true; }
	if (mochi[3] == 1) { stream << u8"飛"; anykoma = true; }
	if (mochi[3] == 2) { stream << u8"飛二"; anykoma = true; }
	if (!anykoma) {
		stream << u8"持駒なし";
	}
	stream << "\n</text>\n";
}

void DrawSVG::drawKyokumen(std::ostream& stream, const Kyokumen& kyokumen) {
	//drawKomadai(stream, 3, 3);
	drawCharKomadai(stream, kyokumen.g_mochi, false, 3, 20);
	drawShogiBan(stream, 40, 25);
	drawDanChar(stream, komaWidth * 5 + 52, 55);
	drawSujiChar(stream, 70, 15);
	//drawKomadai(stream, 9 + komaWidth * 7, 3 + komaHeight );
	drawCharKomadai(stream, kyokumen.s_mochi, true, 60 + komaWidth * 5 + 5, 25 + komaHeight * 5);
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			const auto& k = kyokumen.bammen[x][y];
			if (k != Koma::None) drawCharKoma(stream, k,
				40 + komaWidth * (4LL - x) + komaWidth / 2,
				26 + komaHeight * y + komaHeight / 2);
		}
	}


}

void DrawSVG::drawKyokumenSVG(std::ostream& stream, const Kyokumen& kyokumen) {
	head(stream);
	drawKyokumen(stream, kyokumen);
	tail(stream);
}

void DrawSVG::foutKyokumenSVG(const std::string& path, const Kyokumen& kyokumen) {
	std::ofstream fs(path);
	head(fs);
	drawKyokumen(fs, kyokumen);
	tail(fs);
}
