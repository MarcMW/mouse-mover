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

void t_mmover(){
  // time structure used for nanosleep function
  struct timespec times;
  times.tv_sec=1;   // seconds to sleep
  times.tv_nsec=0; //100000000;  // nanosec to sleep
  // move distance
  int x_move = 100;

  // open the main display (this should work on most systems)
  // main loop
  Display *display = XOpenDisplay(":0.0");
  while(t_mmover_running){
    XWarpPointer(display, None, None, 0,0,0,0,x_move,0); // actual move
    XFlush(display); // flush display to make changes, if not flushed, sleep will interfere
    x_move *= -1; // change direction for next move
    nanosleep(&times,NULL); // sleep thread
  }
  XCloseDisplay(display); // finish and clean

}

main(){
  // call mouse mover function in new thread
  pthread_t tid;
  pthread_create(&tid, NULL, (void * (*)(void *))t_mmover, NULL);

  // kill loop in mover thread
  printf("press any key to quit\n");
  getc(stdin);
  t_mmover_running = 0;

  //
  pthread_join(tid, NULL); // wait for thread to exit  finish


  return 0;
}

  /*
  running = 1;

  pid_t pid = fork();
  if(pid < 0 ){ // fail
    printf("fork failure\n");
    return 1;
  } else if (pid) { // parent process
    printf("press any key to quit\n");
    getc(stdin);
    running = 0;
  } else { // child

  }

  */
