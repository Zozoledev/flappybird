#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

int main()
{
    std::random_device rd; 
    std::mt19937 gen(rd());

    //WINDOW
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Flappy Bird");
    window.setFramerateLimit(60);

   


    //BACKGROUND
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("map.jpeg");
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale((window.getSize().x / backgroundTexture.getSize().x)*1.5, window.getSize().y / backgroundTexture.getSize().y);

    //BAckground play
    auto start = true;
    sf::Texture playbackground;
    playbackground.loadFromFile("arriereplanscene1.png");
    sf::Sprite backgroundstart;
    backgroundstart.setTexture(playbackground);
    
    //startbuuton

    sf::Texture starttexture;
    starttexture.loadFromFile("playbutton.png");
    sf::Sprite buttonstart;
    buttonstart.setTexture(starttexture);
    buttonstart.setPosition(sf::Vector2f(window.getSize().x / 2.f - 115.f, window.getSize().y / 2.f - 100.f));
    buttonstart.setScale(0.5, 0.5);


    //SPRITE FLAPPY
    sf::Texture texture;
    texture.loadFromFile("flappybird.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(50.f, 50.f));
    sprite.setScale(0.8, 0.8);
    auto isjump = false;
    auto cpttime = 0;



    //SPRITE PIPE TOP
    sf::Texture ToppipeTexture;
    ToppipeTexture.loadFromFile("toppipe.png");
    sf::Sprite toppipe;
    toppipe.setTexture(ToppipeTexture);
    toppipe.setPosition(sf::Vector2f(window.getSize().x, (window.getSize().y / - 3.f) ));
    toppipe.setScale(2.f, 8.f);

    //SPRITE PIPE BOTTOM;
    sf::Texture BottompipeTexture;
    BottompipeTexture.loadFromFile("bottompipe.png");
    sf::Sprite bottompipe;
    bottompipe.setTexture(BottompipeTexture);
    bottompipe.setPosition(sf::Vector2f(window.getSize().x, (window.getSize().y / 1.45)));
    bottompipe.setScale(2.f, 8.f);




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
            else{
                buttonispress = false;

                
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
        sf::FloatRect buttonstartbounds = buttonstart.getGlobalBounds();

        if(buttonplayagainbounds.contains(mouseWorldPosition) && buttonispress){
            gameoverbool = false;
            
        }
       

        if(buttonstartbounds.contains(mouseWorldPosition) && buttonispress){
            
            start = false;
            
        }
        


        //PIPE CALCUL
        sf::FloatRect boundsPipe = toppipe.getGlobalBounds();
        sf::FloatRect boundsbottom = bottompipe.getGlobalBounds();


        



        if(boundsPipe.left <= 0 || boundsbottom.left <= 0){
            std::uniform_real_distribution<> moveDis(-150.0, 150.0);
            auto movepipe = moveDis(gen);
            toppipe.setPosition(sf::Vector2f(window.getSize().x, (window.getSize().y / - 3.f) + movepipe * 1.0));
            bottompipe.setPosition(sf::Vector2f(window.getSize().x, window.getSize().y / 1.45 + movepipe * 1.0));

            
            
        }

        toppipe.move(sf::Vector2f(-6.f, 0.f));
        bottompipe.move(sf::Vector2f(-6.f, 0.f));


        //GAME OVER 
        if(spritebounds.intersects(boundsPipe) || spritebounds.intersects(boundsbottom)){
            gameoverbool = true;
        }



        if(start){
            window.clear(sf::Color::Black);
            window.draw(backgroundstart);
            window.draw(buttonstart);

        }
        else if(gameoverbool){
            window.clear(sf::Color::Black);
            window.draw(gameover);
            window.draw(buttonplayagain);
        }else{
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

