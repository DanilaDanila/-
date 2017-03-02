#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
using namespace sf;

const double pi=3.1415;
const double degtorad=180*pi;

class hand
{
public:
    int leng;
    float rotation;
    float speed;
    FloatRect coords;
    RectangleShape hand;
    
    void setup(float x,float y)
    {
        coords.left=x;
        coords.top=y;
        rotation=0;
        hand.setSize(Vector2f(5,leng));
        hand.setFillColor(Color::Green);
        hand.setOrigin(3,leng);
        hand.setPosition(coords.left,coords.top);
        rotation=0;
    }
    
    FloatRect get()
    {
        FloatRect c;
        /*if(rotation==0){
         c.left=c.left;
         c.top=c.top+leng;
         }
         else
         {
         }*/
        c.left=coords.left+leng*cos(rotation-pi/2);
        c.top=coords.top+leng*sin(rotation-pi/2);
        return c;
    }
    
    void update(FloatRect c,float time)
    {
        if(time!=0)
        {rotation+=speed*time;
            coords=c;
            hand.setRotation(rotation*180/pi);
            hand.setPosition(coords.left,coords.top);
        }
    }
    
    void draw(RenderWindow *window)
    {
        window->draw(hand);
    }
};

int main(int argc, char const** argv)
{
    int speed=1;
    bool show=true;
    Image fon;
    fon.create(800,800,Color::White);
    Texture tfon;
    tfon.loadFromImage(fon);
    Sprite sfon;
    sfon.setTexture(tfon);
    
    int m;
    
    while(true)
    {
        std::cout<<"\nВведите колличество колен\n";
        std::cin>>m;
        std::vector<hand> hands(m);
        
        for(int i=0;i<m;i++)
        {
            std::cout<<"\nВведите длинну "<<i+1<<"\n";
            std::cin>>hands[i].leng;
        }
        
        for(int i=0;i<m;i++)
        {
            std::cout<<"\nВведите скорость "<<i+1<<"\n";
            std::cin>>hands[i].speed;
        }
        
        for(int i=0;i<m;i++)
        {
            if(i==0) hands[i].setup(400,400);
            else
            {
                FloatRect r;
                r=hands[i-1].get();
                hands[i].setup(r.left,r.top);
            }
        }
        
        float time;
        Clock clock;
        
        RenderWindow window(VideoMode(800,800),"Spirograph");
        while (window.isOpen())
        {
            time=clock.getElapsedTime().asSeconds()/10;
            clock.restart();
            
            Event event;
            while (window.pollEvent(event))
            {
                if(event.type==event.Closed) window.close();
            }
            window.clear(Color::White);
            
            if(Keyboard::isKeyPressed(Keyboard::Space)) {fon.saveToFile(argv[1]);while(Keyboard::isKeyPressed(Keyboard::Space));}
            //if(Keyboard::isKeyPressed(Keyboard::W)) {show=!show;time=0;while(Keyboard::isKeyPressed(Keyboard::W));}
            
            for(int i=0;i<m;i++)
            {
                if(i==0) hands[i].update(hands[i].coords,time);
                else
                {
                    FloatRect r;
                    r=hands[i-1].get();
                    hands[i].update(r,time);
                }
            }
            
            FloatRect r;
            r=hands[m-1].get();
            fon.setPixel(r.left,r.top,Color::Blue);
            fon.setPixel(r.left-1,r.top,Color::Blue);
            fon.setPixel(r.left+1,r.top,Color::Blue);
            fon.setPixel(r.left,r.top-1,Color::Blue);
            fon.setPixel(r.left,r.top+1,Color::Blue);
            tfon.loadFromImage(fon);
            sfon.setTexture(tfon);
            window.draw(sfon);
            
            if(show) for(int i=0;i<m;i++) hands[i].draw(&window);
            
            window.display();
        }
        for(int i=0;i<800;i++)
            for(int j=0;j<800;j++)
                fon.setPixel(i,j,Color::White);
    }
    return 0;
}
