/*
Copyright (c) 2016 Frederico Schardong
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define STEPS 100
#define GAMMA 0.9
#define EPSILON 0.05

float world[12][4] = {-1.0};
int current_x = 0, current_y = 0;

//a better random number generator
//from http://stackoverflow.com/a/6852396/557697
long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}

void set_possible_new_movements(float *movements){
  if(current_x != 11){
    movements[0] = world[current_x + 1][current_y];
  }
  else{
    movements[0] = -1000.0;
  }

  if(current_x != 0){
    movements[1] = world[current_x - 1][current_y];
  }
  else{
    movements[1] = -1000.0;
  }

  if(current_y != 3){
    movements[2] = world[current_x][current_y + 1];
  }
  else{
    movements[2] = -1000.0;
  }

  if(current_y != 0){
    movements[3] = world[current_x][current_y - 1];
  }
  else{
    movements[3] = -1000.0;
  }
}

//Q policy using greedy strategy
int get_new_movement(float *movements){
  int i, has_duplicate = 0, new_movement = 0;
  int duplicates[4] = {0};
  float max = MAX(movements[0], MAX(movements[1], MAX(movements[2], movements[3])));

  for(i = 0; i < 4; i++){
    if(movements[i] == max){
      new_movement = duplicates[has_duplicate] = i;
      has_duplicate++;
    }
  }

  if(has_duplicate > 1){
    new_movement = duplicates[random_at_most(has_duplicate - 1)];
  }

  //printf("max %f, has_duplicate %d, %d %d %d %d\n", max, has_duplicate, duplicates[0], duplicates[1],duplicates[2],duplicates[3]);

  return new_movement;
}

void make_new_movement(int new_movement){
  if(new_movement == 0){
    current_x++;
  }

  if(new_movement == 1){
    current_x--;
  }

  if(new_movement == 2){
    current_y++;
  }

  if(new_movement == 3){
    current_y--;
  }
}

//show the world vertically
void show_world(){
  int i, j;

  for(i = 0; i < 12; i++){
    for(j = 0; j < 4; j++){
      if(i == current_x && j == current_y){
        printf("X\t");
      }
      else{
        printf("%.2f\t", world[i][j]);
      }
    }

    printf("\n");
  }

  printf("\n\n");
}

int main(int argc, char **argv){
  int i, j;
  int episodes = 0;

  struct timeval t;

  gettimeofday(&t, NULL);
  srand(t.tv_usec * t.tv_sec * getpid());

  //start the cliff
  for(i = 1; i < 11; i++){
    world[i][0] = -100.0;
  }

  //end point
  world[11][0] = 100.0;

  do{
    int steps = 1;
    current_x = 0, current_y = 0;

    do{
      float alpha = 1 / (float)steps;
      float movements[4] = {0.0}; //0 is right, 1 is left, 2 is up and 3 is down

      set_possible_new_movements(movements);

      int new_movement = get_new_movement(movements);
      
      //printf("Choose movement number: %d - %s\n", new_movement, new_movement == 0 ? "right" : (new_movement == 1 ? "left" : (new_movement == 2 ? "up" : "down")));

      //if reaches the cliff then restarts
      if((current_x > 0 && current_x < 11) && current_y == 0){
        printf("Felt into the cliff at x %d y %d\n", current_x, current_y);
        current_x = current_y = 0;
        break;
      }

      //outside the map
      if((current_x == 11 && new_movement == 0) ||
         (current_x == 0 && new_movement == 1) ||
         (current_y == 3 && new_movement == 2) ||
         (current_y == 0 && new_movement == 3)){
        printf("Tried to go out of the grid\n");
        movements[new_movement] = world[current_x][current_y];
      }

      world[current_x][current_y] = world[current_x][current_y] + alpha * (-1.0 + GAMMA * (movements[new_movement] - world[current_x][current_y]));

      make_new_movement(new_movement);

      //printf("up %f down %f left %f right %f at steps %d - %f, current x %d current y %d\n", movements[2], movements[3], movements[1], movements[0], steps, world[current_x][current_y], current_x, current_y);

      steps++;
    }while(steps < 20);

    show_world();
    episodes++;
  }while(/*!(current_x == 11 && current_y == 0)*/ episodes < 20);

  printf("Total episodes: %d\n", episodes);

  return 0;
}
