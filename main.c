/**
 *  R.O.B. Macintosh Driver
 *  -----------------------
 *  (C) 2025 Sirix1995
 *
 *  Control Nintendo's R.O.B. the Robot using a 68k Macintosh with a CRT!
 *  This driver flashes the Mac screen in patterns to command R.O.B. via its optical sensor.
 *
 *  Keyboard Controls:
 *      Arrow Keys  : Move R.O.B.'s arms (Up, Down, Left, Right)
 *      Q           : Close hands
 *      S           : Open hands
 *      T           : Switch R.O.B.'s LED on
 *      X           : Exit program
 *
 *  For use on a Macintosh Classic II or compatible system.
 *  Have fun with your robot companion!
 */

 #include <QuickDraw.h>
 #include <ToolUtils.h>
 #include <Events.h>
 #include <Retrace.h>
 
 long finalTicks;
 GrafPtr savePort, deskPort;
 volatile unsigned long robVBLCount = 0;
 
 pascal void RobVBLProc() {
	 ++robVBLCount;
 }
 
 struct VBLTask RobVBLTask = {
	 NULL, 1, (VBLProcPtr)RobVBLProc, 0
 };
 
 void installVBLTask(void) {
	 robVBLCount = 0;
	 RobVBLTask.vblCount = 1;
	 RobVBLTask.vblAddr = (VBLProcPtr)RobVBLProc;
	 RobVBLTask.vblPhase = 0;
	 VInstall((QElemPtr)&RobVBLTask);
 }
 
 void removeVBLTask(void) {
	 VRemove((QElemPtr)&RobVBLTask);
 }
 
 void waitVBLank() {
	 unsigned long lastVBL = robVBLCount;
	 long timeout = 0;
 
	 while((robVBLCount == lastVBL) && (timeout++ < 100000));
 }
 
 void setScreenWhite() {
	 FillRect(&screenBits.bounds, &qd.white);
 }
 
 void setScreenBlack() {
	 FillRect(&screenBits.bounds, &qd.black);
 }
 
 /* INIT: 00010 - Communication Initiation */
 void initCom() {
	 waitVBLank();
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
 }
 
 /* TEST: 11101011 - Turn the head LED on */
 void testCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(2, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
 }
 
 /* UP: 10111011 - Raises the body up */
 void upCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(2, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
 }
 
 /* DOWN: 11111011 - Lowers the body down */
 void downCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(5, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(2, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
 }
 
 /* LEFT: 10111010 - Turns the body left */
 void leftCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
 }
 
 /* RIGHT: 11101010 - Turns the body right */
 void rightCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
 }
 
 /* CLOSE: 10111110 - Close the arms */
 void closeCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(5, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
 }
 
 /* OPEN: 11101110 - Open the arms */
 void openCommand() {
	 initCom();
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.white);
	 Delay(3, &finalTicks);
	 FillRect(&screenBits.bounds, &qd.black);
	 Delay(1, &finalTicks);
 }
 
 /* Handle a key/arrow event and run the relevant command, returns 1 if user asked to quit */
 int handleKeyEvent(EventRecord* event) {
	 char key;
	 unsigned char keyCode;
	 key = (char)(event->message & charCodeMask);
	 keyCode = (unsigned char)((event->message & keyCodeMask) >> 8);
 
	 if (key == 'x' || key == 'X') {
		 return 1; // quit
	 } else if (key == 'q' || key == 'Q') {
		 closeCommand();
	 } else if (key == 's' || key == 'S') {
		 openCommand();
	 } else if (key == 't' || key == 'T') {
		 testCommand();
	 } else if (keyCode == 0x7E) { // Up arrow
		 upCommand();
	 } else if (keyCode == 0x7D) { // Down arrow
		 downCommand();
	 } else if (keyCode == 0x7B) { // Left arrow
		 leftCommand();
	 } else if (keyCode == 0x7C) { // Right arrow
		 rightCommand();
	 }
	 return 0;
 }
 
 int main(void) {
	 int programEnd = 0;
	 EventRecord event;
 
	 InitGraf(&qd.thePort);
	 InitWindows();
	 InitMenus();
	 InitCursor();
 
	 HideCursor();
	 GetPort(&savePort);
	 GetWMgrPort(&deskPort);
	 SetPort(deskPort);
 
	 installVBLTask();
 
	 setScreenBlack();
 
	 Delay(50, &finalTicks);
 
	 while (!programEnd) {
		 if (WaitNextEvent(everyEvent, &event, 60, NULL)) {
			 if ((event.what == keyDown) || (event.what == autoKey)) {
				 programEnd = handleKeyEvent(&event);
			 }
		 }
	 }
 
	 setScreenBlack();
	 Delay(100, &finalTicks);
	 removeVBLTask();
	 SetPort(savePort);
	 ShowCursor();
	 return 0;
 }