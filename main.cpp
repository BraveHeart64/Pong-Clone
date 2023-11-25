#include<iostream>
#include<math.h>
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

    float x ,y;
    float vel;
    int hit;
    float height, width;
    bool down, up;


    public:
    ALLEGRO_BITMAP* image;
        void SetBitmap(string nameoffile){
            // add code to quit program if file fails to load
            al_load_bitmap(nameoffile.c_str());

        }



           void SetHit(int h){
                this->hit = h;

        }

            int GetHit(){
                return this->hit;
            }

          void Boundry(){
            if(this->y >=460){ // keeps paddle from going to low off screen
                this->y = this->y -5;

            }

            if(this->y <= 45){
                this->y = this->y +5;
               // cout<< this->y;

            }

        }





        void Release(){
            this->up = false;
            this->down = false;

        }

        void PlayerVelocityUp(){
            this->vel= this->vel - 0.5;

            if(this->vel <= -1.5){
                this->y = this->y-1.1;
            }
            else if(this->vel <= -2.5){
                this->y = this->y-2.1;
            }
            else if(this->vel <= -5.0){

                this->y = this->y -5.5;
            }
              if(this->vel <= -5.5){
                this->vel = -5.5;
            }

        }




        void PlayerVelocityDown(){
            this->vel= this->vel + 0.5;

            if(this->vel >= 1.5){
                this->y = this->y+1.1;
            }
            else if(this->vel >=  2.5){
                this->y = this->y+2.1;
            }
            else if(this->vel >5.0){

                this->vel =this->vel + 5.5;
            }

            if(this->vel >= 5.5){
                this->vel = 5.5;
            }


        }

        void Idle(){

            if(this->vel > 0.0){
                this->vel = this->vel -0.5;
            }
            else if(this->vel < 0.0){
                this->vel = this->vel +0.5;
            }
             cout<<this->vel<<endl;
        }


        int MovePlayer(){
             cout<<this->vel<<endl;
            if(up == true){

               PlayerVelocityUp();

             // return  this->y = this->y -5;
              return 1;
            }
            else if(down == true){
                PlayerVelocityDown();
               // return this->y = this->y + 5;
                return 1;
            }
            Idle();
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

            image = al_load_bitmap(name.c_str());
            x = x1;
            y = y1;
            this->vel = 0.0;
            width = al_get_bitmap_width(image);//-3
            height = al_get_bitmap_height(image)-50;//-50

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

        }

};


class Ball{
    private:
        int hit = 0;
        int dir = 0;
        float angle = 0;
        float x = 250;//250
        float y = 50;//50
        int x_width, y_height;
        float height;
        float width;

        ALLEGRO_BITMAP* image = al_load_bitmap("Ball.png");



    public:

    ALLEGRO_BITMAP* GetImage(){

        return this->image;
    }

        void SetHit(int h){
                this->hit = h;

        }

        bool GetHit(){
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

        void Contact(bool rightpaddle, bool left_paddle){


        }


        int BallPath(int con_one,int con_two){ // 250 start out


             if(con_one == 1 && dir == 0){
                dir = 1;
                con_one = 0;

            }
             if(con_two == 1 && dir == 1){

               dir = 0;
                con_two = 0;
            }


            if(dir == 0){
                x=x-1;

            }
            else if(dir == 1){
                x=x + 1;
            }


            return x;
        }

        Ball(){
            image = al_load_bitmap("Ball.png");

            height = al_get_bitmap_height(image);
            width = al_get_bitmap_width(image);
        }

        ~Ball(){
            al_destroy_bitmap(image);
            delete this;
        }

};


class HitDetection{



    public:
        int OverLap(float m_one, float max_one, float m_two, float max_two){

                if(m_two <= max_one && m_one <= max_two){
                    return 1;
                }

            return 0;

        }

