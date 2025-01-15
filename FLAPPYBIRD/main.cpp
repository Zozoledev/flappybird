#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{

    
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Flappy Bird");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("flappybird.png"))
    {
        std::cerr << "Erreur lors du chargement de la texture !\n";
        return -1; 
        //utile que dans le cas où tu n'es pas sur que la texture genre si tu la charges indirectement ( par une classe par ex ) 
    }


    //BACKGROUND
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("map.jpeg");

    sf::Sprite background;
    background.setTexture(backgroundTexture);

    background.setScale((window.getSize().x / backgroundTexture.getSize().x)*1.5, window.getSize().y / backgroundTexture.getSize().y);



    //SPRITE FLAPPY
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(50.f, 50.f));


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
                    if(!(sprite.getPosition().y <= -40)){
                        for(int i = 0; i < 12; i++){
                        if(sprite.getPosition().y <= -40){
                            break;
                        }
                        auto monte = -8.f;
                        sprite.move(sf::Vector2f(0.f, monte));
                        window.clear(sf::Color::Black);
                        window.draw(background);
                        window.draw(sprite);
                        window.draw(pipe);
                        window.display();
                        monte = monte/1.23;
                        

                    }

                    
                    }
                    
                }
            }
            
        }
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (!(bounds.top + bounds.height >= window.getSize().y + 40)) //bounds.top + bounds.height -> le bounds.height est en trop car avec bounds.top représente la coordonée Y du coin supérieur gauche
        {
            sprite.move(sf::Vector2f(0.f, 5.f)); // si tu regardes bien tu te situe dans le window.pollEvent, donc ta "gravité" s'active que si y'a un event ( genre une touche ou un clique ) 
        }
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