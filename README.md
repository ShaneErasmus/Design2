# MicroMouseTemplate

MAKE SURE YOU CLONE THE WHOLE REPOSITORY

## Using as a Git Submodule

You can add this repository as a submodule in another project:

```sh
git submodule add <repo-url> MicroMouseTemplate
git submodule update --init --recursive
```

All paths in this repo are relative, so it works from any subdirectory.

## First Time Hardware setup
After completing your hardware assembly, there are 4 demo binary files. These are for the 4 permutations for the 4 potential wiring of your motors.
Flash AlignDemoX.bin onto the processor board.
Press one of the buttons close to the IMU to activate the motors.
If your robot isnt travelling forwards, flash a different DemoX until your robot is trying to move forward. 
It should avoid obstacles on each of its sides and indicate on the LEDS of the processor board if there is an object within 200mm

This should indicate that your hardware works

## For students:
Use [`StudentTemplate.slx`](./StudentTemplate.slx) as a clean starting point for your own implementation.  
→ Build on this file when creating your own solution.

## For programming the MicroMouse:
Use [`MicroMouse_Deploy.slx`](./MicroMouse_Deploy.slx)  
→ Go to **Hardware > Build, Deploy and Start**

## To skip the long build times and run directly from your machine for an unlocked and faster experience:
Use [`MicroMouse_RapidDevelopment.slx`](./MicroMouse_RapidDevelopment.slx)  
→ Go to **Simulation > Run**

## For developing with C Code:
Open the [`MicroMouseProgramming_Code`](./MicroMouseProgramming_Code) directory as an STM32 Project in VS Code or STM32CubeIDE.

