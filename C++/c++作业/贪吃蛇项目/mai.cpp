#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// 定义蛇的一个部分，包括其坐标和显示字符
class snake
{
    int x, y; // 坐标
    char ch;  // 显示字符
public:
    snake() : x(0), y(0), ch('O') {}             // 构造函数，初始化蛇的部分
    snake(int a, int b) : x(a), y(b), ch('O') {} // 构造函数，设置蛇的部分坐标
    // snake(const snake &ekans) : ch(ekans.ch), x(ekans.x), y(ekans.y) {} // 复制构造函数

    void setCh(char x) { ch = x; }
    char getCh() { return ch; }
    int getX() { return x; }
    void setX(int no) { x = no; }
    int getY() { return y; }
    void setY(int no) { y = no; }
};

// 定义链表节点，用于构建蛇的链表
class node
{
    node *next; // 指向下一个节点的指针
    snake s;    // 蛇的一个部分
public:
    snake getSnake() { return s; }            // 获取蛇的部分
    void setSnake(snake ekans) { s = ekans; } // 设置蛇的部分
    void setNext(node *n) { next = n; }       // 设置下一个节点
    node *getNext() { return next; }          // 获取下一个节点
};

// 定义链表，用于存储蛇的身体部分
class list
{
    node *head; // 链表头指针
    int length; // 链表长度
public:
    list() : head(NULL), length(0) {} // 构造函数，初始化链表
    void add(snake s)
    { // 在链表末尾添加蛇的部分
        node *n = new node;
        n->setSnake(s);
        n->setNext(head);
        head = n;
        length++;
    }
    int listLength() { return length; } // 获取链表长度
    snake get(int n)
    { // 获取指定位置的蛇的部分
        node *temp = head;
        int count = 1;
        while (count != n && temp != NULL)
        {
            count++;
            temp = temp->getNext();
        }
        return temp->getSnake();
    }
    void remove()
    { // 删除链表末尾的节点
        node *temp = head->getNext();
        node *t2 = head;
        while (temp->getNext() != NULL)
        {
            temp = temp->getNext();
            t2 = t2->getNext();
        }
        t2->setNext(NULL);
        delete temp;
        length--;
    }
    void display()
    { // 显示蛇
        int i = 0;
        node *temp = head;
        while (temp != NULL)
        {
            mvaddch(10, 10 + i, temp->getSnake().getCh());
            refresh();
            temp = temp->getNext();
        }
    }
    ~list()
    { // 析构函数，清理链表
        while (head != NULL)
        {
            node *n = head;
            head = head->getNext();
            delete n;
        }
        length = 0;
    }
};
// 定义游戏类，包含游戏逻辑
class game
{
    int score, max_y, max_x, food_x, food_y;
    int dir, prev_dir;
    list l;

public:
    game() : score(0), max_y(0), max_x(0), food_x(0), food_y(0), prev_dir(2), dir(2) {}
    void launch();            // 启动游戏
    void play();              // 开始游戏
    void map();               // 绘制游戏地图
    void genFood();           // 生成食物
    void setSnake();          // 设置蛇的初始位置
    void moveSnake(int dir);  // 移动蛇
    bool checkForCollision(); // 检查是否有碰撞
};

void game::launch()
{
    initscr(); // 初始化ncurses
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE); // 启用键盘映射
    refresh();
    mvprintw(LINES / 2, COLS / 2 - 10, "PRESS ENTER TO CONTINUE");
    int ch;
    // 按回车键开始游戏
    if ((ch = getch()) == 10)
    {
        getmaxyx(stdscr, max_y, max_x);
        play();
    }
    endwin();
}

void game::genFood()
{
    // 在屏幕范围内随机生成食物的位置
    food_y = random() % (max_y - 6) + 4;
    food_x = random() % (max_x - 4) + 2;
    mvprintw(food_y, food_x, "F");
}

void game::map()
{
    box(stdscr, 0, 0);                 // 绘制屏幕边框
    mvprintw(1, 1, "Press q to quit"); // 显示退出提示
    refresh();
}
void game::setSnake()
{
    clear();
    map(); // 绘制地图
    // 初始化蛇的位置
    for (int i = 0; i < 8; i++)
    {
        snake s((COLS / 2) - 8 + i, LINES / 2);
        l.add(s);
        mvprintw(s.getY(), s.getX(), "%c", s.getCh());
    }
    mvprintw(food_y, food_x, "F"); // 显示食物
    refresh();
}

void game::play()
{
    genFood();  // 生成食物
    setSnake(); // 设置蛇的位置
    // 准备开始游戏
    refresh();
    sleep(1);
    int ch = 0;
    timeout(200); // 设置键盘输入超时时间，控制蛇的移动速度
    while ((ch = getch()) != 'q')
    {
        // 根据用户输入的方向键更新蛇的移动方向
        switch (ch)
        {
        case KEY_UP:
            dir = 1;
            break;
        case KEY_DOWN:
            dir = -1;
            break;
        case KEY_RIGHT:
            dir = 2;
            break;
        case KEY_LEFT:
            dir = -2;
            break;
        }
        clear();
        map();                         // 绘制地图
        mvprintw(food_y, food_x, "F"); // 显示食物
        // 防止蛇反向移动
        if (abs(dir) == abs(prev_dir))
        {
            dir = prev_dir;
        }
        moveSnake(dir); // 移动蛇
        refresh();
        if (checkForCollision()) // 检查是否有碰撞
        {
            clear();
            // 游戏结束
            mvprintw(max_y / 2 - 2, max_x / 2 - 8, "GAME OVER");
            refresh();
            sleep(2);
            break; // 退出游戏循环
        }
        prev_dir = dir; // 更新前一个移动方向
    }
}

bool game::checkForCollision()
{
    bool flag = false;
    snake s = l.get(1); // 获取蛇头位置
    int head_x = s.getX();
    int head_y = s.getY();
    // 检查蛇头是否碰到边界
    if (head_x == max_x - 1 || head_y == 1 || head_x == 1 || head_y == max_y - 1)
    {
        return true;
    }
    else
    {
        // 检查蛇头是否碰到蛇身
        int len = l.listLength();
        for (int i = 4; i < len; i++)
        {
            s = l.get(i);
            if (head_x == s.getX() && head_y == s.getY())
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
}

void game::moveSnake(int dir)
{
    snake k;
    k = l.get(1); // 获取蛇头位置
    int x = k.getX(), y = k.getY();
    // 根据移动方向更新蛇头位置
    if (dir == 1)
        y--;
    else if (dir == -2)
        x--;
    else if (dir == -1)
        y++;
    else
        x++;
    snake s(x, y); // 创建新的蛇头位置
    l.add(s);      // 将新的蛇头添加到链表
    // 如果蛇头吃到食物，生成新的食物
    if (x == food_x && y == food_y)
    {
        genFood();
    }
    else
    {
        l.remove(); // 如果没有吃到食物，移除蛇尾
    }
    int len = l.listLength();
    for (int i = 1; i <= len; i++)
    {
        k = l.get(i);
        mvaddch(k.getY(), k.getX(), k.getCh());
        refresh();
    }
}
int main()
{
    game g;
    g.launch(); // 启动游戏
    return 0;
}