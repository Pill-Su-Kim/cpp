#ifndef MYTIME_H
#define MYTIME_H

typedef struct {
    int hour;
    int minute;
    int second;
    int millisecond;
} MyTime;

MyTime addTime(MyTime t1, MyTime t2);

#endif // MYTIME_H
