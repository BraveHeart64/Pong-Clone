#include<iostream>
#include"allegro5/alcompat.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_audio.h"
#include"allegro5/allegro_color.h"
#include"allegro5/allegro_native_dialog.h"
#include"allegro5/allegro_font.h"
#include"allegro5/allegro_ttf.h"
#include"allegro5/keyboard.h"

using namespace std;

// ball needs to bounce off paddle, go off screen  and reapear after the score is counted
// first player to 3 point win the game.
class Ball{


};

class Player{
    float y = 50.5;
    float x = 3.5;
    const float width = 19;
    const float height = 101;
    bool down, up;


    public:
        bool Overlap(float spone_min, float spone_max,float sptwo_min, float sptwo_max){

            if(spone_min <= sptwo_max && sptwo_min <= spone_max){
                return true;
            }else{
              return false;
            }
        }

        bool Collide(Player one, Player two){
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

        void Boundry(){
            if(this->y >=402){ // keeps paddle from going to low off screen
                this->y = this->y -5;
            }
            else if( this->y <= -1){ // keeps paddle form gooing to high
            this->y = this->y +5;

            }

        }

        int GetX(){
            return this->x;
        }

        int GetY(){
            return this->y;
        }

        int GetHeight(){
            return this->height;

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

        void HitDetection(){


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

        Player(){
            down = false;
            up = false;
        }


};




int main(int argc, char* argv[]){
    Player p_one, p_two;

    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_joystick();


    ALLEGRO_TIMER* gameclock;
    double fps = 60.0;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* que;
    bool run = true;
    bool repaint = true;

    ALLEGRO_BITMAP*  ball = al_load_bitmap("Ball.png");
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

                        p_one.PressedDown();
             }

              if(event.keyboard.keycode == ALLEGRO_KEY_UP){
                        p_one.PressedUp();

             }


        break;

        repaint = true;


        case ALLEGRO_EVENT_KEY_UP:
            if(event.keyboard.keycode == ALLEGRO_KEY_UP){

                        p_one.Release();
             }

            if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){

                        p_one.Release();
             }




        break;





        }


        if(repaint == true && al_is_event_queue_empty(que)){

            al_clear_to_color(al_map_rgb(135,206,235));
            p_one.MovePlayer();
            p_one.Boundry();
            //al_draw_bitmap(player_one,10,50,1);
             al_draw_bitmap(player_one,p_one.GetX(),p_one.GetY(),1);
            al_draw_bitmap(player_two,478,50,1);
            al_draw_bitmap(ball,250,50,1);




            al_flip_display();

            //en.SetPaint(false);

        }




    }




    al_destroy_event_queue(que);
    al_destroy_bitmap(ball);
    al_destroy_bitmap(player_one);
    al_destroy_bitmap(player_two);
    al_destroy_display(screen);
    return 0;
}
