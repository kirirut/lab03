Lab 03: Process Management with Signals in C
============================================

Description:
------------
This program demonstrates interprocess communication in Unix-like systems using signals. 
The parent process spawns multiple child processes, handles signals such as SIGUSR1 and SIGUSR2, 
and manages termination of all child processes gracefully.

Project Structure:
------------------
- `src/parent.c`: Contains the parent process logic, including signal handling and child termination.
- `src/child.c`: Contains the child process logic, including timer setup and signal sending.
- `include/parent.h`: Header for parent process functions and shared data.
- `include/child.h`: Header for child process functions.
- `include/common.h`: Defines constants like MAX_CHILDREN.
- `Makefile`: Builds the parent and child executables.

Features:
---------
- Custom signal handlers using `sigaction`.
- Use of `setitimer()` for periodic signaling from child to parent.
- Clean termination of all child processes on exit.
- Output includes PID information and signal communication logging.

Build Instructions:
-------------------
1. Make sure you are in the root directory of the project.
2. Run the following command to build the project:
   ```
   cd build
   cmake ..
   make
   ```

Run Instructions:
-----------------
After building, you can run the parent and child processes as separate programs:

```bash
./build/parent
./build/child
```
Script Instruction:
-----------------
You can use scripts to run the programm
```bash
cd scripts
./build.sh
./run.sh
```

Clean Build:
------------
To clean all compiled files, run:
```
make clean
```

Author:
-------
Vadim