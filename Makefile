.PHONY: all compile both
.NOTPARALLEL: all mingw_all both

rm:=rm -rf
cc:=g++
mingw_cc:=x86_64-w64-mingw32-g++

gfr_src:=$(wildcard src/src/*.cpp) $(wildcard src/src/*/*.cpp) $(wildcard src/server/*.cpp) $(wildcard src/server/*/*.cpp)

gfr_inc:=-Iinc
mingw_gfr_inc:=-Iinc -Ilibs/mingw/include

gfr_cflags:=-O3 -fno-stack-protector

gfr_ldflags:=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf
mingw_gfr_ldflags:=-Llibs/mingw/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf

gfr_dt:=$(patsubst %.cpp,%.gfr,$(gfr_src))
mgfr_dt:=$(patsubst %.cpp,%.mgfr,$(gfr_src))

gfr_t:=$(patsubst %.cpp,%.o,$(gfr_src))


both: mingw_compile_game compile_game

all: compile_game test

compile_game: $(gfr_dt)
	$(cc) $(notdir $(gfr_t)) -o out/gnomefort $(gfr_cflags) $(gfr_inc) $(gfr_ldflags)
	$(rm) $(notdir $(gfr_t))

mingw_compile_game: $(mgfr_dt)
	$(mingw_cc) $(notdir $(gfr_t)) -o out/gnomefort.exe $(gfr_cflags) $(mingw_gfr_inc) $(mingw_gfr_ldflags)
	$(rm) $(notdir $(gfr_t))

mingw_all: mingw_compile_game mingw_test

mingw_test:
	cd out && ./gnomefort.exe

test:
	cd out && ./gnomefort


%.gfr : %.cpp 
	$(cc) $*.cpp -o $(notdir $*.o) -c $(gfr_cflags) $(gfr_inc)

%.mgfr : %.cpp 
	$(mingw_cc) $*.cpp -o $(notdir $*.o) -c $(gfr_cflags) $(mingw_gfr_inc)
