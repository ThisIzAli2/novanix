#ifndef _HEISEN_SCREEN_H
#define _HEISEN_SCREEN_H

void InitScreen();
void PutPixel(int X,int Y,int RGB);
void PutRect(int X,int Y,int Width,int Height,int RGB);
void PutLine(int X1, int Y1, int X2, int Y2, int RGB);


#endif // _HEISEN_SCREEN_H