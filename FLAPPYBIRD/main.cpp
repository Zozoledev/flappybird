#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{

    //WINDOW
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Flappy Bird");
    window.setFramerateLimit(60);

   


    //BACKGROUND
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("map.jpeg");
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale((window.getSize().x / backgroundTexture.getSize().x)*1.5, window.getSize().y / backgroundTexture.getSize().y);



    //SPRITE FLAPPY
    sf::Texture texture;
    texture.loadFromFile("flappybird.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(50.f, 50.f));
    auto isjump = false;
    auto cpttime = 0;



    //SPRITE PIPE
    sf::Texture pipeTexture;
    pipeTexture.loadFromFile("pipe.png");
    sf::Sprite pipe;
    pipe.setTexture(pipeTexture);
    pipe.setPosition(sf::Vector2f(window.getSize().x / 2.f, -10.f));
    pipe.setScale(2.f, window.getSize().y / pipeTexture.getSize().y * 1.5);


 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    isjump = true;
                    
                }
                    
                }
            }
            
        

        //SPRITE CALCUL
        sf::FloatRect spritebounds = sprite.getGlobalBounds();
        if(isjump){
            if(!(spritebounds.top <= -30)){
                if(cpttime < 30){
                    sprite.move(sf::Vector2f(0.f, -4.f));
                    cpttime++;

                }else{
                    isjump = false;
                    cpttime = 0;
                }
            }else{
                isjump = false;
                cpttime = 0;

            }
                
        }
        if(!(isjump)){
            if(!(spritebounds.top + spritebounds.height >= window.getSize().y)){
                sprite.move(sf::Vector2f(0.f, 7.f));

            }
                
        }

        


        //PIPE CALCUL
        sf::FloatRect boundsPipe = pipe.getGlobalBounds();
        if(boundsPipe.left <= 0){
            pipe.setPosition(sf::Vector2f(window.getSize().x / 2.f, -10.f));
        }

        pipe.move(sf::Vector2f(-3.f, 0.f));


        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(sprite);
        window.draw(pipe);



        window.display();
    }


        return 0;
    }

