#include "world.h"
#include <stdlib.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"
// This file contains functions for drawing the the game and changing the state

// Start is called one in the beginning
void* init_game(){
    // Allocate memory for the state
    struct state* st = calloc(1,(sizeof(struct state)));
    return st;
}

// The first event
// Initialize game state
// - borders
// - snake position
// - food position
void init_snake(struct event* world, struct state* st){
    int cy = world->height/2;
    int cx = world->width/2 - 5;
    for (int i = 0; i < 5; i++){
        st->snake = add_snake(st->snake,cx + i ,cy);
    }

    int h = world->height;
    int w = world->width;
    for (int i = 0; i < 5; i++){
        st->foodx[i] = rand() % w;
        st->foody[i] = rand() % h;
    }
    // Initial game vector
    st->sx = 1;
    st->sy = 0;
}

// Step is called in a loop once in interval.
// It should modify the state and draw it.
int world_event(struct event* w,void* game){
    // Get state pointer
    struct state* st = game;
    if (w->type == EVENT_START){
        // Called on beginning
        init_snake(w,st);
    }
    // Called on key press
    else if (w->type == EVENT_KEY){
        int key = w->key;
        // Modifies vector of snake movement
        if (key == KEY_RIGHT){
           st->sx = 1;
           st->sy = 0;
        }
        else if (key == KEY_LEFT){
            st->sx = -1;
            st->sy = 0;
        }
        else if (key == KEY_DOWN){
            st->sx = 0;
            st->sy = 1;
        }
        else if (key == KEY_UP){
            st->sx = 0;
            st->sy = -1;
        }
    }
    // Called on esc key
    else if (w->type == EVENT_ESC){
            // Non zero means finish the loop and stop the game.
            return 1;
    }
    // Called on interval timeout
    else if (w->type == EVENT_TIMEOUT){
        clear_screen();
        // Copy screen size
        st->width = w->width;
        st->height = w->height;
        // Change game state
        int r = step_state(st);
        char ms[200];
        sprintf(ms,"r %d\n",r);
        set_message(ms,9,9);
        // Draw snake
        struct snake* sn = st->snake;
        while (sn != NULL){
            set_cell('x',sn->x,sn->y);
            sn = sn->next;
        }
        // Draw food
        for (int i = 0 ; i < FOOD_COUNT; i++){
            if (st->foodx[i] >= 0 && st->foody[i] >= 0){
                set_cell('*',st->foodx[i],st->foody[i]);
            }
        }
        // Stop the game
        if (r){
            char message[] = "Koniec";
            set_message(message,10,10);
        }
    }
    return 0;
}


int main(int argc, char** argv){
    start_world(init_game,world_event,free);
    return 0;
}
