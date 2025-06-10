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
            // 한글 등 2바이트 문자를 고려하여 너비를 2배로 설정
            line[y] = string(xMax * 2, ' '); 
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            // 문자열이 화면 버퍼를 넘어가지 않도록 위치 계산
            line[y].replace(x * 2, val.length(), val);
        }
    }
    void clear(string val = ". ") {  // 디폴트 값: '. '
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char *title = "<My canvas>") { // const char*로 타입 변경
        system("clear"); // 리눅스에서 화면 지우기
        cout << title << endl;
        for (int y = 0; y < yMax; y++)
            cout << line[y] << endl;
        cout << endl;
    }
};