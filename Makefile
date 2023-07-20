CC = gcc
COMPILE_TIME_CHECKS = -Wall -Wextra -Wformat=2 -Wconversion -Wsign-conversion -Wtrampolines -Werror
RUN_TIME_CHECKS = -D_FORTIFY_SOURCE=3 -O2 -fstack-clash-protection -fstack-protector-strong -Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -fPIE -pie
CUSTOM_CHECKS = -fcf-protection=full -fharden-compares -fsanitize=address -fsanitize=leak -fsanitize=undefined
CFLAGS = $(COMPILE_TIME_CHECKS) $(RUN_TIME_CHECKS) $(CUSTOM_CHECKS) -pedantic -Wformat -Wformat-security -Wshadow -Wundef
all:
	$(CC) $(CFLAGS) -lX11 -pthread mouse.c

debug:
	$(CC) -lX11 -pthread -g mouse.c

clean:
ifneq (,$(wildcard ./a.out))
	rm ./a.out
endif
