#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Random.h"
using namespace std;

int checkMouseClick(vector<Tile>& board, sf::Vector2i mLocalPos, int cols);
vector<Tile> newBoard(int tilecount, int mines, int rows, int cols);
vector<Tile> loadTest(string filename);

int main()
{   
    //Main game variables
    fstream file("../../boards/config.cfg");
    int rows, cols, mines;
    file >> rows;
    file >> cols;
    file >> mines;
    int windowHeight = 88 + (rows * 32);
    int windowWidth = cols * 32;
    int tilecount = rows * cols;
    int flags = 0;
    

    //Loading all needed files
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    vector<Tile> board = newBoard(tilecount, mines, rows, cols);
    int hiddenval = 0;
    bool check = true;
    int gamestate = 0;
    int resetxmin = 0;
    int resetxmax = 0;
    int resetymin = 0;
    int resetymax = 0;

    int debugxmin = 0;
    int debugxmax = 0;
    int test1xmin = 0;
    int test1xmax = 0;
    int test2xmin = 0;
    int test2xmax = 0;
    int test3xmin = 0;
    int test3xmax = 0;

    //MAIN game loop
    while (window.isOpen())
    {
        // check all the window's events since the last iteration of the loop
        sf::Event event;
        sf::Vector2i mLocalPos;

        while (window.pollEvent(event))
        {
            //action for each different event
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                mLocalPos = sf::Mouse::getPosition(window);
                hiddenval = checkMouseClick(board, mLocalPos, cols);
                if ((gamestate == 0 || gamestate == 2) && hiddenval != -1) {
                    if (board[hiddenval].flag == 0) {
                        board[hiddenval].hidden = false;
                    }
                }
                //Check if a button was pressed
                if (mLocalPos.x < resetxmax && mLocalPos.x > resetxmin && mLocalPos.y < resetymax && mLocalPos.y > resetymin) {
                    //Reset the game to a random board
                    board = newBoard(tilecount, mines, rows, cols);
                    check = true;
                    gamestate = 0;
                }
                if (mLocalPos.x < debugxmax && mLocalPos.x > debugxmin && mLocalPos.y < resetymax && mLocalPos.y > resetymin) {
                    cout << "debug" << endl;
                    if (gamestate == 2) {
                        gamestate = 0;
                    }
                    else if (gamestate == 0) {
                        gamestate = 2;
                    }
                }
                if (mLocalPos.x < test1xmax && mLocalPos.x > test1xmin && mLocalPos.y < resetymax && mLocalPos.y > resetymin) {
                    cout << "test1" << endl;
                    board = loadTest("testboard1.brd");
                    check = true;
                    gamestate = 0;
                }
                if (mLocalPos.x < test2xmax && mLocalPos.x > test2xmin && mLocalPos.y < resetymax && mLocalPos.y > resetymin) {
                    cout << "test2" << endl;
                    board = loadTest("testboard2.brd");
                    check = true;
                    gamestate = 0;
                }
                if (mLocalPos.x < test3xmax && mLocalPos.x > test3xmin && mLocalPos.y < resetymax && mLocalPos.y > resetymin) {
                    cout << "test3" << endl;
                    board = loadTest("testboard3.brd");
                    check = true;
                    gamestate = 0;
                }
            }
            else if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                window.close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (gamestate == 0) {
                    mLocalPos = sf::Mouse::getPosition(window);
                    int val = checkMouseClick(board, mLocalPos, cols);
                    if (board[val].flag == 0) {
                        board[val].flag = 1;
                        flags++;
                    }
                    else {
                        board[val].flag = 0;
                        flags--;
                    }
                }
            }
        }

        window.clear(sf::Color(255, 255, 255, 255));

        //Reload sprites to fix positioning
        sf::Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
        sf::Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));
        sf::Sprite face_happy(TextureManager::GetTexture("face_happy"));
        sf::Sprite mine(TextureManager::GetTexture("mine"));
        sf::Sprite face_lose(TextureManager::GetTexture("face_lose"));
        sf::Sprite flag(TextureManager::GetTexture("flag"));
        sf::Sprite one(TextureManager::GetTexture("number_1"));
        sf::Sprite two(TextureManager::GetTexture("number_2"));
        sf::Sprite three(TextureManager::GetTexture("number_3"));
        sf::Sprite four(TextureManager::GetTexture("number_4"));
        sf::Sprite five(TextureManager::GetTexture("number_5"));
        sf::Sprite six(TextureManager::GetTexture("number_6"));
        sf::Sprite seven(TextureManager::GetTexture("number_7"));
        sf::Sprite eight(TextureManager::GetTexture("number_8"));
        sf::Sprite face_win(TextureManager::GetTexture("face_win"));
        sf::Sprite test_1(TextureManager::GetTexture("test_1"));
        sf::Sprite test_2(TextureManager::GetTexture("test_2"));
        sf::Sprite test_3(TextureManager::GetTexture("test_3"));
        sf::Sprite debug(TextureManager::GetTexture("debug"));

        face_happy.scale(0.5, 0.5);
        face_lose.scale(0.5, 0.5);
        face_win.scale(0.5, 0.5);
        test_1.scale(0.5, 0.5);
        test_2.scale(0.5, 0.5);
        test_3.scale(0.5, 0.5);
        debug.scale(0.5, 0.5);

        int w = face_happy.getTexture()->getSize().x;
        int count = 0;
        int width = tile_hidden.getTexture()->getSize().x;
        int height = tile_hidden.getTexture()->getSize().y;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[count].hidden) {
                    window.draw(tile_hidden);
                    if (board[count].flag == 1) {
                        window.draw(flag);
                    }
                    if ((gamestate == 1 || gamestate == 2) && board[count].mine == 1) {
                        window.draw(mine);
                    }
                }
                else {
                    window.draw(tile_revealed);
                    if (board[count].mine == 1) {
                        gamestate = 1;
                        window.draw(mine);
                    }
                    else {
                        int size = board[count].neighbors.size();
                        int nmine = 0;

                        for (int k = 0; k < size; k++) {
                            if (board[count].neighbors[k]->mine == 1) {
                                nmine++;
                            }
                        }
                        if (nmine == 0) {
                            //Reveal the tiles around you
                            for (int k = 0; k < size; k++) {
                                if (board[count].neighbors[k]->flag != 1) {
                                    board[count].neighbors[k]->hidden = false;
                                }
                            }
                        }
                        else if (nmine == 1) {
                            window.draw(one);
                        }
                        else if (nmine == 2) {
                            window.draw(two);
                        }
                        else if (nmine == 3) {
                            window.draw(three);
                        }
                        else if (nmine == 4) {
                            window.draw(four);
                        }
                        else if (nmine == 5) {
                            window.draw(five);
                        }
                        else if (nmine == 6) {
                            window.draw(six);
                        }
                        else if (nmine == 7) {
                            window.draw(seven);
                        }
                        else if (nmine == 8) {
                            window.draw(eight);
                        }
                    }
                }

                //Positioning sprites correctly
                flag.move(width, 0);
                mine.move(width, 0);
                tile_revealed.move(width, 0);
                tile_hidden.move(width, 0);
                one.move(width, 0);
                two.move(width, 0);
                three.move(width, 0);
                four.move(width, 0);
                five.move(width, 0);
                six.move(width, 0);
                seven.move(width, 0);
                eight.move(width, 0);

                //Board attributes getting saved
                sf::Vector2f fpos = tile_hidden.getPosition();
                sf::Vector2i ipos = sf::Vector2i::Vector2(fpos.x, fpos.y);
                board[count].width = width;
                board[count].height = height;
                board[count].pos = ipos;
                board[count].x = j;
                board[count].y = i;
                count++;
            }
            tile_hidden.move(-width * cols, height);
            tile_revealed.move(-width * cols, height);
            mine.move(-width * cols, height);
            flag.move(-width * cols, height);
            one.move(-width * cols, height);
            two.move(-width * cols, height);
            three.move(-width * cols, height);
            four.move(-width * cols, height);
            five.move(-width * cols, height);
            six.move(-width * cols, height);
            seven.move(-width * cols, height);
            eight.move(-width * cols, height);
        }
        
        //Draw buttons onto screen
        sf::Vector2f happypos = sf::Vector2f::Vector2(0, 0);
        bool checkwin = true;
        if (gamestate == 0 || gamestate == 2) {
            face_happy.move(sf::Vector2f::Vector2((windowWidth / 2) - w / 2, windowHeight - 88));
            window.draw(face_happy);
            happypos = face_happy.getPosition();
            for (int i = 0; i < board.size(); i++) {
                if (board[i].hidden == true) {
                    if (board[i].mine == 0) {
                        checkwin = false;
                        break;
                    }
                }
            }
            if (checkwin) {
                gamestate = 1;
            }
        }
        else if (gamestate == 1) {
            if (checkwin) {
                face_win.move(sf::Vector2f::Vector2((windowWidth / 2) - w / 2, windowHeight - 88));
                window.draw(face_win);
                happypos = face_win.getPosition();
            }
            else {
                face_lose.move(sf::Vector2f::Vector2((windowWidth / 2) - w / 2, windowHeight - 88));
                window.draw(face_lose);
                happypos = face_lose.getPosition();
            }
        }

        resetxmin = happypos.x;
        resetymin = happypos.y;
        int width_ = test_1.getTexture()->getSize().x/2;
        int height_ = test_1.getTexture()->getSize().y/2;
        resetxmax = resetxmin + width_;
        resetymax = resetymin + height_; 
        debugxmin = resetxmin + width_ * 2;
        debugxmax = resetxmin + width_ * 3;
        test1xmin = debugxmax+1;
        test1xmax = debugxmax + width_;
        test2xmin = test1xmax+1;
        test2xmax = test1xmax + width_;
        test3xmin = test2xmax + 1;
        test3xmax = test2xmax + width_;
        happypos.x = happypos.x + 2 * width_;
        debug.setPosition(happypos);
        window.draw(debug);
        happypos.x = happypos.x + width_;
        test_1.setPosition(happypos);
        window.draw(test_1);
        happypos.x = happypos.x + width_;
        test_2.setPosition(happypos);
        window.draw(test_2);
        happypos.x = happypos.x + width_;
        test_3.setPosition(happypos);
        window.draw(test_3);


        window.display();

        if (check) {
            //Get all tile neighbors stored
            for (int i = 0; i < tilecount; i++) {
                //Middle right tile
                if (board[i].x != cols - 1) {
                    board[i].neighbors.push_back(&board[i + 1]);
                }
                //Middle left tile
                if (board[i].x != 0) {
                    board[i].neighbors.push_back(&board[i - 1]);
                }
                //top middle tile
                if (board[i].y != 0) {
                    board[i].neighbors.push_back(&board[i - cols]);
                }
                //bottom middle tile
                if (board[i].y != rows - 1) {
                    board[i].neighbors.push_back(&board[i + cols]);
                }
                //top right tile
                if (board[i].y != 0 && board[i].x != cols - 1) {
                    board[i].neighbors.push_back(&board[i - (cols - 1)]);
                }
                //bottom right tile
                if (board[i].y != rows - 1 && board[i].x != cols - 1) {
                    board[i].neighbors.push_back(&board[i + (cols + 1)]);
                }
                //bottom left tile
                if (board[i].y != rows - 1 && board[i].x != 0) {
                    board[i].neighbors.push_back(&board[i + (cols - 1)]);
                }
                //top left tile
                if (board[i].y != 0 && board[i].x != 0) {
                    board[i].neighbors.push_back(&board[i - (cols + 1)]);
                }
            }
            check = false;
        }
    }
    return 0;
}

