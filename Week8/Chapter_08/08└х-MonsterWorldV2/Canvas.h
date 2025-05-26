#pragma once
#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;

class Canvas {
	string line[MAXLINES];	// ȭ�� ����� ���� ���ڿ�
	int xMax, yMax;		// ���� ũ��
public:
	Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax , '.');
	}
	void draw(int x, int y, string val) {
		if (x >= 0 && y >= 0 && x<xMax && y<yMax)
			line[y].replace(x * 2, 2, val);
	}
	void clear(string val = ". ") {		// ����Ʈ �Ű�����: ���� 2��
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				draw(x, y, val);
	}
	void print(char *title = "<My Canvas>") {
		system("cls");
		cout << title << endl;
		for (int y = 0; y < yMax; y++)
			cout << line[y] << endl;
		cout << endl;
	}
};