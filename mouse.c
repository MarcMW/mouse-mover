/*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <marc@informaficker.org> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return
* Marc Müller-Weinhardt
* ----------------------------------------------------------------------------
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int t_mmover_running = 1;

void* t_mmover(){
  // time structure used for nanosleep function
  struct timespec times;
  times.tv_sec=1;   // seconds to sleep
  times.tv_nsec=0; //100000000;  // nanosec to sleep
  // move distance
  int x_move = 100;

  // open the main display (this should work on most systems)
  Display *display = XOpenDisplay(":0.0");
  while(t_mmover_running){  // main loop
    XWarpPointer(display, None, None, 0,0,0,0,x_move,0); // actual move
    XFlush(display);        // flush display to make changes visible
    x_move *= -1;           // change direction for next move
    nanosleep(&times,NULL); // sleep thread
  }
  XCloseDisplay(display);   // finish and clean
  return NULL;
}

int main(){
  // call mouse mover function in new thread
  pthread_t tid;
  pthread_create(&tid, NULL, (void* (*)(void*))t_mmover, NULL);
  printf("press any key to quit\n");
  getc(stdin);             // wait for user interaction
  t_mmover_running = 0;    // stop main loop in thread

  pthread_join(tid, NULL); // wait for thread to finish


  return 0;
}
