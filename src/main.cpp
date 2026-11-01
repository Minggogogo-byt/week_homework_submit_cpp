#include "student.h"
int main()
{
    Student s("小明", 80.5);
    cout << "修改前：" << endl;
    s.showInfo();

    s.changeScore(93.0);

    cout << "修改后：" << endl;
    s.showInfo();
    return 0;
}