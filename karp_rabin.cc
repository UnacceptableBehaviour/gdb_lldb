
// compiler ERROR: karp_rabin.cc:62:10: fatal error: 'bits/stdc++.h' file not found
// to get this to compile - on OSX
// git clone https://gist.github.com/frankchen0130/9ac562b55fa7e03689bca30d0e52b0e5
// create bits dirctory here
// /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/bits/stdc++.h
// copy /stdc++.h into bits
// $  g++ -v -Wall -Weffc++ -g karp_rabin.cc -o k_r
// ./k_r
// $ Pattern found at index 0
// $ Pattern found at index 10

/* Following program is a C++ implementation of Rabin Karp 
Algorithm given in the CLRS book */
#include <bits/stdc++.h> 
using namespace std; 

// d is the number of characters in the input alphabet 
#define d 256 

/* pat -> pattern 
	txt -> text 
	q -> A prime number 
*/
void search(char pat[], char txt[], int q) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 
	int i, j; 
	int p = 0; // hash value for pattern 
	int t = 0; // hash value for txt 
	int h = 1; 

	// The value of h would be "pow(d, M-1)%q" 
	for (i = 0; i < M - 1; i++) 
		h = (h * d) % q; 

	// Calculate the hash value of pattern and first 
	// window of text 
	for (i = 0; i < M; i++) 
	{ 
		p = (d * p + pat[i]) % q; 
		t = (d * t + txt[i]) % q; 
	} 

	// Slide the pattern over text one by one 
	for (i = 0; i <= N - M; i++) 
	{ 

		// Check the hash values of current window of text 
		// and pattern. If the hash values match then only 
		// check for characters on by one 
		if ( p == t ) 
		{ 
			/* Check for characters one by one */
			for (j = 0; j < M; j++) 
			{ 
				if (txt[i+j] != pat[j]) 
					break; 
			} 

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			if (j == M) 
				cout<<"Pattern found at index "<< i<<endl; 
		} 

		// Calculate hash value for next window of text: Remove 
		// leading digit, add trailing digit 
		if ( i < N-M ) 
		{ 
			t = (d*(t - txt[i]*h) + txt[i+M])%q; 

			// We might get negative value of t, converting it 
			// to positive 
			if (t < 0) 
			t = (t + q); 
		} 
	} 
} 

/* Driver code */
int main() 
{ 
	char txt[] = "GEEKS FOR GEEKS"; 
	char pat[] = "GEEK"; 
	int q = 101; // A prime number 
	search(pat, txt, q); 
	return 0; 
} 

// This is code is contributed by rathbhupendra 
// https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/


//  - - - Example from code above
// $ lldb null_ref turkey cruffins
// (lldb) target create "null_ref"
// Current executable set to 'null_ref' (x86_64).
// (lldb) settings set -- target.run-args  "turkey" "cruffins"
// 
// --# set break point at apex of recursive call
// (lldb) breakpoint set --file null_ref.cc --line 78
// Breakpoint 1: where = null_ref`call_stack(int, int) + 64 at null_ref.cc:78, address = 0x0000000100000b70
// 
// --# run the code
// (lldb) run
// Process 30002 launched: '/lang/c++/compile_hello_world_refs_pointers/null_ref' (x86_64)
// Re-Hello World
// 30
//
// 30
// 
// Num args:3
// 
// /Users/simon/a_syllabus/lang/c++/compile_hello_world_refs_pointers/null_ref
// 
// turkey
// 
// cruffins
// 
// Number of Observers = 0
// PIN 00: 0 <
// PIN 00: 0 <
// Process 30002 stopped
// * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
//     frame #0: 0x0000000100000b70 null_ref`call_stack(deep=5, how_deep=6) at null_ref.cc:78
//    75  		if (how_deep <= deep)
//    76  			call_stack(deep, how_deep+1);
//    77  		
// -> 78  		return 0; 				# line 80 after cout added		< BP
//    79  	}
//    80  	
//    81  	int main(int argc, char* argv[]) {
// Target 0: (null_ref) stopped.
// (lldb) 
// (lldb) thread backtrace -c 9
// * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
//   * frame #0: 0x0000000100000b70 null_ref`call_stack(deep=5, how_deep=6) at null_ref.cc:78
//     frame #1: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=5) at null_ref.cc:76
//     frame #2: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=4) at null_ref.cc:76
//     frame #3: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=3) at null_ref.cc:76
//     frame #4: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=2) at null_ref.cc:76
//     frame #5: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=1) at null_ref.cc:76
//     frame #6: 0x0000000100000b6b null_ref`call_stack(deep=5, how_deep=0) at null_ref.cc:76
//     frame #7: 0x0000000100000e9f null_ref`main(argc=3, argv=0x00007fff5fbff490) at null_ref.cc:107
//     frame #8: 0x00007fffd5d52235 libdyld.dylib`start + 1
   
   
   