#pragma once
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;

class Canvas {
    string line[MAXLINES];  // 화면 출력을 위한 문자열 배열
    int xMax, yMax;        // 캔버스 크기
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = string(xMax * 2, 'O');
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax && x * 2 + 2 <= line[y].size()) {
            // val이 2문자가 되도록 패딩
            string padded_val = val;
            if (padded_val.size() < 2) {
                padded_val += " "; // 길이가 1인 경우 공백 추가
            } else if (padded_val.size() > 2) {
                padded_val = padded_val.substr(0, 2); // 2자로 자름
            }
            line[y].replace(x * 2, 2, padded_val);
        }
    }
    void clear(string val = "O ") {  // 디폴트 값: 'O '
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(char *title = "<My canvas>") {
        system("clear"); // 리눅스에서 화면 지우기
        cout << title << endl;
        for (int y = 0; y < yMax; y++)
            cout << line[y] << endl;
        cout << endl;
    }
};
