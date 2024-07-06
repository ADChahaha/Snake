#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include "snake_game.h"



int main(int argc,char** argv)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);  
    nodelay(stdscr, TRUE); 
    curs_set(FALSE);
    int ch;
    //开具方向默认靠右
    char direction = RIGHT;
    //屏幕大小
    int height, width;
    getmaxyx(stdscr, height, width);
    snake_game snake(20, 50);
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ch = getch();
        if(ch != ERR)
        {
            switch(ch)
            {
                case 'w':
                case KEY_UP:
                    direction = UP;
                    break;
                case 's':
                case KEY_DOWN:
                    direction = DOWN;
                    break;
                case 'a':
                case KEY_LEFT:
                    direction = LEFT;
                    break;
                case 'd':
                case KEY_RIGHT:
                    direction = RIGHT;
                    break;
            }
            //改变蛇的方向
            snake.switch_direction(direction);
        }
        //清空缓冲区，防止等会动不了
        //flushinp();
        //每隔x秒进行一次蛇的移动操作(变长包含在内) 
        snake.move();
        //判断蛇是否死亡
        if(snake.is_alive())
        {
            //如果蛇未死亡，则重新绘制  
            snake.draw();
        }
        else
        {
            //如果蛇死亡，退出循环
            //显示你死了,分数什么的
            snake.draw_death();
            nodelay(stdscr, FALSE); // 禁用非阻塞输入
            getch();
            break;
        }           
    }  
    endwin();
    return 0;
}

