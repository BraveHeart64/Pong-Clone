#include<iostream>
#include"allegro5/alcompat.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_audio.h"
#include"allegro5/allegro_color.h"
#include"allegro5/allegro_native_dialog.h"
#include"allegro5/allegro_font.h"
#include"allegro5/allegro_ttf.h"
#include"allegro5/keyboard.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// ball needs to bounce off paddle, go off screen  and reapear after the score is counted
// first player to 3 point win the game.

class Sprite{

    int x ,y;
    float height, width;
    float boudingbox_x, boudingbox_y;
     bool down, up, hit;


    public:
    ALLEGRO_BITMAP* image;
        void SetBitmap(string nameoffile){
            // add code to quit program if file fails to load
            al_load_bitmap(nameoffile.c_str());

        }

          void Boundry(){
            if(this->y >=460){ // keeps paddle from going to low off screen
                this->y = this->y -5;

            }

            if(this->y <= 35){
                this->y = this->y +5;
               // cout<< this->y;

            }

        }





        void Release(){
            this->up = false;
            this->down = false;

        }

        int MovePlayer(){
            if(up == true){
              return  this->y = this->y -5;
            }
            else if(down == true){
                return this->y = this->y + 5;
            }
            return this->y;

        }

        void AI(){


        }

         void PressedDown(){
            this->down = true;
        }

        void PressedUp(){
            this->up = true;
        }

        bool ReturnDown(){
            return down;
        }

        bool ReturnUp(){
             return up;
        }



        int GetX(){

            return this->x;
        }

        int GetY(){
            return this->y;
        }

        float GetWidth(){

            return this->width;
        }

        float GetHeight(){

            return this->height;

        }





        // Sprite(int x1, int y1, float width1, float height1){
        Sprite(string name, int x1, int y1){
            cout<<"create";
            image = al_load_bitmap(name.c_str());
            x = x1;
            y = y1;
            width = al_get_bitmap_width(image)-3;//-3
            height = al_get_bitmap_height(image)-50;//-50
           // cout<< "Height: "<<height<<endl;
          //  cout<< "width: " <<width;
            down = false;
            up = false;
            hit = false;
        }

         void Clearbmp(){
            al_destroy_bitmap(this->image);
         }
        ~Sprite(){
                if(image != 0){
                   al_destroy_bitmap(this->image);
                }
                cout<<"Destroyed ";
        }

};


class Ball{
    private:
        bool hit;
        int x = 250;
        int y = 50;
        int x_width, y_height;
        float height;
        float width;

        ALLEGRO_BITMAP* image = al_load_bitmap("Ball.png");



    public:

    ALLEGRO_BITMAP* GetImage(){

        return this->image;
    }

        bool SetHit(bool h){
                this->hit = h;

            return this->hit;
        }


        int GetX(){
            return this->x;

        }

         int GetY(){

            return this->y;
        }

        int GetHeight(){
            return (this->height);

        }
        int GetWidth(){
            return this->width;
        }

        float GetWidth_x(){

            return this->x_width;
        }

        float GetHeight_y(){

            return this->y_height;

        }


        int BallPath(){ // 250 start out
            if(hit == false){


             // x = x - 15;
             x = x - 1;
            }else if(hit == true){

               // x =50;
                cout<<"Hit occured"<<endl;
            }

            return x;
        }

        Ball(){
            image = al_load_bitmap("Ball.png");
            this->hit = false;
            height = al_get_bitmap_height(image);
            width = al_get_bitmap_width(image);
        }

        ~Ball(){

        }

};


class HitDetection{
    private:
        bool hit = false;

    public:
        void Collsion(Sprite *obj1, Ball obj2){

            if( obj1->GetX() + obj1->GetWidth() > obj2.GetX() - obj2.GetWidth_x() &&
                obj1->GetX() - obj1->GetWidth() < obj2.GetX() + obj2.GetWidth_x() &&
                obj1->GetY()  + obj1->GetHeight()  > obj2.GetY() - obj2.GetHeight_y() &&
                obj1->GetY() -  (obj1->GetHeight())  < obj2.GetY() + obj2.GetHeight_y()){

                    cout<<"Hit";
                    this->hit = true;
                }
                else{
                    this->hit = false;
                }
//44
            al_draw_filled_rectangle(obj1->GetX()  + obj1->GetWidth(),  obj1->GetY() + obj1->GetHeight() , obj1->GetX()  - obj1->GetWidth()+15, obj1->GetY() - obj1->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));
             al_draw_filled_rectangle(24+obj2.GetX()  - obj2.GetWidth(),  obj2.GetY() - obj2.GetHeight()+24 , (obj2.GetX())  + obj2.GetWidth(), obj2.GetY() + obj2.GetHeight(), al_map_rgba_f(.7, 0, .6, .6));
         //   al_draw_filled_rectangle((obj1->GetX()+25)  - obj1->GetWidth_x(), ( obj1->GetY()+100 ) - (obj1->GetHeight_y()+25) , (obj1->GetX()-20)  + obj1->GetWidth_x(), (obj1->GetY()+8) + (obj1->GetHeight_y()-53 ), al_map_rgba_f(.7, 0, .6, .6));
            //al_draw_filled_rectangle(obj1->GetX()  - obj1->GetWidth(), ( obj1->GetY()+153 ) - obj1->GetHeight() , obj1->GetX()  + obj1->GetWidth(), obj1->GetY() + (obj1->GetHeight()-53 ), al_map_rgba_f(.7, 0, .6, .6));

        }





        bool Contact(){

            return hit;
        }


};

