.PHONY: all compile
.NOTPARALLEL: all

rm:=rm -rf
cc:=g++

gfr_src:=$(wildcard src/src/*.cpp) $(wildcard src/src/*/*.cpp) $(wildcard src/server/*.cpp) $(wildcard src/server/*/*.cpp)
gfr_inc:=-Iinc -Ilib/lnx/include
gfr_cflags:=-O3 -fno-stack-protector
gfr_ldflags:=-Llib/lnx/lib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf -lz

gfr_dt:=$(patsubst %.cpp,%.gfr,$(gfr_src))
gfr_t:=$(patsubst %.cpp,%.o,$(gfr_src))


all: compile_game test



test:
	cd out && ./gnomefort

compile_game: $(gfr_dt)
	$(cc) $(notdir $(gfr_t)) -o out/gnomefort $(gfr_cflags) $(gfr_inc) $(gfr_ldflags)
	$(rm) $(notdir $(gfr_t))

%.gfr : %.cpp 
	$(cc) $*.cpp -o $(notdir $*.o) -c $(gfr_cflags) $(gfr_inc)
