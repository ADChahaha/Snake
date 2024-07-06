#include <list>
#include <random>
#include <algorithm>
#include <ncurses.h>
#include "snake_game.h"

snake_game::coordinate snake_game::random_coordinate(std::pair<unsigned int,unsigned int> range_x, std::pair<unsigned int,unsigned int> range_y)
{
    //随机生成一个位置
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis_x(range_x.first, range_x.second);
    std::uniform_int_distribution<> dis_y(range_y.first, range_y.second);
    unsigned int x,y;
    do
    {
        x = dis_x(gen);
        y = dis_y(gen);
    } while (Snake.end() != std::find(Snake.begin(),Snake.end(),coordinate(x,y)));
    return coordinate(x,y);
} 

bool snake_game::generate_food()
{
    //重新生成食物
    food_coordinate = random_coordinate(std::pair<unsigned int,unsigned int>(2,col - 1),std::pair<unsigned int,unsigned int>(2,row - 1));
    return true;
}

void snake_game::move_snake()
{
    //移动位置(后一个变为前一个，前一个按照方向移动)
    coordinate head = get_front_coordinate();
    Snake.push_front(head);
    Snake.pop_back();
}

bool snake_game::is_bump_against_itself()
{
    //判断是否撞到自己(find(*begin(),begin()+1,end()))
    auto it = Snake.begin();
    it++;
    //找到了
    if(std::find(it, Snake.end(),*Snake.begin()) != Snake.end())
    {
        alive = false;
        return true;
    }
    return false;
}

bool snake_game::is_bump_against_wall()
{
    //判断是否撞到墙
    coordinate head = *Snake.begin();
    if(head.first == col || head.first == 1 || head.second == row || head.second == 1)
    {
        alive = false;
        return true;
    }
    return false;
}

void snake_game::get_food()
{
    //前方是食物，加长蛇
    coordinate head = get_front_coordinate();
    Snake.push_front(head);
}

snake_game::coordinate snake_game::get_front_coordinate()
{
    coordinate head = *Snake.begin();
    switch(direction)
    {
        case RIGHT:
            head.first += 1;
            break;
        case LEFT:
            head.first -= 1;
            break;
        case UP:
            head.second -= 1;
            break;
        case DOWN:
            head.second += 1;
            break;
    }
    return head;
}

bool snake_game::switch_direction(char dirc)
{
    if(dirc == LEFT && direction == RIGHT)
        return false;
    else if(dirc == RIGHT && direction == LEFT)
        return false;
    else if(dirc == UP && direction == DOWN)
    return false;
    else if(dirc == DOWN && direction == UP)
    return false;
    direction = dirc;
    return true;
}

bool snake_game::is_alive()
{
    return alive;
}

void snake_game::move()
{
    //进行一次蛇的移动(在移动过程中要判断是否死亡,撞墙和撞到自己)(还要判断是否吃掉了食物，吃掉了要加长蛇并且重新生成食物)
    //先判断前方位置是不是食物，如果是肯定不会撞墙，直接加长蛇   
    //如果不是，移动这个蛇，然后判断是否撞到墙和自己
    if(get_front_coordinate() == food_coordinate)
    {
        //吃到食物，加长蛇
        get_food();
        //分数+1
        score += 1;
        //重新生成一个食物
        generate_food();
    }
    else
    {
        move_snake();
        //判断是否撞到自己
        if(is_bump_against_itself())
        {
            alive = false;
        }
        //判断是否撞墙
        else if(is_bump_against_wall())
        {
            alive = false;
        }
    }
}
snake_game::snake_game(unsigned int urow,unsigned int ucol)
{
    //进行初始化
    row = urow;
    col = ucol;
    score = 0;
    direction = RIGHT;
    alive = true;
    //生成蛇
    //给人一点反应时间
    coordinate head = random_coordinate(std::pair<unsigned int,unsigned int>(1 + SNAKE_DEFAULT_LENGTH,col - 5),std::pair<unsigned int,unsigned int>(2,row - 1));
    Snake.push_front(head);
    for(int i = 0;i < SNAKE_DEFAULT_LENGTH - 1;++i)
    {
        head.first -= 1;
        Snake.push_back(head);
    }
    //生成食物
    generate_food();
}

//--------------------------------------------------------------
//还剩下draw和draw_death没写

void snake_game::draw_border()
{
    // 使用 ncurses 绘制边框
    for (int i = 1; i <= col; i++) {
        mvprintw(1, i, "#");           // 顶部边框
        mvprintw(row, i, "#");  // 底部边框
    }
    for (int i = 1; i <= row; i++) {
        mvprintw(i, 1, "#");           // 左侧边框
        mvprintw(i, col, "#");   // 右侧边框
    }
}

void snake_game::draw()                               
{
    clear();
    int cnt =  2;
    unsigned char ch = 4;
    //绘制蛇s
    for(auto coor:Snake) 
    {                          
        mvprintw(coor.second, coor.first, "%c",'o');  
    }
    //绘制背景(后画防止蛇的身体代替墙)
    draw_border();
    //绘制食物
    mvprintw(food_coordinate.second, food_coordinate.first, "%c",'$');  
    refresh();
}

void snake_game::draw_death()
{
    draw();
    mvprintw(row / 2, col / 2 - 6, "You dead. Your score is:  %u.",score);
    mvprintw(row / 2 + 2, col / 2 - 6, "Press any key to exit.");
    refresh();
}