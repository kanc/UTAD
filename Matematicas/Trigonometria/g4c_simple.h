// https://code.google.com/p/g4c-lib/
// Tweaked by Javier Arevalo

#pragma once

typedef int(*SpriteProc)(int, int, void *);
typedef int(*KeyProc)(int, void *);
typedef int(*MouseProc)(int x, int y, bool leftBtn, bool rightBtn, void *data);

void main();

// use those

void draw_line(int x1, int y1, int x2, int y2);
void draw_line(int x1, int y1, int x2, int y2, int clr);

void draw_ellipse(int x1, int y1, int w, int h);
void draw_ellipse(int x1, int y1, int w, int h, int penClr, int brushClr);

void draw_rect(int x1, int y1, int w, int h);
void draw_rect(int x1, int y1, int w, int h, int penClr, int brushClr);

void fill_ellipse(int x1, int y1, int w, int h);
void fill_ellipse(int x1, int y1, int w, int h, int penClr, int brushClr);

void fill_rect(int x1, int y1, int w, int h);
void fill_rect(int x1, int y1, int w, int h, int penClr, int brushClr);

void load_sprite(char *fname, int spriteNum);
void put_sprite(int spriteNum, int x, int y);
void get_sprite_pos(int spriteNum, int &x, int &y);
void get_sprite_size(int spriteNum, int &w, int &h);
void hide_sprite(int spriteNum, int x, int y);
int make_extra_sprite();

void wait(int millisecs);

int inkey();
char *input(char *prompt, int x, int y);
void text_out(char *txt, int x, int y);
void text_out(char *txt, int x, int y, int clr);
//void text_out(LPCWSTR txt, int x, int y);
//void text_out(LPCWSTR txt, int x, int y, int clr);
void register_mouse_proc(MouseProc);

void register_key_down_proc(KeyProc proc);
void register_key_up_proc(KeyProc proc);

void register_sprite_proc(SpriteProc);
void disable_sprite_proc();
void disable_sprite_proc(int spr);
void enable_sprite_proc(int spr);

void swap_sprite_images(int spr1, int spr2);
void copy_sprite_image(int spriteNum, int x, int y);


// color constants

static const int CLR_BLACK = 0;
static const int CLR_ORANGE = 1;
static const int CLR_GREEN = 2;
static const int CLR_LIGHT_GREEN = 3;

static const int CLR_DARK_BLUE = 4;
static const int CLR_BLUE = 5;
static const int CLR_DARK_RED = 6;
static const int CLR_CYAN = 7;

static const int CLR_RED = 8;
static const int CLR_LIGHT_RED = 9;
static const int CLR_YELLOW = 10;
static const int CLR_LIGHT_YELLOW = 11;

static const int CLR_DARK_GREEN = 12;
static const int CLR_MAGENTA = 13;
static const int CLR_GRAY = 14;
static const int CLR_WHITE = 15;