        int Collsion(Sprite *obj1, Ball* obj2){


             //al_draw_filled_rectangle(24+obj2->GetX()  - obj2->GetWidth(),  obj2->GetY() - obj2->GetHeight()+24 , obj2->GetX()  + obj2->GetWidth(), obj2->GetY() + obj2->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));

            float obj1_left =  obj1->GetX();
            float obj1_right =  obj1_left + obj1->GetWidth()-5;
            float obj2_left = obj2->GetX();
            float obj2_right = obj2_left + obj2->GetWidth();



            float obj1_bottom =  obj1->GetY()-45;
            float obj1_top =  obj1_bottom + obj1->GetHeight();
            float obj2_bottom = obj2->GetY();
            float obj2_top = obj2_bottom  + obj2->GetHeight();

            // al_draw_filled_rectangle(obj1->GetX()  + obj1->GetWidth(),  obj1->GetY() + obj1->GetHeight() , obj1->GetX()  - obj1->GetWidth(), obj1->GetY() - obj1->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));//obj1->GetWidth()+17



            return OverLap(obj1_left, obj1_right, obj2_left, obj2_right)&&
            OverLap(obj1_bottom ,obj1_top, obj2_bottom, obj2_top) ;
        }
};


/*

class HitDetection{



    public:
        void Collsion(Sprite *obj1, Ball* obj2){


             al_draw_filled_rectangle(obj1->GetX()  + obj1->GetWidth(),  obj1->GetY() + obj1->GetHeight() , obj1->GetX()  - obj1->GetWidth()+15, obj1->GetY() - obj1->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));
             al_draw_filled_rectangle(24+obj2->GetX()  - obj2->GetWidth(),  obj2->GetY() - obj2->GetHeight()+24 , (obj2->GetX())  + obj2->GetWidth(), obj2->GetY() + obj2->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));


            if( obj1->GetX() + obj1->GetWidth() > obj2->GetX() - obj2->GetWidth_x() &&
                obj1->GetX() - obj1->GetWidth() < obj2->GetX() + obj2->GetWidth_x() &&
                obj1->GetY()  + obj1->GetHeight()  > obj2->GetY() - obj2->GetHeight_y() &&
                obj1->GetY() -  (obj1->GetHeight())  < obj2->GetY() + obj2->GetHeight_y()){

                 //obj2->SetHit( true);
                obj2->SetHit(false);
                }
                else{
                   // obj2->SetHit(false);

                obj2->SetHit( true);
                }


        }



};

*/



/*

        int Collsion(Sprite *obj1, Ball* obj2){

                //obj1->GetWidth()+15
             al_draw_filled_rectangle(obj1->GetX()  + obj1->GetWidth(),  obj1->GetY() + obj1->GetHeight() , obj1->GetX()  - obj1->GetWidth()+17, obj1->GetY() - obj1->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));
             al_draw_filled_rectangle(24+obj2->GetX()  - obj2->GetWidth(),  obj2->GetY() - obj2->GetHeight()+24 , obj2->GetX()  + obj2->GetWidth(), obj2->GetY() + obj2->GetHeight(), al_map_rgba_f(.7, 0, .6, .6));

            float obj1_left =  obj1->GetX();
            float obj1_right =  obj1_left + obj1->GetWidth()+17;
            float obj2_left = obj2->GetX()+24;
            float obj2_right = obj2_left + obj2->GetWidth();



            float obj1_bottom =  obj1->GetY();
            float obj1_top =  obj1_bottom + obj1->GetHeight();
            float obj2_bottom = obj2->GetY();
            float obj2_top = obj2_bottom  + obj2->GetHeight()+24;




            return OverLap(obj1_left, obj1_right, obj2_left, obj2_right)&&
            OverLap(obj1_bottom ,obj1_top, obj2_bottom, obj2_top) ;
        }
};


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

    Sprite* p_two = new  Sprite(name,478,50);
    Ball* ball = new Ball();

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
                //ball.SetHit(true);
            //al_draw_bitmap(player_one,10,50,1);








            al_draw_bitmap(player_one,p_one->GetX(),p_one->GetY()-51,1);
            al_draw_bitmap(player_two,p_two->GetX()-5,p_two->GetY()-51,1);

            p_one->SetHit(col.Collsion(p_one,ball));
            p_two->SetHit( col.Collsion(p_two,ball));
           // ball->BallPath(p_one->GetHit());
            /*
                    Suggestion to fixing the code we are overwriting it thats the error

                bool collision_p1 = col.Collsion(p_one, ball);
                bool collision_p2 = col.Collsion(p_two, ball);

                ball->SetHit(collision_p1 || collision_p2);

            */


            al_draw_bitmap(ball->GetImage(),ball->BallPath(p_one->GetHit(),p_two->GetHit()),50,1);//250


            al_flip_display();

            //en.SetPaint(false);

        }




    }




    al_destroy_event_queue(que);
    //al_destroy_bitmap(img_ball);
     al_destroy_bitmap(ball->GetImage());
    al_destroy_display(screen);
    delete p_one;
    delete p_two;

    return 0;
}
