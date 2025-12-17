# R.O.B. Macintosh Driver

<img src="https://i91.servimg.com/u/f91/14/82/73/92/20251210.jpg" alt="R.O.B. and Macintosh Classic II setup" width="512">

Control your Nintendo **R.O.B.** (Robotic Operating Buddy) using a classic 68k Macintosh as a "remote control"—by flashing the CRT display in patterns R.O.B. understands!  
_A project by Sirix1995, 2025_

---

## What is this?

This is a C program for vintage Macintosh computers (tested on Macintosh Classic II or compatible) that sends commands to Nintendo's R.O.B. robot accessory using the Mac's screen. R.O.B. recognizes sequences of flashes produced by the display and interprets them as commands, just like the original NES games (such as *Gyromite*) which communicated with the robot with **no wires—just light patterns on a CRT!**

**You can:**
- Move R.O.B.'s arms using the arrow keys (Up, Down, Left, Right)
- Open/close R.O.B.'s hands (`Q` = Close, `S` = Open)
- Turn R.O.B.'s "LED ON" (`T`)
- Exit the program (`X`)

Just run the program, put R.O.B. facing your Mac's CRT, and use your keyboard to control your robot companion!

---

## How does it work?

R.O.B. reads data via his "eyes"—sensors that detect flashes on a CRT. This program generates precise pulse and timing patterns for different commands, toggling the entire screen between black and white. Each command is a series of these flashes (see code for details).

---

## About the VBLTask (VBL Interrupt Task)

On a classic Mac, screen drawing and timing can be precisely tied to the screen's refresh rate—the **vertical blanking interval** (VBL), which occurs every 1/60th of a second (for 60 Hz displays).

This program installs a custom **VBLTask**: a handler that runs at every VBL interrupt, simply incrementing a counter (`robVBLCount`). This allows the program to synchronize flashes and delays with exact screen refresh timing—avoiding drift that might confuse R.O.B.

Relevant code excerpt:
```c
volatile unsigned long robVBLCount = 0;

pascal void RobVBLProc() {
    ++robVBLCount;
}
struct VBLTask RobVBLTask = { NULL, 1, (VBLProcPtr)RobVBLProc, 0 };

void installVBLTask(void) { ... }
void removeVBLTask(void) { ... }
```
The program can then call `waitVBLank()` to wait for the next refresh before sending a pattern, guaranteeing stable timing for R.O.B.'s sensor.

---

## Why use `Delay()` and not `Microseconds()` or tight loops?

R.O.B. was designed for the reliable but *low-precision* timing of home game consoles and TVs. The Mac's `Delay()` routine is tied to VBL (every 1/60th of a second), so it provides **stable and accurate enough intervals** for generating the required signals.

- `Microseconds()` is available on some Macs, but can be unreliable or unavailable, especially on early systems and under certain conditions (interrupts, low-level code).
- The CRT's refresh—not just CPU speed—dictates what R.O.B. "sees." Using `Delay()` and synchronizing with VBL reduces the risk of misaligned flashes that R.O.B. might miss.

So, `Delay()` and VBL syncing together guarantee the right signal—**timing as robust as the old NES!**

---

## Building the Program

### Requirements

- A vintage Macintosh computer (68k processor; e.g., Macintosh Classic II or compatible) with a CRT display
- **Think C 5.0** development environment

### Build Instructions

1. Create a new project in Think C 5.0.
2. Add these files to your project:
    - `main.c` (from this repository)
    - `Mac #includes.c`
    - `MacTraps`
    - `MacTraps2`
3. Make sure your project type is set to **Application**.
4. Build and run.

### Running

1. Place your R.O.B. in front of your Macintosh's CRT display.
2. Launch the application.
3. Use your keyboard (see above) to send commands!
4. Enjoy real robot fun on real vintage hardware.

---

Enjoy making your Mac and your Robot work together—just like in the '80s, but with even more style! 🤖🍏

