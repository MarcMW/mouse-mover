CC = gcc
COMPILE_TIME_CHECKS = -Wall -Wextra -Wformat=2 -Wconversion -Wsign-conversion -Wtrampolines -Werror
RUN_TIME_CHECKS = -D_FORTIFY_SOURCE=3 -O2 -fstack-clash-protection -fstack-protector-strong -Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -fPIE -pie
CFLAGS = $(COMPILE_TIME_CHECKS) $(RUN_TIME_CHECKS)
all:
	$(CC) $(CFLAGS) -lX11 -pthread mouse.c

debug:
	$(CC) -lX11 -pthread -g mouse.c

clean:
ifneq (,$(wildcard ./a.out))
	rm ./a.out
endif
