#include "snake.h"
#include <stdlib.h>

struct snake* add_snake(struct snake* snake,int x,int y){
	struct snake* hlava = calloc(1,sizeof(struct snake));

	hlava->x = x;
	hlava->y = y;
	hlava->next = snake;
	
	return hlava;
}

struct snake* remove_snake(struct snake* snake){
	if(snake == NULL){ free(snake); return NULL; }  //prazdny vstup

	if(snake->next == NULL){ free(snake); return NULL; } //jednoprvkovy vstup
	
	struct snake* ptr = snake; //pomocny pointer
	//hladanie predposledneho prvku
	
	while(ptr->next->next != NULL){
		ptr = ptr->next; 
	}
	//odstranenie posledneho prvku
	ptr->next = NULL;
	free(ptr->next);
	return snake;
	
}

void free_snake(struct snake* sn){
	free(sn);
}


int is_snake(struct snake* snake,int x,int y){
	struct snake* ptr = snake;
	while(ptr != NULL){
		if(ptr->x == x && ptr-> y == y){ return 1; }
		ptr = ptr->next;
	}
	return 0;
}

int step_state(struct state* st){
	int nx = (st->snake->x + st->sx);
    	int ny = (st->snake->y + st->sy);
    	return END_CONTINUE;
}
