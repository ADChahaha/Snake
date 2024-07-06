#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#define RIGHT 'd'
#define LEFT 'a'
#define UP 'w'
#define DOWN 's'
#define SNAKE_DEFAULT_LENGTH 5

#include <list>
class snake_game
{
    using coordinate = std::pair<unsigned int,unsigned int>;
private:
    //图的大小
    unsigned int row, col;//图为1-row，1-col的大小，1和row和col为墙壁
    //蛇(list)
    std::list<coordinate> Snake; 
    //蛇的当前方向
    char direction;
    //蛇是否存活(变量)
    bool alive;
    //食物的当前位置
    coordinate food_coordinate;
    //分数
    unsigned int score;
//-----------------------------------------------------------
    //函数部分
    //随机生成一个位置()
    coordinate random_coordinate(std::pair<unsigned int,unsigned int> range_x, std::pair<unsigned int,unsigned int> range_y);
    //重新生成食物
    bool generate_food();
    //移动位置(后一个变为前一个，前一个按照方向移动)
    void move_snake();
    //判断是否撞到自己(find(*begin(),begin()+1,end()))
    bool is_bump_against_itself();
    //判断是否撞到墙
    bool is_bump_against_wall();
    //前方是食物，加长蛇
    void get_food();
    //前方位置
    coordinate get_front_coordinate();
    //画边框
    void draw_border();
public:
    //初始化蛇的位置和第一个食物的位置和地图大小(构造函数)
    snake_game(unsigned int urow,unsigned int ucol);
    //切换蛇的方向
    bool switch_direction(char dirc);
    //绘制蛇与地图(画面)
    void draw();
    //蛇是否存活(函数)
    bool is_alive();  
    //进行一次蛇的移动(借口)(在移动过程中要判断是否死亡,撞墙和撞到自己)(还要判断是否吃掉了食物，吃掉了要加长蛇并且重新生成食物)
    //先判断前方位置是不是食物，如果是肯定不会撞墙，直接加长蛇   
    //如果不是，移动这个蛇，然后判断是否撞到墙和自己
    void move();
    //分数(list.size())
    unsigned int get_score();
    //显示死亡画面
    void draw_death();
};


#endif