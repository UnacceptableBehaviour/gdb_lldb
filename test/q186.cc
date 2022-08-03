// compile with - C++17
//
// g++ -v -Wall -Weffc++ -std=c++17 test_c++.cc -o test_c++
// -v 		    verbose show commands issued by compiler / linker
// -Wall 	    show c++ related warnnings
// -Weff++ 	  warning generated by code that breaks coding advice in Effective C++ - S.Meyers   
// -g  		    include debugger information
// -std=c++17 __cplusplus=201703 => C++ Standard=C++17

// GDB-LLDB command map - https://lldb.llvm.org/use/map.html
// Intro LLDB - https://towardsdatascience.com/an-introduction-to-debugging-in-c-and-lldb-part-i-e3c51991f83a
// LLDB command format - <noun> <verb> [-options [option-value]] [argument [argument...]]
//						  |		  |
//	target (thread, frame etc)	  |
//							   command
//
// (lldb) breakpoint set -l 39					# set BP at line 39
// (lldb) settings show target.run-args			# show args passed in to start
// target.run-args (array of strings) =
//   [0]: "turkey"
//   [1]: "cruffins"
// (lldb) thread step-in 						# step in
// (lldb) step 
// (lldb) s
// (lldb) thread step-over 						# step over
// (lldb) next 
// (lldb) n 
// (lldb) thread step-out 						# step out of current frame
// (lldb) finish 
// (lldb) breakpoint set --name main 			# set BP function main
// (lldb) br s -n main 
// (lldb) b main
// (lldb) breakpoint list 						# list BPs
// (lldb) br l
// (lldb) breakpoint delete 1 					# del BP
// (lldb) br del 1
// 												# set BP in FILE at LINE no.
// (lldb) breakpoint set --file test.c --line 12 		
// (lldb) br s -f test.c -l 12 
// (lldb) b test.c:12
// 												# conditional BP
// (lldb) breakpoint set --name foo --condition '(int)strcmp(y,"hello") == 0' 
// (lldb) br s -n foo -c '(int)strcmp(y,"hello") == 0'
											

// quick note about python2 - err WTF? yep . .
// https://www.legendiary.at/2016/11/27/lldb-nameerror-name-run_one_line-is-not-defined/
// and a fix: https://github.com/Homebrew/homebrew-core/issues/2730
// quick answer its a python dependency issue
// easy fix: $ python3 -m venv venv											# create clean environment
//           $ . venv/bin/activate											# activate it
//           $ g++ -v -Wall -Weffc++ -g null_ref.cc interface_demo.cc -o null_ref	# compile c++
//           $ lldb null_ref turkey cruffins								# fire up debugger w/ args
//           (lldb) run 													# execute
//           Process 29761 launched: '/Users/simon/a_syllabus/lang/c++/
//           compile_hello_world_refs_pointers/null_ref' (x86_64)


//#include<cassert>
//#include<iostream>
//using namespace std;
//
//#include"interface_demo.h"
//
//
//unsigned int read_io_pin_00 (void) {
//	volatile int port_pins = 0x50;		// simulate a port read
//										
//	return port_pins & 0x01;	
//}
//
//// call_stack(5) to create a 5 frame call stack
//// set BP on new_depths = 0xFF0
//int call_stack(int deep, int how_deep = 0){
//	
//	volatile long int new_depths = 0xFF << how_deep;
//	
//	cout << new_depths << endl;
//	
//	if (how_deep <= deep)
//		call_stack(deep, how_deep+1);
//	
//	return 0; 
//}

// std::cout << a << b << '\n';
// std::cout << n << ", " << n << ", " << n << ", " << n << ", " << " \n";
#include <iostream>
//#include <string>
//#include <algorithm>  // std::find, std::for_each

void p(int v, std::string msg=""){
    std::cout << msg << ": " << v << " \n";  
}

//#include <vector>
//void pv(std::vector<int> v, std::string msg=""){
//    std::cout << msg << ": " << "v = { ";
//    for (int n : v) {
//        std::cout << n << " ";
//    }
//    std::cout << "}; \n";  
//}

// https://cppquiz.org/
// q168.cc

#include <typeinfo>

// PASSED IN array converted to a prvalue (temporary) of type "pointer to int" IE int*
void takes_pointer(int* pointer) {
  if (typeid(pointer) == typeid(int[])) std::cout << 'a';
  if (typeid(pointer) == typeid(int*)) std::cout << 'p';
}

// in compiler F() SIGNATURE "array of T" (...) is adjusted to be "pointer to T" IE int*
void takes_array(int array[]) {
  if (typeid(array) == typeid(int[])) std::cout << 'a';
  if (typeid(array) == typeid(int*)) std::cout << 'p';
}

int main() {
  int* pointer = nullptr; // pointer type int* named pointer assigned 0x0
  int array[1];           // array definition array of 1 int, array of size 1 type int named array
                          // more generally array of N T  (N=size T=type)

  takes_pointer(array);   // p  PASSED IN array converted to a prvalue (temporary) of type "pointer to int"
  takes_array(pointer);   // p  IN F() SIGNATURE "array of T" (...) is adjusted to be "pointer to T" IE int*

  std::cout << (typeid(int*) == typeid(int[])); // 0 - false
  //std::cout << typeid(int*); // error: invalid operands to binary expression ('std::__1::ostream' (aka 'basic_ostream<char>') and 'const std::type_info')
}
// o/p
// pp0



// Functions taking pointers can also be called with arrays, and vice versa.
// So are arrays and pointers the same? NO.
// 
// If they aren't the same, why can both functions be called with both arguments?
// 
// == takes_pointer(array);
// First let's look at takes_pointer(array);. What happens here is usually referred to as the array "decaying" to a pointer. To be a bit more precise, let's have a look at §[conv.array] in the C++ standard:
// 
// "An lvalue or rvalue of type “array of N T” or “array of unknown bound of T” can be converted to a prvalue of type “pointer to T”."
// 
// array is of type "array of 1 int", which converts to a prvalue (temporary) of type "pointer to int".
// 
// == takes_array(pointer);
// So what happens with takes_array(pointer);, does the pointer convert to an array?
// No, it's actually the other way around. Let's look at §[dcl.fct]¶5 about function parameters:
// 
// "After determining the type of each parameter, any parameter of type “array of T” (...) is
// adjusted to be “pointer to T”".
// 
// So in void takes_array(int array[]), the type of array is adjusted to be pointer to int.