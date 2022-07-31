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
#include <string>
#include <algorithm>  // std::find, std::for_each

// q114.cc
#include <memory>
#include <vector>   // https://en.cppreference.com/w/cpp/container/vector

class C {
public:
  void foo()       { std::cout << "A"; }
  void foo() const { std::cout << "B"; }
};

struct S {
  std::vector<C> v;
  std::unique_ptr<C> u;   // object this points to deleted when this goes out of scope, is reset, or re-assigned
  C *const p;             // constant pointer to type C

  S() 
    : v(1)         // std::vector<int> v (5);  // 5 default-constructed ints - v = { 0 0 0 0 0 };
    , u(new C())
    , p(u.get())   // 
  {}
};

int main() {
  S s;                // ctor   v[0] = C,  u = &C,  p = &C
  const S &r = s;     // r ref to s, r is const
 
  s.v[0].foo();       // A
  s.u->foo();         // A
  s.p->foo();         // A    pointer constant not C

  r.v[0].foo();       // B
  r.u->foo();         // A
  r.p->foo();         // A
}


// According to §[dcl.ptr]¶1 in the C++ Standard, "The cv-qualifiers [e.g., const] apply to the
// pointer and not to the object pointed to."
// 
// That is, const-ness is shallow with regards to raw pointers and references (and standard types
// that seek to emulate them, like std::unique_ptr) but not with regard to standard containers such
// as std::vector.
// 
// In the code above, the object s is non-const, and so its members all retain their default
// const-ness and all calls through them invoke the non-const version of C::foo().
// 
// However, r refers to its object as a const instance of S.
// That const-ness changes the behavior of its member v, an std::vector which is "const-correct"
// in the sense that its operator§[] returns const C& (see [sequence.reqmts]¶14) and therefore
// invokes the const version of C::foo().
// 
// The const-ness of r's referent is also propagated to its members u and p (meaning one could not
// perform a mutating operation on u, e.g., calling r.u.reset()), but this has no effect on the instance
// of C that they both point to. That is, the pointers themselves become const, but the pointed-to
// objects remain non-const. Hence, they both still call the non-const version of C::foo().
// 
// The const-ness of the member S::p is the same for both s and r. Because it is declared as a const
// pointer, it does not change const-ness to follow the const-ness of its instance of S but remains a
// const pointer to a non-const object.

// auto&&  vs   const auto&
// A "universal reference", auto&& or T&&, will bind to anything.
// https://stackoverflow.com/questions/13230480/what-does-auto-tell-us
// You might say, well why not just use a const auto& because that will also bind to anything?
// The problem with using a const reference is that it's const!
// You won't be able to later bind it to any non-const references or invoke any member functions
// that are not marked const.
//
// more on Universal Refs - Scott Myers TODO
// https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers



// vector basics
// https://www.edureka.co/blog/vectors-in-cpp/

// Member function w/ Examples
// https://cplusplus.com/reference/vector/vector/

// Implementation
// https://timsong-cpp.github.io/cppwp/n4659/vector

