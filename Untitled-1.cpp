#include <iostream>
#include <time.h>
using namespace std;

bool defesenve_futive(int w) { 
            return (rand() % w) < 2; 
        }

int main(){
    srand(time(NULL));
    for(int i=0; i < 10; i++) cout << defesenve_futive(4) << "\n";

}

