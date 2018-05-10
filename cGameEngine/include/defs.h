//defs.h
#ifndef INCLUDE_DEFS
#define INCLUDE_DEFS

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef WIN32                        //--------------WINDOWS INCLUDES-----------------------
#include <windows.h>
#include <curses.h>
typedef HANDLE thread_t;
#define ThreadCreate(a, b, c) *a = CreateThread(NULL, 0, b, c, 0, NULL)

#elif _POSIX_C_SOURCE >= 199309L    //--------------LINUX/MACOS INCLUDES-------------------
#include <time.h>
#include <pthread.h>
#include <ncurses.h>
typedef pthread_t thread_t;
#define ThreadCreate(a, b, c) pthread_create(a, NULL, b, c)
#endif

#define TERMINAL_LINES (LINES)
#define TERMINAL_COLS (COLS)

#define GENERIC_SET_INT 'i'
#define GENERIC_SET_DOUBLE 'd'
#define GENERIC_SET_POINTER 'p'
#define GENERIC_SET_STRING 's'

#define MAXOF3(a, b, c) ((a>=b)&&(a>=c))? a : ((b>=a)&&(b>=c))? b : c
#define MINOF3(a, b, c) ((a<=b)&&(a<=c))? a : ((b<=a)&&(b<=c))? b : c
#define SQUARE(n) (n * n)
#define CUBE(n) (n * n * n)
#define MAX(a, b) ((a>b)? a : b)
#define MIN(a, b) ((a<b)? a : b)

#define MAX_PANELS 10

//circle math
#define PI 3.141592f
#define FULL_CIRCLE ((2) * PI)
#define DEG2RAD(d) d * (PI/180.0f)
#define RAD2DEG(r) r * (180.0f/PI)

//color definitions
#define NUM_COLORS 8
#define MAX_TEXTURES 16
typedef uint8_t color_t;

#define ULL unsigned long long
#define LL long long

#define true 1
#define false 0

#define FRAME_TIME_MS 16

#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define CYAN 5
#define YELLOW 6
#define MAGENTA 7
#define BLACK 8
#define BACKGROUND_COLOR BLACK
#define NCURSES_BACKGROUND_COLOR COLOR_BLACK

//random number generation (inclusive)
#define RAND_IN_RANGE(l, h) (rand()%(h - l)) + (l)

/**
 * frame buffer constants and defs
 * */

//one byte for the symbol and another byte for the 255 colors
typedef uint16_t frameBuffer_t;

//I believe 8 bits would be enough, but my depth buffer is linear, so I may not be able to trust the accuracy if the scale is low enough
typedef uint32_t depthBuffer_t;
#define DEPTH_BUFFER_MAX 0xFFFFFFFF

#define BR_COLOR_BUFFER_BIT 0b01
#define BR_DEPTH_BUFFER_BIT 0b10

/**
 * an array of generic data
 * */
typedef struct set{
    void** data;        //the data in the set
    int elements;       //the number of elements in the set
    int bytes;          //the total number of bytes making up the set
    char* types;        //the types, used for freeing and so the user can figure out the type of each var
}GenericSet;

#define CLEAR_COLOR 0

/**
 * clears all content on the terminal
 * works for linux and windows and mac
 * */
void clearConsole();

/**
 * all the different ways you can render a triangle
 * */
enum DrawMode{
    RENDER_TRIANGLE_FILL,
    RENDER_POINTS,
    RENDER_LINES
};

/**
 * sleeps the thread for a set number of milliseconds and
 * has cross platform support
 * */
void sleep_ms(int milliseconds);

/**
 * returns the next byte found in a file
 * */
unsigned char nextByte(FILE* file);

/**
 * returns the time in milliseconds
 * */
uint64_t getTimeMilliseconds();

//key definitions
#define CHAR_a 'a'
#define CHAR_b 'b'
#define CHAR_c 'c'
#define CHAR_d 'd'
#define CHAR_e 'e'
#define CHAR_f 'f'
#define CHAR_g 'g'
#define CHAR_h 'h'
#define CHAR_i 'i'
#define CHAR_j 'j'
#define CHAR_k 'k'
#define CHAR_l 'l'
#define CHAR_m 'm'
#define CHAR_n 'n'
#define CHAR_o 'o'
#define CHAR_p 'p'
#define CHAR_q 'q'
#define CHAR_r 'r'
#define CHAR_s 's'
#define CHAR_t 't'
#define CHAR_u 'u'
#define CHAR_v 'v'
#define CHAR_w 'w'
#define CHAR_x 'x'
#define CHAR_y 'y'
#define CHAR_z 'z'

#define CHAR_A 'A'
#define CHAR_B 'B'
#define CHAR_C 'C'
#define CHAR_D 'D'
#define CHAR_E 'E'
#define CHAR_F 'F'
#define CHAR_G 'G'
#define CHAR_H 'H'
#define CHAR_I 'I'
#define CHAR_J 'J'
#define CHAR_K 'K'
#define CHAR_L 'L'
#define CHAR_M 'M'
#define CHAR_N 'N'
#define CHAR_O 'O'
#define CHAR_P 'P'
#define CHAR_Q 'Q'
#define CHAR_R 'R'
#define CHAR_S 'S'
#define CHAR_T 'T'
#define CHAR_U 'U'
#define CHAR_V 'V'
#define CHAR_W 'W'
#define CHAR_X 'X'
#define CHAR_Y 'Y'
#define CHAR_Z 'Z'

#endif
