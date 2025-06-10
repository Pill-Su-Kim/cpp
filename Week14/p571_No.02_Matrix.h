#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
	int rows, cols;		// 행과 열의 크기
	int** mat;		    // 동적 할당된 2차원 배열
public:
	Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
		if (r > 0 && c > 0) {
			mat = new int*[rows];
			for (int i = 0; i < rows; i++)
				mat[i] = new int[cols];
		}
	}
	~Matrix() {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				delete[] mat[i];
			delete[] mat;
		}
	}
	int& elem(int x, int y) { return mat[y][x]; }
	int Rows() { return rows; }
	int Cols() { return cols; }
	int** Data() { return mat; };
	void print(const char *str = "Mat") { // const char*로 타입 변경
		cout << str << " " << rows << "x" << cols << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				cout << setw(4) << mat[i][j];
			cout << "\n";
		}
	}
	void setRand(int val = 100) {
		if (mat != NULL) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					mat[i][j] = (rand() % val);
		}
	}
};