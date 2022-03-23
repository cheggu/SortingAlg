#pragma once
#include "includes.h"
#include "Helpers.h"
#include <algorithm>
#include <windows.h> 

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Bubble Sort Visualized");

class Line {
public:
    sf::RectangleShape shape;
    int value; 

    Line(int height) {
        sf::Vector2f size;
        size.x = 1;
        size.y = height;

        value = height;

        shape.setRotation(180);
        shape.setSize(size);
        shape.setFillColor(sf::Color::White);
    }
};

void thing(int count) {
    srand(rand() % 999999999);

    double mult = 1;

    float dt;
    sf::Clock dt_clock;

    sf::Clock timer;

    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;

    sf::Sound sound;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }

    std::vector<sf::Drawable> drawableList = {};

    std::vector<Line> lineList = {};

    int i, j;

    for (int i = 0; i < 44100; i++) {  //44100
        //samples.push_back(sound::SineWave(i, 440, 0.9));
        samples.push_back(sound::SquareWave(i, 440, .1));
        //samples.push_back(sound::Noise(0.9));
    }

    buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);

    sound.setBuffer(buffer);

    sf::Text time;
    time.setFont(font);
    time.setString("Hello world");
    time.setCharacterSize(24); // in pixels, not points!
    time.setFillColor(sf::Color::White);
    time.setPosition(50, 25);

    //lord forgive me, for I have sinned.
restart:

    lineList.clear();
    drawableList.clear();

    //1880
    for (int i = 0; i < count; i++) {
        int foo = random(1, 1000);
        Line tempLine = *(new Line(foo));
        tempLine.value = foo;
        lineList.push_back(tempLine);
    }

    i = 1;
    j = 1;

    while (window.isOpen())
    {
        window.clear();

        dt = dt_clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit(0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                goto restart;
            }
        }
        //+1
        int lastX = 20;
        for (Line line : lineList) {
            line.shape.setPosition(lastX + 1, 1040);
            double add = ((1880 - count) / count);
            if (add < 1) add = 1.0;
            lastX += add;

            window.draw(line.shape);
        }

        int length = lineList.size();

        if (i <= length - 1) {
            bool swapped = false;
            for (int j = 1; j < length; j++) {
                if (lineList.at(j - 1).value > lineList.at(j).value) {
                    sf::RectangleShape tempShape = lineList.at(j - 1).shape;
                    int tempValue = lineList.at(j - 1).value;

                    lineList.at(j - 1).value = lineList.at(j).value;
                    lineList.at(j - 1).shape = lineList.at(j).shape;

                    lineList.at(j).value = tempValue;
                    lineList.at(j).shape = tempShape;

                    lineList.at(j - 1).shape.setFillColor(sf::Color::Red);
                    lineList.at(j).shape.setFillColor(sf::Color::White);

                    //cant get sound to work this fast
                    //sound.setPitch(float(lineList.at(j - 1).value / 1000.0));
                    //sound.play();
                    //std::iter_swap(lineList.begin() + j, lineList.begin() + j - 1);

                    swapped = true;
                }

                lineList.at(j).shape.setFillColor(sf::Color::White);
            }
        }
        else {
            for (Line& line : lineList) {
                line.shape.setFillColor(sf::Color::Green);
            }
        }
        i++;
        j++;

        for (Line& line : lineList) {
            if (i == length - 1) {
                line.shape.setFillColor(sf::Color::Green);
            }

            window.draw(line.shape);
        }

        time.setString("Size: " + std::to_string(lineList.size()) + "\nPress 'R' to Restart\nPress 'ESC' to Quit");
        window.draw(time);

        window.display();
    }
}

int main()
{
    window.setVisible(false);

    int count = 0;
    std::cout << "\nType -1 to quit!\nEnter the amount of elements you want to sort in the array (max 1880, min 1): ";
    std::cin >> count;
    std::cin.clear();
    while (count > 1880 || count == 0 || count < -1) {
        if (count == -1) {
            exit(0);
        }

        std::cout << "Invalid number, please try again (max 1880, min 1): ";
        std::cin >> count;
        std::cin.clear();
    }

    window.setVisible(true);

    thing(count);

    return 0;
}