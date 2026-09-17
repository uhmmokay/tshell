## TShell
A minimalist C++ terminal shell with history tracking and status code display.
## Dependencies

* C++17 compiler
* GNU Readline library

## Build

g++ -std=c++17 main.cpp -o tshell -lreadline

## Run

./tshell

## Builtins

cd [path] — Change directory (defaults to $HOME)
exitplease — Exit the shell

