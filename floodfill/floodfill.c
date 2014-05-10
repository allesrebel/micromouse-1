/*
 * Floodfill algorithm for California Micromouse Cal Poly SLO
 */

#include <stdio.h>
#include <math.h>
#include <msp430.h>
#define min_dist(i,j) min(min(abs(i-center)+abs(j-center),abs(i-center+1)+abs(j-center)),min(abs(i-center)+abs(j-center+1),abs(i-center+1)+abs(j-center+1)));

struct point {
  int x;
  int y;
};
struct node {
  char walls;
  char cost;
};

char to_center = 1;
char to_start = 0;

char const mapsize = 16;
char center = mapsize/2;
node maze[mapsize][mapsize];
//test maze
char const discowalls[mapsize][mapsize] = {
  11,11,11,9,5,5,5,5,5,5,5,5,5,5,5,3,
  10,10,8,2,9,5,5,5,5,5,5,5,5,5,5,2,
  12,0,2,10,10,13,5,5,3,9,5,5,5,5,3,10,
  9,6,10,10,10,9,5,5,0,4,9,5,5,5,2,10,
  8,5,6,10,10,8,5,1,4,3,12,5,5,3,10,10,
  8,5,5,6,10,10,9,4,7,14,9,5,5,6,10,10,
  10,9,5,5,6,8,0,7,9,3,12,5,5,3,10,10,
  10,8,5,5,5,6,14,9,2,8,5,5,5,6,14,14,
  10,10,9,5,5,3,11,9,6,8,1,5,1,5,1,3,
  10,12,4,5,3,10,8,5,5,6,12,1,0,5,2,10,
  8,5,5,3,10,10,12,5,5,5,5,6,12,5,2,10,
  8,5,3,10,10,10,9,5,5,5,5,5,5,5,4,2,
  9,3,10,10,10,10,12,5,5,5,5,5,5,5,3,10,
  9,0,2,10,10,12,5,5,5,5,5,5,5,5,6,14,
  10,10,8,2,12,5,5,5,5,5,5,5,5,5,5,3,
  14,14,14,12,5,5,5,5,5,5,5,5,5,5,5,6
};

struct point botdist;
botdist.x = 0;
botdist.y = 300;
struct node curnode;
curnode.x = 0;
curnode.y = 0;

int tempdist = 0;
//motor initializations here


//declear directions
enum direction{
  north = 0, east, south, west
};

enum derection direct = north;

int main() {
  for(int i = 0; i<mapsize; i++) {
    for(int j = 0; j < mapsize; j++) {
      maze[i][j].cost = min_dist(i,j);
      maze[i][j].walls = 0;
    }
  }

  for(;;) {
    
  }
}

void adddist(int dist) {
  if (direct == north) {
    botdist.y -= dist;
  }
  else if (direct == south) {
    botdist.y += dist;
  }
  else if (direct == east) {
    botdist.x += dist;
  }
  else {
    botdist.x -= dist;
  }
}
