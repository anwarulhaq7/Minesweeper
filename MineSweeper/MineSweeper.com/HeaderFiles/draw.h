#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <string>
#include <fstream>

class Square {
    sf::RectangleShape cell;
    sf::ConvexShape up, down;
    int size;
public:
    Square() {
        cell.setPosition(sf::Vector2f(0.0f, 0.0f));
        up.setPointCount(3);
        down.setPointCount(3);
        size = 32;
    }
    Square(int s) {
        size = s;
    }
    void setPosition(const sf::Vector2f& position) {

        //------------------------------------------------ Middle Square ------------------------------------

        cell.setPosition(position + sf::Vector2f(3.0f, 3.0f));
        cell.setSize(sf::Vector2f(size-7, size-7));
        cell.setFillColor(sf::Color(195, 195, 200));

        //---------------------------------- Making UP and down convex shapes to add shades to square 

        up.setPointCount(3);
        down.setPointCount(3);

        up.setPoint(0, sf::Vector2f(position + sf::Vector2f(0.f, size)));
        up.setPoint(1, sf::Vector2f(position + sf::Vector2f(0.f, 0.f)));
        up.setPoint(2, sf::Vector2f(position + sf::Vector2f(size, 0.f)));

        down.setPoint(0, sf::Vector2f(position + sf::Vector2f(0.f, size)));
        down.setPoint(1, sf::Vector2f(position + sf::Vector2f(size, size)));
        down.setPoint(2, sf::Vector2f(position + sf::Vector2f(size, 0.f)));

        up.setFillColor(sf::Color(255, 255, 255));
        down.setFillColor(sf::Color(90, 90, 90));
    }
    void draw(sf::RenderWindow& window) {
        window.draw(up);
        window.draw(down);
        window.draw(cell);
    }
};

class Flag {
    sf::RectangleShape b1, b2, p;
    sf::ConvexShape triangle;
public:
    Flag() {
        b1.setSize(sf::Vector2f(16, 3));
        b2.setSize(sf::Vector2f(10, 3));
        p.setSize(sf::Vector2f(3, 17));
        triangle.setPointCount(5);
    }
    void setPosition(const sf::Vector2f& position) {
        b1.setPosition(sf::Vector2f(10, 24) + position);
        b2.setPosition(sf::Vector2f(13, 21) + position);
        p.setPosition(sf::Vector2f(18, 4) + position);

        triangle.setPoint(0, sf::Vector2f(18, 5) + position);
        triangle.setPoint(1, sf::Vector2f(6, 5) + position);
        triangle.setPoint(2, sf::Vector2f(10, 10) + position);
        triangle.setPoint(3, sf::Vector2f(6, 17) + position);
        triangle.setPoint(4, sf::Vector2f(18, 17) + position);
    }
    void draw(sf::RenderWindow& window) {
        b1.setFillColor(sf::Color(0, 0, 0));
        b2.setFillColor(sf::Color(10, 10, 12));
        p.setFillColor(sf::Color(30, 20, 10));
        triangle.setFillColor(sf::Color(255, 10, 10));

        window.draw(b1);
        window.draw(b2);
        window.draw(p);
        window.draw(triangle);
    }
};

class Mine {
    sf::Texture imag;
    sf::Sprite pic;
public:
    Mine() {
        pic.setTexture(imag);
        pic.setTextureRect(sf::IntRect(0, 0, 1080,1150));
        pic.setScale(0.022,0.021);
        imag.setSmooth(true);
    }
    void setTexture(sf::Texture& tex) {
        imag = tex;
    }
    void setPosition(const sf::Vector2f& position) {
        pic.setPosition(position + sf::Vector2f(5, 5));

    }
    void draw(sf::RenderWindow& window) {
        window.draw(pic);
    }
};

