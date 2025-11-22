nasm -f win64 asmfunc.asm
gcc -c main.c -o main.obj -m64
gcc main.obj asmfunc.obj -o main.exe -m64
main.exe
pause