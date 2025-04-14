#ifndef MYDIC_H //if not defined, 여기서 MYDIC_H 가 정의되지 않았으면 그 아래 코드를 실행하겠다는 뜻
#define MYDIC_H
#include <string>
#include <fstream>//ifstream이라는 데이터를 읽어오는 클래스를 쓰기위해 헤더로 선언
#include <iostream>
using namespace std;


#define MAXWORDS 100 //최대 단어수를 정의하는 상수 -> 단어의 개수를 100개로 제한

struct WordPair {
    string eng;  // 구조체 안에는 변수가 들어가야한다 영어 단어 한글은 저장을 해야하므로add()함수를 이용한다, 
    string kor;
};

class Mydic{
private:
    WordPair words[MAXWORDS]; //C++에서 배열은 만들 때 크기를 미리 정해야 해 -> 그래서 위에 #define 선언을 통해 MAXWORDS을 100으로 크기를 미리지정
    int nWords;

public:
    Mydic() : nWords(0) {}

// 하나의 단어 추가
void add(string eng, string kor) {
    if (nWords < MAXWORDS) {
        words[nWords].eng = eng;
        words[nWords].kor = kor;
        nWords++;
    } else {
        cout << "단어를 더 이상 추가할 수 없습니다!" << endl;
    }
}

// 파일에서 단어 읽기
void load(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }
    nWords = 0;
    string eng, kor;
    while (fin >> eng >> kor) {  // 파일은 "영어 한글" 순서로 저장돼 있다고 가정
        add(eng, kor);
    }
    fin.close();
}

// 파일에 모든 단어 저장
void store(string filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "파일을 저장할 수 없습니다: " << filename << endl;
        return;
    }
    for (int i = 0; i < nWords; i++) {
        fout << words[i].eng << " " << words[i].kor << endl;
    }
    fout.close();
}

// 모든 단어를 화면에 출력
void print() {
    for (int i = 0; i < nWords; i++) {
        cout << i << ": " << words[i].eng << " - " << words[i].kor << endl;
    }
}

// id 번째 영어 단어 반환
string getEng(int id) {
    if (id >= 0 && id < nWords) {
        return words[id].eng;
    }
    return "";  // 잘못된 id라면 빈 문자열 반환
}

// id 번째 한글 뜻 반환
string getKor(int id) {
    if (id >= 0 && id < nWords) {
        return words[id].kor;
    }
    return "";  // 잘못된 id라면 빈 문자열 반환
    }
};













#endif