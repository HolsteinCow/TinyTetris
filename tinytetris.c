#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ui.h"
#include "tetris.h"

#define T_COLOR_L_BLUE	51
#define T_COLOR_D_BLUE	20
#define T_COLOR_ORANGE	214
#define T_COLOR_YELLOW	227
#define T_COLOR_GREEN	34
#define T_COLOR_PURPLE	55
#define T_COLOR_RED		160

WINDOW *uiwindow = NULL;

extern attr matrix[X_BOUND][Y_BOUND];
extern long int score;

//attr render[X_BOUND + 10][Y_BOUND + 5];

bool init_ui(void);
void update_ui(void);
void gen_color_pairs(void);
int ui_loop(void);

void gen_color_pairs(){
	init_pair(TETRIS_BLANK, COLOR_BLACK, COLOR_BLACK);
	init_pair(TETRIS_L_BLUE, COLOR_BLACK, T_COLOR_L_BLUE);
	init_pair(TETRIS_D_BLUE, COLOR_BLACK, T_COLOR_D_BLUE);
	init_pair(TETRIS_ORANGE, COLOR_BLACK, T_COLOR_ORANGE);
	init_pair(TETRIS_YELLOW, COLOR_BLACK, T_COLOR_YELLOW);
	init_pair(TETRIS_GREEN, COLOR_BLACK, T_COLOR_GREEN);
	init_pair(TETRIS_PURPLE, COLOR_BLACK, T_COLOR_PURPLE);
	init_pair(TETRIS_RED, COLOR_BLACK, T_COLOR_RED);
}

bool init_ui(){
	/*ncurses init*/
	uiwindow = initscr();
	noecho();
	cbreak();
	nodelay(uiwindow, TRUE);
	curs_set(0);
	attrset(A_BOLD);

	/*render matrix init*/
	for(int x = 0; x < X_BOUND; x++){
		for(int y = 0; y < Y_BOUND; y++){
			matrix[x][y].char_val = 0;
			matrix[x][y].color = TETRIS_BLANK;
		}
	}
	
	/*color init*/
	start_color();

	if(has_colors() == false){
		endwin();
		fprintf(stderr, "Error: your terminal does not support colors!\n");
		return false;
	}
	
	gen_color_pairs();

	return true;
}

void update_ui(){
	for(int x = 0; x < X_BOUND; x++){
		for(int y = 0; y < Y_BOUND; y++){
			if(matrix[x][y].color){
				attron(COLOR_PAIR(matrix[x][y].color));
				mvaddch(y, x, matrix[x][y].char_val);
				attroff(COLOR_PAIR(matrix[x][y].color));
			}
			else{
				attron(A_INVIS);
				attron(COLOR_PAIR(TETRIS_BLANK));
				mvaddch(y, x, matrix[x][y].char_val);
				attroff(COLOR_PAIR(TETRIS_BLANK));
				attroff(A_INVIS);
			}
		}
	}
	refresh();
}

int main(int argc, char **argv){
	printf("here\n");
	if(!init_ui()){
		fprintf(stderr ,"Error: init_ui() faliure, ui failed to initialize\n");
		return EXIT_FAILURE;
	}
	printf("there\n");

	/*run the game*/
	tetris_init();
	printf("where\n");	
	tetris_gameloop(update_ui);	
	getch();


	/*teardown process*/
	delwin(uiwindow);
	endwin();
	return EXIT_SUCCESS;
}
