#include <iostream> 

using namespace std; 
  
int main(int argc, char** argv) // argc = Number of arguments       argv = Array of pointers to str arguments 
{ 
    cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
  
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
  
    return 0; 
} 