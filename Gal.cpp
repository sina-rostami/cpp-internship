#include <iostream>
#include <cstdio>
using namespace std;
int n, m, l;
int *finalWorld;
char set[] = {'0', '1'};

void arrCpy(int *src, int *dst) {
    for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			* (dst + i * m + j) = * (src + i * m + j);
}

void StrToArrCpy(string str, int *arr) {
    for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			* (arr + i * m + j) = str[m * i + j] - 48;
}

void evolution(int *world) {
	int newWorld[n][m];
    int lives;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			lives = 0;
			for (int i_neighbor = i - 1; i_neighbor <= i + 1; i_neighbor++)
				for (int j_neighbor = j - 1; j_neighbor <= j + 1; j_neighbor++)
                    if (* (world + (m * ((i_neighbor + n) % n)) + ((j_neighbor + m) % m ))) 
						lives++;

			if (* (world + i * m + j)) {
                lives--; 
                newWorld[i][j] = (lives == 3 || lives == 2);
            } else
                newWorld[i][j] = (lives == 3);
		}
	arrCpy(newWorld[0], world);
}

void drawWorld(int *world) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << (*(world + i*m + j) ? "*" : ".");
		printf("\n");
	}
    printf("\n");
}

bool areEqual(int *arr1, int *arr2) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(*(arr1 + m * i + j) != *(arr2 + m * i + j))
                return false;
    return true;
}

bool check(string str) {
    int onesCntFinal = 0, onesCntTemp = 0;
    int tempWrold[n][m];
    StrToArrCpy(str, tempWrold[0]);

    for(int i = 0; i < n * m; i++) {
        if(*(finalWorld + i) == 1) onesCntFinal++;
        if(*(*tempWrold + i) == 1) onesCntTemp++;
    }
    
    if(onesCntFinal - 2 > onesCntTemp || onesCntTemp > onesCntFinal + 3) 
        return false;
    
    for(int i = 0; i < l; i++)
        evolution(tempWrold[0]);

    if(!areEqual(finalWorld, tempWrold[0]) )
        return false;

    StrToArrCpy(str, tempWrold[0]);

    drawWorld(tempWrold[0]);
    exit(0);
}

void makePermutatios(string prefix, int k) {
    if (k == 0) { 
        check(prefix);
        return;
    }
    for (int i = 0; i < 2; i++) { 
        string newPrefix; 
        newPrefix = prefix + set[i]; 
        makePermutatios(newPrefix, k - 1); 
    } 
}

int main() {
    cin >> n >> m >> l;
    int final[n][m];
    string str = "";
    for(int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        str += temp;
    }
    //store input World to an array and make finalWorld point to it.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            final[i][j] = str[m * i + j] == '*' ? 1 : 0;
    finalWorld = final[0];

    makePermutatios("", n * m);
    cout << "impossible" << endl;
	return 0;
}
