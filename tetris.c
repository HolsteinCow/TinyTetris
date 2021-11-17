#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"

long int score;
attr matrix[X_BOUND][Y_BOUND];

double gen_rand_d(){return (double)rand() / (double)RAND_MAX;}

void tetris_init(){
	printf("wut");
	time_t t;
	score = 0;
	unsigned int SEED = (unsigned)time(&t);
	srand(SEED);
	printf("%d", SEED);
}

void tetris_check(){
	/*if a line is full, a bit is set to 1 in int line*/
	field f;
	f.bits = 0;
	for(int y = Y_BOUND - TETRIS_HEIGHT; y < Y_BOUND; y++){
		for(int x = 0; x < X_BOUND; x++){
			if(!matrix[x][y].char_val)
				continue;	
			f.bits |= 1 << (Y_BOUND - y);
		}
	}
	if(f.bits){
		delete_lines(f);
	}
}

void delete_lines(field bitfield){
	for(int i = 1; i <= 4; i++){
		/*if the bit field has bit set to 1 at the position to remove line*/
		if((bitfield.bits >> i) & 1){
			for(int x = 0; x < X_BOUND; x++){
				matrix[x][i].char_val = 0;
				matrix[x][i].color = TETRIS_BLANK;
				score += 1000;
			}
		}
	}
	/*tetris bonus*/
	if(bitfield.bits == 7){
		score += 6000;
	}
}

void tetris_gameloop(vfuncptr update){
	for(;;){
		/*testing*/
		matrix[0][0].color = TETRIS_YELLOW;
		matrix[1][0].color = TETRIS_YELLOW;
		matrix[0][1].color = TETRIS_YELLOW;
		matrix[1][1].color = TETRIS_YELLOW;
		matrix[0][0].char_val = ' ';
		matrix[1][0].char_val = ' ';
		matrix[0][1].char_val = ' ';
		matrix[1][1].char_val = ' ';

		tetris_check();
		update();
		break;
	}
}
