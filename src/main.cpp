#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <fstream>
#include "Cell.h"
#include "Utility.h"
#include "Button.h"
#include "Slider.h"

using namespace std ;
using namespace sf ;

#define E(i,j) ((j)+(N)*(i))
#define EMPTY_CELL 0,0,0

int main()
{
    int width = 400 ;
    int height = 400 ;
    float ratio = width / (float)height ;
    int N = 200 ;
    float dx = height / N ;
    RenderWindow window(VideoMode(width, height, 32), "Cellular automaton") ;
    //window.setFramerateLimit(2) ;
    int maxHealth = 100 ;
    int maxForce = 2000 ;
    float splitFactor = 2 ;
    float ageFactor = 1;
    float forceAgeFactor = 1 ;
    float heal = 1 ;
    float healForce = 10 ;
    int maxForceXP = 100 ;

    float colorFactor = 0.004;

    srand(time(NULL)) ;
    random_device r ;
    mt19937 gen(r());
    uniform_int_distribution<int> distrib(0, 2) ;
    uniform_int_distribution<int> distrib2(0, 1000) ;
    int r1, r2 ;

    int teamNumber = 2 ;
    vector<Cell> board ;

    for(int i(0) ; i < N * ratio ; i++)
    {
        for(int j(0) ; j < N ; j++)
        {
            if(pow(i - N / 2, 2) + pow(j - N / 2 - 60, 2) < 40)
                board.push_back(Cell(maxHealth, rand() % maxForce, 1)) ;
            else if(pow(i - N / 2, 2) + pow(j - N / 2 + 60, 2) < 40)
                board.push_back(Cell(maxHealth, rand() % maxForce, 2)) ;
            else
                board.push_back(Cell(EMPTY_CELL)) ;
        }
    }

    Image image ;
    image.create(width, height) ;
    Texture texture ;
    texture.loadFromImage(image) ;
    Sprite sprite ;
    sprite.setTexture(texture, true) ;

    vector<int> fighterNumber(teamNumber) ;
    int iter1 = 0 ;

    ofstream stats("stats.txt") ;
    Vector2f mousePos ;
    Event event ;

    while(window.isOpen())
    {
        //cout<<board[E(150,170)].getHealth()<<endl;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed || event.type == Event::KeyPressed)
                window.close();
        }

        //mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y) ;

        for(int i(1) ; i < (N - 1)*ratio ; i++)
        {
            for(int j(1) ; j < N - 1 ; j++)
            {
                if(board[E(i, j)].getTeam() != 0)
                {

                    r1 = distrib(gen) - 1 ;
                    r2 = distrib(gen) - 1 ;

                    if(board[E(i + r1, j + r2)].getTeam() == 0) // move phase
                    {
                        board[E(i + r1, j + r2)].setMaxHealth(board[E(i, j)].getMaxHealth()) ;
                        board[E(i + r1, j + r2)].setHealth(board[E(i, j)].getHealth() / splitFactor) ;
                        board[E(i + r1, j + r2)].setMaxForce(board[E(i, j)].getMaxForce()) ;
                        board[E(i + r1, j + r2)].setForce(board[E(i, j)].getForce() / splitFactor) ;
                        board[E(i + r1, j + r2)].setTeam(board[E(i, j)].getTeam()) ;
                        //board[E(i,j)] = board[E(i+r1,j+r2)] ;
                    }
                    else if(board[E(i + r1, j + r2)].getTeam() != 0 && board[E(i + r1, j + r2)].getTeam() != board[E(i, j)].getTeam()) // fight phase
                    {
                        board[E(i, j)].setHealth( board[E(i, j)].getHealth() - board[E(i + r1, j + r2)].getForce() ) ;
                        board[E(i + r1, j + r2)].setHealth( board[E(i + r1, j + r2)].getHealth() - board[E(i, j)].getForce() ) ;
                        board[E(i, j)].setMaxForce(board[E(i, j)].getMaxForce() + maxForceXP) ;
                        board[E(i + r1, j + r2)].setMaxForce(board[E(i + r1, j + r2)].getMaxForce() + maxForceXP) ;
                    }
                    else if(board[E(i + r1, j + r2)].getTeam() == board[E(i, j)].getTeam()) // heal phase
                    {
                        board[E(i + r1, j + r2)].setHealth( board[E(i + r1, j + r2)].getHealth() + heal ) ;

                        board[E(i + r1, j + r2)].setForce(board[E(i + r1, j + r2)].getForce() + healForce) ;
                    }

                    board[E(i, j)].setHealth(board[E(i, j)].getHealth() / ageFactor) ;
                    board[E(i, j)].setForce(board[E(i, j)].getForce() / forceAgeFactor) ;

                    if(board[E(i, j)].getHealth() == 0)
                        board[E(i, j)] = Cell(EMPTY_CELL) ;
                }
            }
        }

        if(iter1 == 100)
        {
            for(int k(0) ; k < teamNumber ; k++)
                fighterNumber[k] = 0 ;

            for(int i(1) ; i < N - 1 ; i++)
            {
                for(int j(1) ; j < N - 1 ; j++)
                {
                    for(int k(0) ; k < teamNumber ; k++)
                        if(board[E(i, j)].getTeam() == k + 1)
                            fighterNumber[k]++ ;
                }
            }

            iter1 = 0 ;
            cout << fighterNumber[0] << " ; " << fighterNumber[1] << endl;
            //stats << warrior1<<" ; "<<warrior2<<" ; "<<warrior1+warrior2<<endl;
        }

        iter1++ ;

        image.create(width, height) ;

        for(int i(0) ; i < N * ratio ; i++)
        {
            for(int j(0) ; j < N ; j++)
            {
                for(int k(0) ; k < dx ; k++)
                {
                    for(int n(0) ; n < dx ; n++)
                    {
                        if(board[E(i, j)].getTeam() == 1)
                        {
                            image.setPixel(i * dx + k, j * dx + n, Color(255, (board[E(i, j)].getHealth() / colorFactor / (float)maxHealth), 0)) ;
                            //image.setPixel(i*dx+k,j*dx+n,Color((board[E(i,j)].getForce()/colorFactor/(float)maxForce),0,0)) ;
                        }
                        else if(board[E(i, j)].getTeam() == 2)
                        {
                            image.setPixel(i * dx + k, j * dx + n, Color(0, board[E(i, j)].getHealth() / colorFactor / (float)maxHealth, 0)) ;
                            //image.setPixel(i*dx+k,j*dx+n,Color(0,board[E(i,j)].getForce()/colorFactor/(float)maxForce,0)) ;
                        }
                    }
                }
            }
        }

        texture.update(image) ;
        sprite.setTexture(texture, true) ;
        window.clear() ;
        window.draw(sprite) ;
        window.display() ;

    }
}
