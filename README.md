# skilledroll

This proof-of-concept program lets you make a d20 roll with actual player skill, imitating what it would be like trying to hit a target with a ranged weapon. You can do similar things for other objectives, making the die rolls in a game challenging and more interesting.

I wrote this program in C because I wanted to see how fast the original ncurses library would be compared to false terminals.

To compile, simply do `gcc skilledroll.c -o skilledroll -lncurses`. Use roguelike vi-keys (h/j/k/l/y/u/b/n) to direct the cross-hair, and press space to fire. If you are accurate enough, you get a bonus (to be applied somewhere in the system you are using), in addition to the roll.

Here's a video:

https://github.com/whitehackrpg/skilledroll/assets/130791778/df5b9d4c-78ec-4e87-bc61-99352c483bb9



