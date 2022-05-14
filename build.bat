@echo off
g++ *.cpp -o game.exe -O1 -static -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32  -lwinmm
game