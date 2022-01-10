
#include <string>
#include <iostream> 
#include <fstream>
#include <Windows.h>

int main() {
    string content;
    fstream file;
    string var_1 = "zk~blcdnox";
	char *var_2;

    if (IsDebuggerPresent())
    {
        printf("Nope");
        return 1;
    }

    
	for (int cnt = 0; cnt < var_1.size(); cnt++) {
		var_1[cnt] = var_1[cnt] ^ 10;
	}

	file.open("test.txt");
	if (!file) 
	{
		printf("Bad1");
		return 1;
	}
    file >> content;

	if(content == var_1)
	{
		printf("Good job!\n");
		return 0;
	} else {
		printf("Bad2");
		return 1;
	}
}