void drawBorder(sf::RenderWindow& window, int mode) {
    int length=0, width=0, pos=0;
    switch (mode) {
    case 1:
        width = 312;
        length = 394;
        pos = 800;
        break;
    case 2:
        width = 536;
        length = 618;
        pos = 700;
        break;
    case 3:
        width = 984;
        length = 618;
        pos = 450;
        break;
    }
    sf::View view(sf::FloatRect(0, 0, width, length));
    window.setView(view);
    window.setSize(sf::Vector2u(width, length));
    window.setPosition(sf::Vector2i(pos, 250));

    sf::ConvexShape out_up, out_down, t_up, t_down;
    sf::RectangleShape mid_rect(sf::Vector2f(width - 8, length - 8));
    mid_rect.setPosition(sf::Vector2f(4.f, 4.f));
    mid_rect.setFillColor(sf::Color(195, 195, 200));

    //------------------------------ Adding Outer shades -------------------------

    out_up.setPointCount(3);
    out_down.setPointCount(3);

    out_up.setPoint(0, sf::Vector2f(sf::Vector2f(width, 0.f)));
    out_up.setPoint(1, sf::Vector2f(sf::Vector2f(0.f, 0.f)));
    out_up.setPoint(2, sf::Vector2f(sf::Vector2f(0.f, length)));

    out_down.setPoint(0, sf::Vector2f(sf::Vector2f(0.f, length)));
    out_down.setPoint(1, sf::Vector2f(sf::Vector2f(width, length)));
    out_down.setPoint(2, sf::Vector2f(sf::Vector2f(width, 0.f)));

    out_up.setFillColor(sf::Color(255, 255, 255));
    out_down.setFillColor(sf::Color(90, 90, 90));

    //------------------------------ Adding inner shades --------------------------

    t_up.setPointCount(3);
    t_down.setPointCount(3);

    t_up.setPoint(0, sf::Vector2f(sf::Vector2f(width - 8, 8.f)));
    t_up.setPoint(1, sf::Vector2f(sf::Vector2f(8.f, 8.f)));
    t_up.setPoint(2, sf::Vector2f(sf::Vector2f(8.f, 86.f)));

    t_down.setPoint(0, sf::Vector2f(sf::Vector2f(8.f, 86.f)));
    t_down.setPoint(1, sf::Vector2f(sf::Vector2f(width - 8, 86.f)));
    t_down.setPoint(2, sf::Vector2f(sf::Vector2f(width - 8, 8.f)));

    sf::RectangleShape r1, r2;
    r1.setSize(sf::Vector2f(4, 40));
    r2.setSize(sf::Vector2f(4, 40));

    r1.setPosition(sf::Vector2f(width - 11, 8));
    r2.setPosition(sf::Vector2f(11, 86));

    r1.rotate(90);
    r2.rotate(-90);

    r1.setFillColor(sf::Color(90, 90, 90));
    r2.setFillColor(sf::Color(255, 255, 255));

    t_up.setFillColor(sf::Color(90, 90, 90));
    t_down.setFillColor(sf::Color(255, 255, 255));

    window.draw(out_up);
    window.draw(out_down);
    window.draw(mid_rect);

    mid_rect.setPosition(sf::Vector2f(12.f, 12.f));
    mid_rect.setSize(sf::Vector2f(width - 24, 70));

    window.draw(t_up);
    window.draw(t_down);
    window.draw(r1);
    window.draw(r2);
    window.draw(mid_rect);

    t_up.setPoint(0, sf::Vector2f(sf::Vector2f(width - 8, 90.f)));
    t_up.setPoint(1, sf::Vector2f(sf::Vector2f(8.f, 90.f)));
    t_up.setPoint(2, sf::Vector2f(sf::Vector2f(8.f, length - 8)));

    t_down.setPoint(0, sf::Vector2f(sf::Vector2f(8.f, length - 8)));
    t_down.setPoint(1, sf::Vector2f(sf::Vector2f(width - 8, length - 8)));
    t_down.setPoint(2, sf::Vector2f(sf::Vector2f(width - 8, 90.f)));

    mid_rect.setPosition(sf::Vector2f(12.f, 94.f));
    mid_rect.setSize(sf::Vector2f(width - 24, length - 106));

    window.draw(t_up);
    window.draw(t_down);
    window.draw(mid_rect);
}

int drawMenu(sf::RenderWindow& window) {

    sf::Texture imag;
    imag.loadFromFile("Images/menu.jpg", sf::IntRect(0, 0, 480, 640));

    sf::Sprite sprite(imag);
    sprite.setScale(1.02, 1);
    imag.setSmooth(true);
    window.draw(sprite);
    sf::Font blood;
    blood.loadFromFile("Fonts/Static.ttf");

    sf::Text opt;

    opt.setFont(blood);
    opt.setStyle(sf::Text::Bold);
    opt.setStyle(sf::Text::Italic);
    opt.setCharacterSize(50);
    opt.setLetterSpacing(1.f);
    opt.setFillColor(sf::Color(255, 192, 0));
    opt.setOutlineThickness(1);
    opt.setOutlineColor(sf::Color(255, 255, 255));

    
    opt.setString("High Scores");
    opt.setPosition(sf::Vector2f(20, 450));
    window.draw(opt);
    opt.setString("Quit");
    opt.setPosition(sf::Vector2f(20, 530));
    window.draw(opt);
    opt.setString("Play Game");
    opt.setPosition(sf::Vector2f(20, 370));
    window.draw(opt);

    window.display();

    int x, y,mx=0,my=0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (x >= 25) {
                        if (y >= 380 && y <= 420 && x<=275) {
                            return 1;
                        }
                        if (y >= 460 && y <= 500 && x<=330) {
                            return 2;
                        }
                        if (y >= 540 && y <= 580 && x<=135) {
                            return 3;
                        }
                    }
                }
            }
        }   
    }
}