//Checks if the mouse click has a tile underneath it and returns the index of the tile in the board vector if so
int checkMouseClick(vector<Tile>& board, sf::Vector2i mLocalPos, int cols) {
    int xmin = 0;
    int ymin = 0;
    int xmax = 32;
    int ymax = 32;
    int count = 0;
    for (int i = 0; i < board.size(); i++) {
        if (mLocalPos.x >= xmin && mLocalPos.x <= xmax && mLocalPos.y >= ymin && mLocalPos.y <= ymax) {
            return i;
        }
        else {
            xmin += 32;
            xmax += 32;
            if (count == cols-1) {
                ymin += 32;
                ymax += 32;
                xmin = 0;
                xmax = 32;
                count = 0;
            }
            else {
                count++;
            }
        }
    }
    return -1;
}

//Creates new random board
vector<Tile> newBoard(int tilecount, int mines, int rows, int cols) {
    vector<Tile> board;
    //Creating the correct amount of tiles for the board
    for (int i = 0; i < tilecount; i++) {
        Tile temp;
        board.push_back(temp);
    }

    //Ranomdize mines
    int minecount = 0;
    while (minecount < mines) {
        int rand = Random::Int(0, board.size() - 1);
        if (board[rand].mine == 0) {
            board[rand].mine = 1;
            minecount++;
        }
    }

    return board;
}

//Load the test boards
vector<Tile> loadTest(string filename) {
    filename = "../../boards/" + filename;
    ifstream file(filename);
    vector<Tile> board;
    vector<string> lines;
    string val;
    while (file >> val) {
        lines.push_back(val);
    }
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            Tile temp;
            char ind = lines[i].at(j);
            if (ind == '1') {
                temp.mine = 1;
            }
            board.push_back(temp);
        }
    }

    return board;
}