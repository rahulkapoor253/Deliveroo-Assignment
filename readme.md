**DELIVEROO WORK HOME ASSIGNMENT - CRON EXPRESSION PARSER**

The script is developed in C++ and Catch2 is used for Unity Testing due to its simplicity and compatibility with Mac M1.

**How to run the script:**

- First, we need to build the program. It is under program/main.cpp
- Build it with this command in terminal: ```g++ -std=c++11 program/main.cpp```
- This will create the default executable file: a.out in your project.
- Run it with command in terminal: ```./a.out '*/15 0 1,15 * 1-5 /usr/bin/find'```


Sample output with the above args:
```
minute        0 15 30 45
hours         0
day of month  1 15
month         1 2 3 4 5 6 7 8 9 10 11 12
day of week   1 2 3 4 5
command       /usr/bin/find
```


**How to run the test file**

- Commend out the main func in the program/main.cpp file. As single header file catch.hpp will be having it.
- Build the test file with this command in terminal: ```g++ -std=c++11 testing/test.cpp```
- This will create the default executable file: a.out in your project.
- Run it with command in terminal: ```./a.out```


