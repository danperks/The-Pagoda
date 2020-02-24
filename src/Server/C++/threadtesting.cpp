#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#include <iostream>
#include <thread>

using namespace std;





int main(){
    thread t1 (function1);
    thread t2 (function2);
    thread t3 (function3);
    t1.join();
    t2.join();
    t3.join();
    system("pause");
    return 0;

}
void function1(){
    cout<<"this is function1"<<endl;

}
void function2(){
    cout<<"ths is function2"<<endl;
}

void function3(){
    cout<<"this is function3"<<endl;
}