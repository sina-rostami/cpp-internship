#include <iostream>
#include <cstdio>
using namespace std;
#define length(x) sizeof(x)/sizeof(int)
int n, m, l;
int *finalWorld;

void evolution(int *world) {
	int temp[n][m];
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++) {
			int lives = 0;
			for (int xd = x - 1; xd <= x + 1; xd++)
				for (int yd = y - 1; yd <= y + 1; yd++) {
                    if (* (world + (m * ((xd + n) % n)) + ((yd + m) % m )))  // * (world + (m * ((xd + n) % n)) + ((yd + m) % m ))
						lives++;
                }
					
			if (* (world + x * m + y)) {
                lives--; 
                temp[x][y] = (lives==3 || lives==2);
            } else {
                temp[x][y] = lives == 3;
            }
			

		}
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++)
			* (world + x * m + y) = temp[x][y];
}

void draw(int *world) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << (*(world + i*m + j) ? "*" : ".");
		printf("\n");
	}
    printf("\n");
}

bool isEqual(int *arr1, int *arr2) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(*(arr1 + m * i + j) != *(arr2 + m * i + j))
                return false;
    return true;
}

bool check(string str) {
    int onesCntFinal = 0, onesCntTemp = 0;

    for(int i = 0; i < n * m; i++)
        if(*(finalWorld + i) == 1) onesCntFinal++;
    
    int tempWrold[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            tempWrold[i][j] = str[m * i + j] - 48;
            if(tempWrold[i][j] == 1) onesCntTemp++;
        }
    
    if(onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3) 
        return false;
    
    for(int i = 0; i < l; i++)
        evolution(tempWrold[0]);

    if(!isEqual(finalWorld, tempWrold[0]) )
        return false;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            tempWrold[i][j] = str[m * i + j] - 48;
    draw(tempWrold[0]);
    exit(0);
}

void printAllKLengthRec(char set[], string prefix, int k) {
    if (k == 0) { 
        check(prefix);
        return;
    }
    for (int i = 0; i < 2; i++) { 
        string newPrefix; 
        newPrefix = prefix + set[i]; 
        printAllKLengthRec(set, newPrefix, k - 1); 
    } 
}

int main() {
    cin >> n >> m >> l;
    string str = "";
    for(int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        str += temp;
    }
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '*') 
            str.replace(i, 1, "1");
        else
            str.replace(i, 1, "0");
    }
    int final[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            final[i][j] = str[m * i + j] - 48;
    finalWorld = final[0];




    char set[] = {'0', '1'};
    printAllKLengthRec(set, "", n * m);
    cout << "impossible" << endl;
	return 0;
}