//void pv(std::vector<int> v, std::string msg=""){
//    std::cout << msg << ": " << "v = { ";
//    for (int n : v) {
//        std::cout << n << " ";
//    }
//    std::cout << "}; \n";  
//}
//
//void pv(std::vector<int>::iterator iv, std::vector<int>::iterator end, std::string msg=""){
//    std::cout << msg << ": " << "v = { ";
//    //for (int n : v) { // error: invalid range expression of type 'std::__1::__wrap_iter<int *>'; no viable 'begin' function available
//    for (; iv != end; iv++) {
//        std::cout << *iv << " ";
//    }
//    std::cout << "}; \n";  
//}
//
//void processItemFunc (int i){    // function
//  std::cout << " " << i;
//}
//
//struct classname {               // functor
//  void operator() (int i) {
//    std::cout << " " << i;
//  }
//} processorObj;
//
//int main()
//{
//    // curly braces for initialisation
//    int ba = 5;
//    int bra{5};   // same as prev line
//    
//    std::string stra = "String initialised W/O braces";
//    std::string strab{"String initialised w/ braces"};    // same as prev line
//    
//    std::vector<int> vv = { 7, 5, 16, 8 };
//    std::vector<int> vvb { 12, 2, 18, 4 };
//    
//    std::cout << ba << ", " << bra << ", " << stra << ", " << strab << ", "
//              << vv[0] << ", " << vvb[0] << ", " << " \n";
//
//
//
//    // std::cout << n << ", " << n << ", " << n << ", " << n << ", " << " \n";
//    std::vector<int> myvec (5);  // 5 default-constructed ints
//    pv(myvec, "myvec (5)");      // v = { 0 0 0 0 0 };
//    
//    // Create a vector containing integers
//    std::vector<int> v = { 7, 5, 16, 8, 77, -5 };
//    pv(v, "contents");
//    
//    // shift, unshift, push(push_back), pop(pop_back)
//    v.push_back(25);
//    pv(v, "push_back");
//    v.push_back(13);    
//    pv(v, "push_back");
//
//    v.pop_back();
//    pv(v, "pop_back");
//    v.pop_back();    
//    pv(v, "pop_back");
//    
//    // BETTER OFF USING DEQUE! if need shift/unshift
//    // 1st arg is an (random access iterator) iterator not an index
//    // shift
//    v.insert(v.begin(), 88);  // ** Linear complexity on the number of elements after position (moving).
//    pv(v, "shift - insert");
//    
//    // shift
//    // emplace can construct a vector element based on args
//    v.emplace(v.begin(), 99);  // ** Linear complexity on the number of elements after position (moving).
//    pv(v, "shift - emplace");
//    
//    // unshift
//    
//    
//    // find unique - #include <algorithm> std::find(iter.begin, iter.end, target) return iter to target or iter.end
//    // unless vector is sorted find checks all locations - slow
//    // https://stackoverflow.com/questions/571394/how-to-find-out-if-an-item-is-present-in-a-stdvector
//    // suggest map or hash_set
//    // find 7 in vector
//    int target = 7;
//    if ( std::find(v.begin(), v.end() , target) != v.end() )
//      std::cout << "Found " << target << '\n';
//    else
//      std::cout << target << " NOT Found " << '\n';
//
//    std::vector<int>::iterator itag = std::find(v.begin(), v.end() , target);      
//    if ( itag != v.end() )
//      // int index = itag - v.begin(); // this arithmatic doesn't appear to return int - returns iterator
//      // std::cout << "Found " << target << " at index " << index << " content="<< *itag << " or " << v[index] <<'\n';      
//      std::cout << "Found " << target << " at index " << itag - v.begin() << " content="<< *itag << " or " << v[itag - v.begin()] <<'\n';
//    else
//      std::cout << target << " NOT Found " << '\n';
//    
//    
//    // find multiple - see for_each
//    
//    
//    // splice
//    pv(v, "slice vector untouched: ");
//    std::vector<int> v2 = std::vector<int>(v.begin() + 1, v.begin() + 5); // doesn't include last pos!
//    pv(v2, "slice vector 1-4: ");
//    
//    // - - - scanning
//    // using index
//    std::cout << "GOF for loop - v contains: ";
//    for (int i=0; i < v.size(); i++)
//      std::cout << v[i] << ' ';
//    std::cout << '\n';
//    
//    // iterating
//    std::vector vtr = {'A', 'B', 'C', 'D', 'E'};
//    //for (std::vector::iterator it=vtr.begin(); it != vtr.end(); it++) // error: 'vector' is not a class, namespace, or enumeration
//    //for (std::vector<int>::iterator it=vtr.begin(); it != vtr.end(); it++) // error: no viable conversion from '__wrap_iter<std::__1::vector<char, std::__1::allocator<char> >::pointer>' to '__wrap_iter<std::__1::vector<int, std::__1::allocator<int> >::pointer>'
//    for (std::vector<char>::iterator it=vtr.begin(); it != vtr.end(); it++)  // OK - char not int
//    //for (auto it=vtr.begin(); it != vtr.end(); it++) // OK
//        std::cout << *it << ' ';
//    std::cout << std::endl;    
//
//    // neater
//    std::cout << "v contains:";
//    for (auto& x: vtr)    // range notation
//      std::cout << ' ' << x;
//    std::cout << '\n';    
//    
//    
//    // for_each(v.begin(), v.end(), func/method)    #include <algorithm> std::for_each
//    std::cout << "for_each function call:";
//    std::for_each(v.begin(), v.end(), processItemFunc);
//    std::cout << '\n';    
//
//    std::cout << "for_each function object call:";
//    std::for_each(v.begin(), v.end(), processorObj);
//    std::cout << '\n';    
//
//    
//    // REVERSE iterating
//    std::cout << "reverse:";
//    std::vector<int>::reverse_iterator rit;// = v.rbegin();
//    for (rit = v.rbegin(); rit!= v.rend(); ++rit)  // v.end()
//      std::cout << ' ' << *rit;
//    std::cout << '\n';
//    
//    //if (v.rbegin() == v.end()) std::cout << "v.rbegin() == v.end()" << std::endl;
//    
//    //std::vector<int>::iterator rit = v.rbegin();
//    //pv(rit);
//    pv(v, "pv forward");
//    pv(v.begin(), v.end(), "iterator f()");
//      
//    //std::cout << "reverse:";
//    //std::vector<int>::reverse_iterator rit2 = v.rbegin();
//    //for (rit2 = v.end(); rit2!= v.begin()-1; --rit)
//    //  std::cout << ' ' << *rit;
//
//    
//    //for (std::vector<char>::iterator it=x.rend(): vtr) // nope
//    ////for (std::vector<char>::iterator x.rend(); it != vtr.end(); it++)
//    //  std::cout << ' ' << x;
//    //std::cout << '\n';      
//    
//}
//
