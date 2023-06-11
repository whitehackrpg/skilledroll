/* This dice roller involves player skill. The idea is that x moves to
 * and fro across the screen over a range of numbers, one of which is 
 * marked as the target. It moves fast, and then stops once you press 
 * space. The difference between your stop and the target is how well you
 * did, and it can be used to modify an existing roll at some predecided
 * rate. For example, if I get 2, this might be enough to modify a d6 
 * roll by 1, or ad20 roll by up to 3. */

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int row,col,maxr,maxc,x,y,ch,rd,timecounter,acc;

int roll_die(int);
void updatescreen(); 
void targetting();
void display_results();
void quitting();

int main()
{
  srand(time(NULL));
  
  // preparing curses
  initscr();
  cbreak();
  noecho();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
  nodelay(stdscr, TRUE);
  attron(A_BOLD);
  curs_set(0);
  refresh();

  // setting some initial values
  getmaxyx(stdscr,maxr,maxc);
  row = maxr/2;
  col = maxc/2;
  x = roll_die(maxc);
  y = roll_die(maxr);
  timecounter = 0;
  
  targetting(); // main loop
  
  display_results(); 

  quitting();
  
  return 0;
}


int roll_die(int sides)
{
  int die_specific_rand_max = RAND_MAX - (RAND_MAX % sides);
  int rnum;

  while((rnum = rand()) >= die_specific_rand_max); // avoid skewing the roll
  return rnum % sides;
}

void update_screen() {
   clear(); 
  mvprintw(row-1,col,"|");
  mvprintw(row,col-3,"--   --");
  mvprintw(row+1,col,"|");
  mvprintw(y,x,"%d",rd);

  attron(COLOR_PAIR(1));
  mvprintw(0,0,"Player Accuracy (0--10): %d. Time Left: %ds."
	   ,acc,10-timecounter/20);
  attroff(COLOR_PAIR(1));

  refresh();
}

void targetting() {
  ch = getch();

  // move the cross-hair
  if      (ch == 'l') {col+=1;}
  else if (ch == 'h') { col-=1; }
  else if (ch == 'j') { row+=1; }
  else if (ch == 'k') { row-=1; }
  else if (ch == 'y') { col--; row--; }
  else if (ch == 'u') { col++; row--; }
  else if (ch == 'b') { col--; row++; }
  else if (ch == 'n') { col++; row++; }

	   
  // roll the die and move it
  rd = roll_die(20)+1;
  y = y+roll_die(3)-1;
  x = x+roll_die(3)-1;

  // stay away from the screen borders
  if (y < 0) y =+ 10;
  if (y > maxr) y =- 10;
  if (x < 0) x =+ 20;
  if (x > maxc) x =- 20;
      
  // calculate player accuracy
  acc= 10 - (float)((abs(row - y) + 1 + abs(col - x)) 
		    / 2) / ((maxr+maxc)) * 100;
  if (acc < 0) acc=0;
  
  update_screen();
  usleep(50000);
  timecounter++;
  if (10-timecounter/20 > 1 && ch != ' ') targetting();
}

void display_results() {

  attron(COLOR_PAIR(1));
  if (acc <= 8) {
    mvprintw(0,0,"Player Accuracy (0--10): %d. Time Left: %ds. Roll: %d.",
	     acc,10-timecounter/6000,rd);
  } else if (acc > 8 && acc < 10) {
    mvprintw(0,0,"Player Accuracy (0--10): %d. Time Left: %ds. Roll: %d."
	     " Modification: +/- 1."
	     ,acc,10-timecounter/6000,rd); 
  } else if (acc == 10) {
    mvprintw(0,0,"Player Accuracy (0--10): %d. Time Left: %ds. Roll: %d."
	     " Modification: +/- 2.",acc,10-timecounter/6000,rd); 
  }
  attroff(COLOR_PAIR(1));
}

void quitting() {
  nodelay(stdscr, FALSE);
  getch();
  mvprintw(2,0,"Press again to quit.");
  attroff(A_BOLD);
  getch();
  endwin();
}
