// MecabTest.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <mecab.h>
#include <fstream>
#include <sstream>
#include<vector>

using namespace std;

/*
*形態素解析結果のタブをカンマに置換
*@param string mecabの元のstring
*@return string
*/
string replace_tab_to_commma (string original_mecab) {
	//タブをカンマに置換
	string target = "\t";
	string repl = ",";
	auto position = original_mecab.find (target);
	auto len = target.length ();
	string::size_type pos = 0;
	while(( pos = original_mecab.find (target, pos) ) != string::npos) {
		original_mecab.replace (pos, len, repl);
		pos += repl.length();
	}
	return original_mecab;
}


/*
*区切り文字で区切り、配列に詰める
*@param string 形態素解析の一行
*@return string[]
*/
vector<string> make_vector (string &line, char sep) {
	//戻り値を宣言
	vector<string> v;

	stringstream str (line);
	string buffer;
	while(getline (str, buffer, sep)) {
		v.push_back (buffer);
	}
	return v;
}

int main(int argc, char **argv)
{
	//テキストファイルを取得
	ifstream str("C:/Users/Fate/Desktop/test3.txt");
	//存在しなければ終了
	if (!str) return 1;
	//テキストストリームのポインタを最後に指定
	str.seekg(0, fstream::end);
	unsigned long eofPos = str.tellg();
	//テキストストリームのポインタをclear
	str.clear();
	//テキストストリームのポインタを最初に指定
	str.seekg(0, fstream::beg);
	unsigned long begPos = str.tellg();

	unsigned long size = eofPos - begPos;

	//出力用テキストファイルを設定
	ofstream outputfile("C:/Users/Fate/Desktop/testOUT.txt");
	
	//形態素解析結果の配列を詰める配列を宣言
	vector<vector<string>> all_result;
	vector<string> tempVector;
	vector<string> morAnalysis;

	char *input = new char[size];
	//strから行単位で文字列を取得
	while (str.getline(input, size - 1)) {
		MeCab::Tagger *tagger = MeCab::createTagger("");
		const char *result = tagger->parse(input);
		const string resultString = tagger->parse(input);
		string  resultStringComma = replace_tab_to_commma(resultString);
		tempVector=make_vector (resultStringComma, '\n');
		int i = 0;
		while(i < tempVector.size ()-1) {
			all_result.push_back(make_vector (tempVector[i], ','));
			cout << all_result[i][7] << endl;
			i++;
		}
		
		//cout << resultStringComma << endl;

		outputfile << resultStringComma;
	}
	outputfile.close();
	return 0;
}

