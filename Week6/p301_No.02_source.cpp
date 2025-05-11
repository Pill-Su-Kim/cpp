#include "p301_No.02_header.h"

int main() {
    // Mydic 클래스 객체 생성
    Mydic myDic;

    // 사용자로부터 단어 등록
    int n;
    cout << "등록할 단어 수를 입력하세요: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string eng, kor;
        cout << i + 1 << "번째 단어 (영어): ";
        cin >> eng;
        cout << i + 1 << "번째 단어 (한글 뜻): ";
        cin >> kor;
        myDic.add(eng, kor);
    }

    // 단어들을 파일에 저장
    string filename = "mydictionary.txt";
    myDic.store(filename);
    cout << "\n단어들을 파일 '" << filename << "'에 저장했습니다." << endl;

    // 새로운 객체로 파일에서 단어 읽기
    Mydic newDic;        //load함수를 통해 파일을"mydictionary.txt"파일을 읽고 불러온다
    newDic.load(filename);

    // 파일에서 읽은 단어장 출력
    cout << "\n파일에서 읽은 단어장 출력:" << endl;
    newDic.print();

    return 0;
}
