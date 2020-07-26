#include <iostream>
#include <cstdio>
using namespace std;

void evolution(int n, int m, int *world) {
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

void draw(int n, int m, int *world) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << (*(world + i*m + j) ? "*" : ".");
		printf("\n");
	}
    printf("\n");
}

bool isEqual(int *arr1, int *arr2, int n, int m) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(*(arr1 + m * i + j) != *(arr2 + m * i + j))
                return false;
    return true;
}

bool check(string str, int *final, int l, int n, int m) {
    int oneCntF = 0, oneCntT = 0;
    for(int i = 0; i < n * m; i++)
        if(*(final + i) == 1) oneCntF++;
    int temp1[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            temp1[i][j] = str[m * i + j] - 48;
            if(temp1[i][j] == 1) oneCntT++;
        }
    
    if(oneCntF - 2 > oneCntT || oneCntT > oneCntF + 3) return false;
    
    int temp2[n][m] = {};
    for(int i = 0; i < l; i++) {
        evolution(n, m, temp1[0]);
        if(isEqual(temp1[0], temp2[0], n, m) && !isEqual(temp1[0], final, n, m)) 
            return false;
        for(int x = 0; x < n; x++)
            for(int y = 0; y < m; y++)
                temp2[x][y] = temp1[x][y];
    }   
    if(!isEqual(final, temp1[0], n, m))
        return false;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            temp1[i][j] = str[m * i + j] - 48;
    draw(n, m, temp1[0]);
    exit(0);
}

void printAllKLengthRec(char set[], string prefix, int n, int k, int m, int l, int nn, int *final) {
    if (k == 0) { 
        check(prefix, final, l, nn, m);
        return;
    }
    for (int i = 0; i < n; i++) { 
        string newPrefix; 
        newPrefix = prefix + set[i]; 
        printAllKLengthRec(set, newPrefix, n, k - 1, m, l, nn, final); 
    } 
}




int main() {
	int n, m, l;
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
    char set[] = {'0', '1'};
    printAllKLengthRec(set, "", 2, n * m, m, l, n, final[0]);
    cout << "impossible" << endl;
	return 0;
}