int drawEnd(sf::RenderWindow& window, int score) {
    window.setSize(sf::Vector2u(480, 640));
    sf::View view(sf::FloatRect(0, 0, 480,640));
    window.setView(view);

    sf::Texture imag;
    imag.loadFromFile("Images/menu.jpg", sf::IntRect(0, 0, 480, 640));

    sf::Sprite sprite(imag);
    sprite.setScale(1.02, 1);
    imag.setSmooth(true);
    window.draw(sprite);
    sf::Font blood;
    blood.loadFromFile("Fonts/Johnny Pistolas.otf");

    sf::Text text;
    text.setFont(blood);
    text.setCharacterSize(60);
    text.setString("Your Score: " + std::to_string(score));
    text.setFillColor(sf::Color(0,128,0));
    text.setPosition(sf::Vector2f(35, 210));
    text.rotate(27);
    text.setOutlineThickness(3);
    text.setOutlineColor(sf::Color(255,255,255));
    window.draw(text);

    sf::RectangleShape button;
    button.setSize(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color(255, 192, 0));
    button.setOutlineThickness(3);
    button.setOutlineColor(sf::Color(0,50,0));
    button.setPosition(sf::Vector2f(140, 450));
    window.draw(button);

    button.setSize(sf::Vector2f(120, 40));
    button.setPosition(sf::Vector2f(180, 550));
    window.draw(button);

    text.setString("Main Menu");
    text.setCharacterSize(50);
    text.setOutlineThickness(1);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(sf::Vector2f(160, 440));
    text.rotate(-27);
    window.draw(text);

    text.setString("Exit");
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(215, 540));
    window.draw(text);

    window.display();

    int x = 0, y = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (x >= 140 && x <= 340 && y>=450 && y<=500) {
                        return 1;
                    }
                    if (x >= 180 && x <= 300 && y >= 550 && y <= 590) {
                        return 0;
                    }
                }
            }
        }
    }
}

int drawLevel(sf::RenderWindow& window) {
    window.clear(sf::Color(28, 39, 64));
    sf::Font blood;
    blood.loadFromFile("Fonts/Johnny Pistolas.otf");

    sf::Text text;
    text.setFont(blood);
    text.setString("Select Difficulty");
    text.setCharacterSize(70);
    text.setLetterSpacing(2.f);
    text.setPosition(sf::Vector2f(35, 25));
    text.setFillColor(sf::Color(255, 190, 0));
    window.draw(text);

    sf::RectangleShape button;

    button.setSize(sf::Vector2f(300, 70));
    button.setFillColor(sf::Color(255, 192, 0));
    button.setOutlineThickness(5);
    button.setOutlineColor(sf::Color(0, 0, 0));
    button.setPosition(sf::Vector2f(90, 200));
    window.draw(button);
    button.setPosition(sf::Vector2f(90, 320));
    window.draw(button);
    button.setPosition(sf::Vector2f(90, 440));
    window.draw(button);

    //------------- Back button
    button.setSize(sf::Vector2f(120, 40));
    button.setPosition(sf::Vector2f(30, 580));
    button.setFillColor(sf::Color(0, 150, 0));
    button.setOutlineThickness(2);
    window.draw(button);

    blood.loadFromFile("Fonts/Stay and Shine.ttf");
    text.setFont(blood);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color(0, 0, 0));
    text.setCharacterSize(40);
    text.setFillColor(sf::Color(255, 255, 255));

    text.setString("Beginner");
    text.setPosition(sf::Vector2f(150, 210));

    window.draw(text);
    text.setString("Intermediate");
    text.setPosition(sf::Vector2f(120, 330));
    window.draw(text);
    text.setString("Advance");
    text.setPosition(sf::Vector2f(160, 450));
    window.draw(text);
    //------------- For Back Button
    text.setLetterSpacing(1.5f);
    text.setOutlineThickness(1);
    text.setCharacterSize(30);
    text.setString("<-Back");
    text.setPosition(sf::Vector2f(35, 580));
    window.draw(text);


    window.display();

    int x, y;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (x >= 90 && x <= 390) {
                        if (y >= 200 && y <= 270) {
                            return 1;
                        }
                        if (y >= 320 && y <= 390) {
                            return 2;
                        }
                        if (y >= 440 && y <= 510) {
                            return 3;
                        }
                    }
                    if (x >= 40 && x <= 160) {
                        if (y >= 580 && y <= 620)
                            return 10;
                    }
                }
            }
        }
    }
}

