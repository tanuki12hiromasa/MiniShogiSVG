// MiniShogiSVG.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "kyokumen.h"
#include "DrawSVG.h"
#include "SvgHtml.h"
#include "sfen.h"

int main()
{
    //Kyokumen kyokumen;
    //kyokumen.s_mochi[0] = 2;
    //kyokumen.g_mochi[3] = 2;
    //DrawSVG::foutKyokumenSVG("test.svg", kyokumen);
    while (true) {
        std::cout << "input sfen > ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "q" || line == "quit") return 0;
        const auto kifu = sfen::SFENtoKifu(line);
        std::string folder = "./svg/" + Util::DateTimeString();
        std::filesystem::create_directories(folder);
        for (std::size_t i = 0; i < kifu.size(); i++) {
            const std::string path = (folder + "/" + std::to_string(i) + ".svg");
            DrawSVG::foutKyokumenSVG(path, kifu[i]);
        }
    }

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
