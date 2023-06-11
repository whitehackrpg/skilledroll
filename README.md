# skilledroll

This proof-of-concept program lets you make a d20 roll with actual player skill, imitating what it would be like trying to hit a target with a ranged weapon. You can do similar things for other objectives, making the die rolls in a game challenging and more interesting.

To compile the program, simply do `gcc skilledroll.c -o skilledroll -lncurses`. Use roguelike vi-keys (h/j/k/l/y/u/b/n) to direct the cross-hair, and press space to fire. If you are accurate enough, you get a bonus (to be applied somewhere in the system you are using), in addition to the roll.

Here's a video:


I wrote this program in C because I wanted to see how fast the original ncurses library would be compared to false terminals.

Some neat C, GDB and NCURSES resources: 

* John Erickson, _Hacking: The Art of Exploitation,_ 2nd ed., San Francisco: No Starch Press, 2008. 

* Brian W. Kernighan and Rob Pike, _The UNIX Programming Environment,_ Englewood Cliffs: Prentice Hall, 1984.

* Brian W. Kernighan and Dennis M. Ritchie _The C Programming Language,_ 2nd ed., Englewood Cliffs: Prentice Hall, 1988.

* Pradeep Padala, "NCURSES Programming HOWTO," https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/, 2005.