char* fileName(int lvl) {
    char* file = nullptr;
    switch (lvl) {
    case 1:
        file = new char[13];
        strcpy_s(file, 13, "beginner.txt");
        break;
    case 2:
        file = new char[17];
        strcpy_s(file, 17, "intermediate.txt");
        break;
    case 3:
        file = new char[12];
        strcpy_s(file, 12, "advance.txt");
        break;
    }
    return file;
}

//std::string takeInput(sf::RenderWindow& window, int input) {
//    window.setSize(sf::Vector2u(480, 640));
//    sf::View view(sf::FloatRect(0, 0, 480, 640));
//    window.setView(view);
//    window.clear(sf::Color(28, 39, 64));
//    
//    sf::Text text;
//    text.setCharacterSize(40);
//    text.setFillColor(sf::Color(255, 255, 255));
//
//    if (input == 0) {
//        text.setString("Sorry! You couldn't make it into top 5.");
//        text.setPosition(sf::Vector2f(20, 15));
//        window.draw(text);
//        text.setString("Better Luck Next Time!");
//        text.setPosition(40, 20);
//        window.draw(text);
//    }
//
//
//
//}

int showScores(sf::RenderWindow& window, int lvl) {
    window.clear(sf::Color(28, 39, 64));
    sf::Font blood;
    blood.loadFromFile("Fonts/Johnny Pistolas.otf");

    sf::Text text;
    text.setFont(blood);
    text.setString("Top Scorers");
    text.setCharacterSize(50);
    text.setLetterSpacing(1.5f);
    text.setPosition(sf::Vector2f(15, 15));
    text.setFillColor(sf::Color(255, 190, 0));
    window.draw(text);

    sf::RectangleShape button;

    button.setSize(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color(255, 192, 0));
    button.setOutlineThickness(4);
    button.setOutlineColor(sf::Color(0, 0, 0));

    blood.loadFromFile("Fonts/Stay and Shine.ttf");
    text.setFont(blood);

    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color(0, 0, 0));
    text.setCharacterSize(40);

    int scores[5];

    char* file=nullptr;
    file = fileName(lvl);

    std::ifstream get(file);
    for (int x = 0;x < 5;x++)
        get >> scores[x];

    int ys = 120;
    int xs = 30;
    for (int i = 0;i < 5;i++) {
        button.setPosition(sf::Vector2f(xs + 50, ys));
        window.draw(button);

        text.setFillColor(sf::Color(255, 192, 0));
        text.setString(std::to_string(i) + ".");
        text.setPosition(sf::Vector2f(xs, ys));
        window.draw(text);

        if (scores[i] != 99999) {
            text.setFillColor(sf::Color(255, 255, 255));
            text.setString(std::to_string(scores[i]));
            text.setPosition(sf::Vector2f(xs + 90, ys));
            window.draw(text);
        }
        ys += 90;
        xs += 40;
    }
    //----------------- Back Button
    button.setSize(sf::Vector2f(120, 40));
    button.setPosition(sf::Vector2f(30, 580));
    button.setFillColor(sf::Color(0, 150, 0));
    button.setOutlineThickness(2);
    window.draw(button);

    text.setFillColor(sf::Color(255, 255, 255));
    text.setCharacterSize(30);
    text.setString("<-Back");
    text.setPosition(sf::Vector2f(35, 580));
    window.draw(text);

    window.display();

    //--------------------------------------------
    int x, y;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (x >= 40 && x <= 160) {
                        if (y >= 580 && y <= 620)
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void updateScores(sf::RenderWindow& window, int lvl, int newScore) {
    char* file = nullptr;
    //std::string name;
    std::string names[5];
    bool input = 0;

    file = fileName(lvl);
    std::ifstream get(file);
    int arr[5];

    for (int i = 0;i < 5;i++) {
        get >> arr[i] >> names[i];
    }
    for (int i = 0;i < 5;i++) {
        if (arr[i] > newScore) {
            arr[4] = newScore;
            input = 1;
            break;
        }
    }

    //name = takeInput(window, input);

    for (int i = 0;i < 5;i++) {
        for (int j = 4;j > i;j--) {
            if (arr[j] < arr[j - 1])
                std::swap(arr[j], arr[j - 1]);
        }
    }
    
    std::ofstream temp;
    temp.open("temp.txt");
    for (int i = 0;i < 5;i++) {
        temp << arr[i] << std::endl;
    }
    temp.close();
    get.close();
    remove(file);
    rename("temp.txt", file);
}