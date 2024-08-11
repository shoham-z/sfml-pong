#include <SFML/Graphics.hpp>
#include <cstdlib> // For rand()
#include <cmath>   // For M_PI
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct vector
{
    float x, y;
};
void handle_ball();

// constants
const unsigned int height = 720u, width = 1280u;
const float block_width = 25.f, block_height = 120.f, ball_size = 20.f, ball_speed = 10.f;

// ball speed
double dir = (rand() % 121 - 60) * M_PI / 180.0 + M_PI * (rand() % 2);
float X_step = std::cos(dir);
float Y_step = std::sin(dir);
// actual ball movement per frame should be {X_step * ball_speed, Y_step * ball_speed}

// global vars (since i want to organize the code into functions, and it would be easier then passing arguments and returning them UNLESS I PASS REFERENCES AS ARGUMENTS)
vector player_position = {30.f, (float)height / 2.f - block_height / 2.f};
vector opponent_position = {(float)width - 30.f - block_width, (float)height / 2.f - block_height / 2.f};
vector ball_position = {(float)width / 2.f - ball_size, (float)height / 2.f - ball_size};
vector ball_direction;


// defining shapes
sf::CircleShape ball(ball_size);
sf::RectangleShape player(sf::Vector2f(block_width, block_height));
sf::RectangleShape opponent(sf::Vector2f(block_width, block_height));

int main()
{
    // create the window
    auto window = sf::RenderWindow{{width, height}, "Pong"};
    window.setFramerateLimit(60);
    
    ball_direction = {(float)std::cos(dir), (float)std::sin(dir)};

    // set colors and positions for the shapes
    ball.setPosition(ball_position.x, ball_position.y);
    ball.setFillColor(sf::Color(100, 250, 50));

    player.setPosition(player_position.x, player_position.y);
    player.setFillColor(sf::Color(255, 50, 50));

    opponent.setPosition(opponent_position.x, opponent_position.y);
    opponent.setFillColor(sf::Color(255, 50, 50));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        handle_ball();

        // handle ball movement
        // 1. move the ball in the direction set for it
        // 2. handle collision with the ceiling or floor
        // handle player movement
        // handle opponent(bot) movement

        // clear the window with black color
        window.clear();

        // draw everything here...
        window.draw(ball);
        window.draw(player);
        window.draw(opponent);

        // end the current frame
        window.display();
    }
}

void handle_ball()
{
    ball_position = {ball_position.x + ball_direction.x * ball_speed, ball_position.y + + ball_direction.y * ball_speed};
    std::cout<<ball_position.x << "  " << ball_position.y<<std::endl;


        ball.setPosition(ball_position.x, ball_position.y);

}
