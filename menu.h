#ifndef MENU_H
#define MENU_H

#include <windows.h>

#define IDM_NEW         101
#define IDM_OPEN        102
#define IDM_SAVE        103
#define IDM_SAVEAS      104
#define IDM_CLOSE       105
#define IDM_CLOSEALL    106 
#define IDM_QUIT        107
#define IDM_UNDO        201
#define IDM_REDO        202
#define IDM_CUT         203
#define IDM_COPY        204
#define IDM_PASTE       205
#define IDM_DELETE      206
#define IDM_SELECTALL   207
#define IDM_ABOUT       301

HMENU createMenuBar();

#endif
