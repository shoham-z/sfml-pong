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
void start_game();

// constants
const unsigned int screen_height = 720u, screen_width = 1280u;
const float block_width = 25.f, block_height = 120.f, ball_size = 20.f, ball_speed = 10.f;

// ball direction


// global vars (since i want to organize the code into functions, and it would be easier then passing arguments and returning them UNLESS I PASS REFERENCES AS ARGUMENTS)
unsigned int player_wins = 0, bot_wins = 0;
vector player_position;
vector opponent_position;
vector ball_position;
vector ball_direction;
double ball_dir;

// defining shapes
sf::CircleShape ball(ball_size);
sf::RectangleShape player(sf::Vector2f(block_width, block_height));
sf::RectangleShape opponent(sf::Vector2f(block_width, block_height));

int main()
{
    // create the window
    auto window = sf::RenderWindow{{screen_width, screen_height}, "Pong"};
    window.setFramerateLimit(60);

    start_game();

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

void start_game(){
    // reset everythings that is needed for a new round of the game
    player_position = {30.f, (float)screen_height / 2.f - block_height / 2.f};
    opponent_position = {(float)screen_width - 30.f - block_width, (float)screen_height / 2.f - block_height / 2.f};
    ball_position = {(float)screen_width / 2.f - ball_size, (float)screen_height / 2.f - ball_size};
    ball_dir = (rand() % 121 - 60) * M_PI / 180.0 + M_PI * (rand() % 2);
    ball_direction = {(float)std::cos(ball_dir), (float)std::sin(ball_dir)};
}

void handle_ball()
{

    // add collision logic

    // first check if the ball hit the bottom or top borders
    if (ball_position.y < 0 || ball_position.y + ball_size * 2 > screen_height - 1)
    {
        std::cout << "ball hit the bottom or top borders" << std::endl;
        ball_direction.y *= -1;
    }
    // else check if the ball reached the right or left borders to restart the game

    else if (ball_position.x - ball_size < 1 || ball_position.x + ball_size > screen_width)
    {
        std::cout << "someone won" << std::endl;
        // restart game
        (ball_position.x - ball_size < 1) ? bot_wins += 1 : player_wins += 1;
        start_game();
    }
    // else check if the ball collided with the player block
    else if (ball_position.x - ball_size - player_position.x - block_width < 0.5 &&
             ball_position.y - player_position.y < block_height / 2 + ball_size / 2 &&
             ball_position.y - player_position.y > -block_height / 2 - ball_size / 2)
    {
        std::cout << "in player" << std::endl;
        ball_direction = {ball_position.x - (player_position.x + block_width / 2) , ball_position.y - player_position.y};
    }
    // else check if the ball collided with the bot block
    else if (opponent_position.x - ball_position.x - ball_size < 0.5 &&
             ball_position.y - opponent_position.y < block_height + ball_size &&
             ball_position.y - opponent_position.y > -ball_size)
    {
        std::cout << "in opponent" << std::endl;
        ball_direction = {(opponent_position.x + block_width / 2) - ball_position.x , (opponent_position.y + block_height / 2) - ball_position.y};
    }

    ball_position = {ball_position.x + ball_direction.x * ball_speed, ball_position.y + ball_direction.y * ball_speed};
    ball.setPosition(ball_position.x, ball_position.y);
}
