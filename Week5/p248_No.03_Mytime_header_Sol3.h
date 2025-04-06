#ifndef MYTIME_H
#define MYTIME_H

typedef struct {
    int hour;
    int minute;
    int second;
    int millisecond;
} MyTime;

void addTime(MyTime t1, MyTime t2, MyTime *t3);

#endif // MYTIME_H
