class Sample{
    char *name;
public:
    Sample() {}
    Sample(const char * name){}  // 매개변수를 받긴 하지만 아무것도 하지 않는 텅 빈 생성자

};

int main(){
    Sample a("sample");
    Sample b(a);
}