/* I need to figure out how to make this code work for hit detection
 bool Overlap(float spone_min, float spone_max,float sptwo_min, float sptwo_max){

            if(spone_min <= sptwo_max && sptwo_min <= spone_max){
                return true;
            }else{
              return false;
            }
        }

        bool Collide(Player one, Ball two){
            float   one_left = one.GetX();
            float   one_right = one_left + one.GetHeight();
            float   two_left = two.GetX();
            float   two_right = two_left + two.GetHeight();

            float   one_bottom = one.GetY();
            float   one_top = one_bottom + two.GetY();
            float   two_bottom = two.GetY();
            float   two_top = two_bottom + two.GetY();

            return Overlap(one_left,one_right,two_left,two_right) &&
            Overlap(one_bottom,one_top ,two_bottom ,two_top);

        }

*/







int main(int argc, char* argv[]){

string name = "Paddle.png";
    HitDetection col;


    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_joystick();
    al_init_primitives_addon();


   // Sprite* p_one = new  Sprite(name,3,50);
    Sprite* p_one = new  Sprite(name,3,150);
    Sprite* p_two = new  Sprite(name,478,150);

    Ball ball;

    ALLEGRO_TIMER* gameclock;
    double fps = 60.0;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* que;
    bool run = true;
    bool repaint = true;

  //  ALLEGRO_BITMAP*  img_ball = al_load_bitmap("Ball.png");
    ALLEGRO_BITMAP*  player_one = al_load_bitmap("Paddle.png");
    ALLEGRO_BITMAP*  player_two = al_load_bitmap("Paddle.png");
    ALLEGRO_DISPLAY* screen = al_create_display(500,500);
    al_set_window_title(screen, "Pong");

    que = al_create_event_queue();
    gameclock = al_create_timer(1.0/fps);


    al_register_event_source(que,al_get_keyboard_event_source());
    al_register_event_source(que, al_get_display_event_source(screen));
    al_register_event_source(que, al_get_timer_event_source(gameclock));


    al_start_timer(gameclock);


     while(run == true){

       al_wait_for_event(que,&event);

    switch(event.type){

        case ALLEGRO_EVENT_TIMER:
            // The game logice is here

           repaint = true;
        break;


            case ALLEGRO_KEY_ESCAPE:
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    run = false; // ends on escape
                break;



                break;

           break;

 // switch(ge.GetEventType().keyboard.keycode  ) case ALLEGRO_KEY_ESCAPE: run = false break
        case ALLEGRO_EVENT_KEY_DOWN:
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        run = false;
             }

             if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){

                        p_one->PressedDown();
             }

              if(event.keyboard.keycode == ALLEGRO_KEY_UP){
                        p_one->PressedUp();

             }


        break;

        repaint = true;


        case ALLEGRO_EVENT_KEY_UP:
            if(event.keyboard.keycode == ALLEGRO_KEY_UP){

                        p_one->Release();
             }

            if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){

                        p_one->Release();
             }




        break;





        }


        if(repaint == true && al_is_event_queue_empty(que)){

            al_clear_to_color(al_map_rgb(135,206,235));
            p_one->MovePlayer();
            p_one->Boundry();
            //al_draw_bitmap(player_one,10,50,1);
            al_draw_bitmap(player_one,p_one->GetX(),p_one->GetY()-50,1);
            al_draw_bitmap(player_two,p_two->GetX()-5,p_two->GetY()-50,1);
            al_draw_bitmap(ball.GetImage(),ball.BallPath(),50,1);//250

            //p_one.SetHit(p_one.Collide(p_one, ball));
           // p_two.SetHit(p_two.Collide(p_two, ball));
           //  ball.SetHit(p_one.Collide(p_one, ball));

            col.Collsion(p_one,ball);
            col.Collsion(p_two,ball);


            al_flip_display();

            //en.SetPaint(false);

        }




    }




    al_destroy_event_queue(que);
    //al_destroy_bitmap(img_ball);
     al_destroy_bitmap(ball.GetImage());
    al_destroy_display(screen);
    delete p_one;
    delete p_two;
    return 0;
}
