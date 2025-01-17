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
    sprite.setScale(0.5, 0.5);
    auto isjump = false;
    auto cpttime = 0;



    //SPRITE PIPE TOP
    sf::Texture ToppipeTexture;
    ToppipeTexture.loadFromFile("toppipe.png");
    sf::Sprite toppipe;
    toppipe.setTexture(ToppipeTexture);
    toppipe.setPosition(sf::Vector2f(window.getSize().x, -10.f));
    toppipe.setScale(2.f, (window.getSize().y / ToppipeTexture.getSize().y )/2.5);

    //SPRITE PIPE BOTTOM;
    sf::Texture BottompipeTexture;
    BottompipeTexture.loadFromFile("bottompipe.png");
    sf::Sprite bottompipe;
    bottompipe.setTexture(BottompipeTexture);
    bottompipe.setPosition(sf::Vector2f(window.getSize().x, window.getSize().y / 1.45));
    bottompipe.setScale(2.f, (window.getSize().y / ToppipeTexture.getSize().y )/2.5);




    //FONTS 
    auto gameoverbool = false;
    sf::Font font;
    font.loadFromFile("BPdotsUnicase.otf");
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setString("GAME OVER !");
    gameover.setFillColor(sf::Color::White);
    gameover.setStyle(sf::Text::Bold);
    gameover.setPosition(sf::Vector2f(window.getSize().x / 3.f + 40, window.getSize().y / 3.f));
    

    //BUTTON PLYA AGAIN
    auto buttonispress = false;
    sf::Texture buttontexture;
    buttontexture.loadFromFile("playagain.png");
    sf::Sprite buttonplayagain;
    buttonplayagain.setTexture(buttontexture);
    buttonplayagain.setPosition(sf::Vector2f(window.getSize().x / 3.f + 40, window.getSize().y / 3.f + 40));
    buttonplayagain.setScale(1.5, 1.5);

     
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    isjump = true;
                    
                }
                    
                }
            }if(event.type == sf::Event::MouseButtonPressed){
                buttonispress = true;

            }

            
            
        

        //SPRITE CALCUL
        sf::FloatRect spritebounds = sprite.getGlobalBounds();
        if(isjump){
            if(!(spritebounds.top <= 0)){
                if(cpttime < 10){
                    sprite.move(sf::Vector2f(0.f, -10.f));
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
        

        //MOUSE POSITION 
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);
        sf::FloatRect buttonplayagainbounds = buttonplayagain.getGlobalBounds();
        if(buttonplayagainbounds.contains(mouseWorldPosition) && buttonispress){
            gameoverbool = false;
            
        }
        buttonispress = false;


        //PIPE CALCUL
        sf::FloatRect boundsPipe = toppipe.getGlobalBounds();
        sf::FloatRect boundsbottom = bottompipe.getGlobalBounds();
        if(boundsPipe.left <= 0 || boundsbottom.left <= 0){
            toppipe.setPosition(sf::Vector2f(window.getSize().x, -10.f));
            bottompipe.setPosition(sf::Vector2f(window.getSize().x, window.getSize().y / 1.45));
        }

        toppipe.move(sf::Vector2f(-3.f, 0.f));
        bottompipe.move(sf::Vector2f(-3.f, 0.f));


        //GAME OVER 
        if(spritebounds.intersects(boundsPipe) || spritebounds.intersects(boundsbottom)){
            gameoverbool = true;
        }




        if(gameoverbool){
            window.clear(sf::Color::Black);
            window.draw(gameover);
            window.draw(buttonplayagain);
        }
        
        if(!gameoverbool){
            window.clear(sf::Color::Black);
            window.draw(background);
            window.draw(sprite);
            window.draw(toppipe);
            window.draw(bottompipe);

        }
        
        



        window.display();
    }


        return 0;
    }

