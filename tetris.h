#ifndef __TETRIS_H__
#define __TETRIS_H__

#define X_BOUND				40
#define Y_BOUND				10
#define TETRIS_HEIGHT		4

/*tetrimino coloring*/
#define TETRIS_BLANK		0
#define TETRIS_L_BLUE		1
#define TETRIS_D_BLUE		2
#define TETRIS_ORANGE		3
#define TETRIS_YELLOW		4
#define TETRIS_GREEN		5
#define TETRIS_PURPLE		6
#define TETRIS_RED			7

typedef void (*vfuncptr)(void);

typedef struct{
    char char_val;
    unsigned int color;
} attr;

typedef struct{
	unsigned int bits : 4;
} field;

enum GAMESTATE{
	PAUSE,
	GENERATE,
	FALL,
	SLIDE,
	LOCK,
	HOLD,
	LINE_CHECK,
};

enum BLOCKTYPE{
	I_BLOCK,
	L_BLOCK,
	J_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	O_BLOCK,
};

void tetris_init(void);
void tetris_gameloop(vfuncptr);
void tetris_check(void);
void delete_lines(field);
#endif
