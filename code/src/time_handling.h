#ifndef TIME_HANDLING_H
#define TIME_HANDLING_H

/**
 * A function to handle the fact that the timer value represented by micros() 
 * will overflow after approximately 70 minutes. We assume that time is always
 * increasing, so this function always returns a non-negative value.
*/
unsigned long time_diff(unsigned long former_time, unsigned long current_time);

#endif  // TIME_HANDLING_H