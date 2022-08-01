
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//


/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
*/
#include <SFML/Graphics.hpp>
#include <time.h>
#include "ResourcePath.hpp"
using namespace sf;

const int M=20;
const int N=20;

int field[M][N]={0};

struct Point
{int x,y;}a[4],b[4];

int figures[7][4]=
{
    1,3,5,7,
    2,4,5,7,
    3,4,5,6,
    3,4,5,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};
bool check()
{
    for(int i=0;i<4;i++)
        if(a[i].x<0||a[i].x>=N||a[i].y>=M)
            return 0;
        else if(field[a[i].y][a[i].x])
            return 0;
    return 1;
}

int main()
{ srand(time(0));
   RenderWindow window(VideoMode(320, 480), "Welcome");
    Texture t;
    Texture t2,t3;
    t2.loadFromFile(resourcePath()+"bg.jpeg");
    t.loadFromFile(resourcePath()+"spri.png");
    
    Sprite s(t),background(t2);
    s.setTextureRect(IntRect(0,0,18,18));
    
    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3;
    Clock clock;
    
    
   while(window.isOpen())
   {   float time=clock.getElapsedTime().asSeconds();
       clock.restart();
       timer+=time;
       
       Event e;
       while(window.pollEvent(e))
       {
           if(e.type == Event::Closed)
           window.close();
           if(e.type == Event::KeyPressed)
           { if(e.key.code==Keyboard::Up)
                   rotate=true;
               else if(e.key.code==Keyboard::Left)
                   dx=-1;
               else if (e.key.code==Keyboard::Right)
                   dx=+1;
           }
       }
       if(Keyboard::isKeyPressed(Keyboard::Down))
           delay=0.05;
       
       for(int i=0;i<4;i++)
       {
           b[i]=a[i];
           a[i].x+=dx;
           
       }
       
       if(!check())
           for(int i=0;i<4;i++)
           {
               a[i]=b[i];
           }
           
       if(rotate)
       {
           Point p=a[1];
           for(int i=0;i<4;i++)
           {
               int x=a[i].y-p.y;
               int y=a[i].x-p.x;
               a[i].x=p.x-x;
               a[i].y=p.y+y;
               
           }
           if (!check())
               for (int i=0;i<4;i++)
                   a[i]=b[i];
       }
       
       
       if(timer>delay)
       { for(int i=0;i<4;i++)
       {
           b[i]=a[i];
            a[i].y+=1;
       }
           
           if(!check())
           {
               for(int i=0;i<4;i++)
                   {
                       field[b[i].y][b[i].x]=colorNum;
                       
                   }
               
               colorNum=1+rand()%7;
               int n=rand()%7;
               for(int i=0;i<4;i++)
               {
                   a[i].x=figures[n][i]%2;
                   a[i].y=figures[n][i]/2;
               }

           }
         timer=0;
           
       }
       
      /* int n=3;
       if(a[0].x==0)
       for(int i=0;i<4;i++)
       {
           a[i].x=figures[n][i]%2;
           a[i].y=figures[n][i]/2;
       }*/
       
       int k=M-1;
       for(int i=M-1;i>0;i--)
       {
           int count=0;
           for(int j=0;j<N;j++)
           {
               if(field[i][j])
                   count++;
               field[k][j]=field[i][j];
           }
           if(count<N)
               k--;
       }
       
       
       dx=0;rotate=0;delay=0.3;
     window.clear(Color::White);
      /* window.draw(background);*/
       
       for(int i=0;i<M;i++)
           for(int j=0;j<N;j++)
           {
               if(field[i][j]==0)
                   continue;
               s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
               s.setPosition(j*18, i*18);
               s.move(28,31);
               window.draw(s);
           }
       
       
       for(int i=0;i<4;i++)
       {
           s.setTextureRect(IntRect(colorNum*18,0,18,18));
           s.setPosition(a[i].x*18, a[i].y*18);
           s.move(28,31);
           window.draw(s);
       }
       window.draw(s);
     window.display();
   }
return 0;

}
