#include <SFML/Graphics.hpp>

int main()
{
    const unsigned int height = 720u, width = 1280u;
    const float block_width = 25.f, block_height = 120.f, ball_size = 20.f;
    // create the window
    auto window = sf::RenderWindow{ { width, height }, "Pong" };
    window.setFramerateLimit(60);


    // define all shapes here
    sf::CircleShape ball(ball_size);
    // set the circle color to green
    ball.setFillColor(sf::Color(100, 250, 50));
    ball.setPosition((float)width/2.f - ball_size, (float)height/2.f - ball_size);

    // define a 120x50 rectangle
    sf::RectangleShape player(sf::Vector2f(block_width, block_height));

    player.setPosition(30.f, (float)height/2.f - block_height/2.f);
    player.setFillColor(sf::Color(255, 50, 50));


    sf::RectangleShape opponent(sf::Vector2f(block_width, block_height));

    opponent.setPosition((float)width - 30.f - block_width, (float)height/2.f - block_height/2.f);
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
