#ifndef snake_h_INCLUDED
#define snake_h_INCLUDED

// Number of food items on the plane
#define FOOD_COUNT 5

/**
 * One part of the snake;
 * 
 * The snake is a linked list;
 */
 
struct snake {
    // x position of the snake part
    int x;
    // y position of the snake part
    int y;
    // Pointer to the next snake part.
    // The last part of the snake has NULL pointer to the next part.
    struct snake* next;
};

// End game reason constants, return value of step_state
enum endgame {
    // Continue the game
    END_CONTINUE = 0,
    // Snake hit a wall
    END_WALL,
    // Snake hit itself
    END_SNAKE,
    // No food left
    END_FOOD,
    // Other reason to end
    END_USER
};

/**
 * State of the game.
 * 
 * The state consists of the snake, its speed and food on the plane.
 * 
 * The snake is a linked list of snake parts.
 * 
 * Speed vector is a vector added to the last head position to create a new head.
 * 
 * Food are points on the plane. Food with negative coordinates meads food is already eaten.
 */
 
struct state {
    // Snake as a linked list
    struct snake* snake;
    // X of the food positions
    int foodx[FOOD_COUNT];
    // Y of the food positions
    int foody[FOOD_COUNT];
    int sx;
    int sy;
    int width;
    int height;
};

/**
 * Add a new snake part with given position. The new snake part becomes the new head.
 *
 * @param head of the snake.
 * @param x coordinate of the new head;
 * @param y coordinate of the new head.
 * @return new head of the snake.
 */
struct snake* add_snake(struct snake* snake,int x,int y);

/**
 * Remove the last snake part.
 * The last snake part  should always have NULL next pointer.
 *
 * @param head of the snake.
 * @return new head of the snake.
 */
struct snake* remove_snake(struct snake* snake);

/**
 * Finds out if given coordinates are part of the snake.
 * @param snake
 * @param x coordinate to search in snake
 * @param y coordinate to search in snake
 * @return True, if there is a snake part with coordinates x,y. False otherwise
 *
 */
int is_snake(struct snake* snake,int x, int y);
/**
 * Remove and free each snake part;
 * @param head of the snake.
 */
void free_snake(struct snake* sn);
/**
 * Change game state.
 *
 * The function shoud calculate new posision of the snake head
 * from the current position and speed vector.
 * Then it should modify snake parst  or food coordinates according to the rules:
 * 
 * - If the new position is on the snake, end the game, return END_SNAKE.
 * - If the new position is on the food, mark food as eaten
 *   (set its coordinates to -1) and add new snake part on the position of the food. If there is no food left, return END_FOOD. else return END_CONTINUE.
 * - If the new position is on the plane, add new snake part on the new position and remove the last part of the snake, return END_CONTINUE.
 * 
 * @param current state of the game
 * @return reason to end the game according to enum endgame.
 */
int step_state(struct state* state);


#endif // snake_h_INCLUDED

