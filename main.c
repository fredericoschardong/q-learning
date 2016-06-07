/*
Copyright (c) 2016 Frederico Schardong
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define STEPS 100
#define GAMMA 0.9

float world[12][4] = {0.0};
int current_x = 0, current_y;

//show the world vertically
void show_world(){
  int i, j;

  for(i = 0; i < 12; i++){
    for(j = 0; j < 4; j++){
      if(i == current_x && j == current_y){
        printf("X\t");
      }
      else{
        printf("%.1f\t", world[i][j]);
      }
    }

    printf("\n");
  }

  printf("\n\n");
}

int main(int argc, char **argv){
  int i, j;
  int episodes = 0;

  srand(time(NULL));

  //start the cliff
  for(i = 1; i < 11; i++){
    world[i][0] = -100.0;
  }

  //do{
    int steps = 1;

    do{
      float alpha = 1 / steps;
      float movements[4] = {0.0}; //0 is right, 1 is left, 2 is up and 3 is down

      if(current_x != 11){
        movements[0] = world[current_x + 1][current_y];
      }
      else{
        movements[0] = -100.0;
      }

      if(current_x != 0){
        movements[1] = world[current_x - 1][current_y];
      }
      else{
        movements[1] = -100.0;
      }

      if(current_y != 3){
        movements[2] = world[current_x][current_y + 1];
      }
      else{
        movements[2] = -100.0;
      }

      if(current_x != 0){
        movements[3] = world[current_x][current_y - 1];
      }
      else{
        movements[3] = -100.0;
      }

      float max = MAX(movements[0], MAX(movements[1], MAX(movements[2], movements[3])));
      int duplicates[4] = {0};
      int has_duplicate = 0;

      for(i = 0; i < 4; i++){
        if(movements[i] == max){
          duplicates[has_duplicate] = i;
          has_duplicate++;
        }
      }

      //printf("max %f, has_duplicate %d, %d %d %d %d\n", max, has_duplicate, duplicates[0],duplicates[1],duplicates[2],duplicates[3]);

      if(has_duplicate > 1){
        duplicates[0] = duplicates[rand() % has_duplicate];
      }

      if(duplicates[0] == 0){
        current_x++;
      }

      if(duplicates[0] == 1){
        current_x--;
      }

      if(duplicates[0] == 2){
        current_y++;
      }

      if(duplicates[0] == 3){
        current_y--;
      }

      world[current_x][current_y] = world[current_x][current_y] + alpha * (-1.0 + GAMMA * (movements[duplicates[0]] - world[current_x][current_y]));

      printf("up %f down %f left %f right %f at steps %d - %f\n", movements[2], movements[3], movements[2], movements[1], steps, world[current_x][current_y]);

      steps++;
    }while(/*current_x != 11 && current_y != 3*/ steps < 20);

    show_world();
    episodes++;
  //}while(!(current_x == 11 && current_y == 0));

  printf("Total episodes: %d\n", episodes);

  return 0;
}
