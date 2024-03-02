#include <iostream>
#include <string>

class Person
{
private:
    std::string name;
    int age;

public:
    Person(const std::string &personName, int personAge){
        name=personName;
        age=personAge;
    }
    void display();
};

void Person::display()
{
    std::cout << "姓名" << name << std::endl
              << "年龄" << age << std::endl;
}
int main()
{
    Person zhangsan("张三",18);
    zhangsan.display();
    Person lisi("李四",18);
    lisi.display();
    return 0;
}
