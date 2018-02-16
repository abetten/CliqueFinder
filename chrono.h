/* 
 * File:   chrono.h
 * Author: Sajeeb
 *
 * Created on October 26, 2017, 5:02 PM
 */

/*
    Description:
        This is a custom chrono class used to measure the amount of time a
	particular operation, or a particular statement took to complete.
	The amount of time it took an operation or a series of operations
	to complete can be found out by wrapping the operation or the series
	of operations with the chrono class. In other words calling the
	reset_duration() of the chrono object before the start of the
	operation(s) and doing the following right after the operation 
	statements: 

		cout<< "Operation(s) Took: " << chrono_object.calculateDuration();
	
	Every time the above statement is called the clock in the chrono class
	is reset from the creation of the chrono object to the time of calling 
	the above statement. The chrono class returns the time in milliseconds.
*/


#ifndef CHRONO_H
#define CHRONO_H

#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>

using std::cout;
using std::endl;

class chrono {
public:
    chrono() {
	reset();
        if (debug) {
            cout<< "Constructor for chrono called: " << duration <<endl;
        }
    }
    ~chrono() {
        if (debug) {
            cout<< "Destructor for chrono called: " << duration <<endl;
        }
    }
    long calculateDuration() {
        long old_duration = duration;
        reset();
        return (duration-old_duration);
    }
    void reset() {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
        duration = value.count();
    }

    long duration;
private:
    static const bool debug =  false;
};

#endif /* CHRONO_H */

