CC = gcc
COMPILE_TIME_CHECKS = -Wall -Wextra -Wformat=2 -Wconversion -Wsign-conversion -Wtrampolines -Werror
RUN_TIME_CHECKS = -fstack-clash-protection -fstack-protector-strong -Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -fPIE -pie
CFLAGS = $(COMPILE_TIME_CHECKS) $(RUN_TIME_CHECKS)
all:
	$(CC) $(CFLAGS) -lX11 -pthread -g mouse.c
