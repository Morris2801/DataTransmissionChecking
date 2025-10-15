#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


//KnuthMorrisPratt O(n + m) para encontrar patrón P en texto T ----Geeks4Geeks y yo
int KnuthMorrisPratt(string T, string P){
    int n = T.length(), m = P.length();
    // Preprocesamiento
    vector<int> lps(m, 0);  // Longest Proper Prefix which is also Suffix
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && P[i] != P[j]) {
            j = lps[j - 1];
        }
        if (P[i] == P[j]) {
            j++;
        }
        lps[i] = j;
    }
    // AlgoritmoFull
    int i = 0; // index para  T
    j = 0;     // index para P
    while (i < n) {
        if (P[j] == T[i]) {
            i++;
            j++;
        }
        if (j == m) {
            // Patrón encontrado en índice (i - j)
            cout << "Patrón encontrado en índice " << (i - j) << endl;
            j = lps[j - 1]; // Continuar buscando más ocurrencias
            return i - j;   // Devolver índice de la primera ocurrencia
        }
        else if (i < n && P[j] != T[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return -1; // Patrón no encontrado
}

class Manacher { // Geeks4Geeks y ya 
public: 
    // p[i] = radius of longest palindrome centered at i 
    // in transformed string
    vector<int> p;    
    
    // transformed string with # and sentinels
    string ms;        

    // preprocess the string and run the algorithm
    Manacher(string &s) {
        
        // left sentinel
        ms = "@"; 
        for (char c : s) {
            ms += "#" + string(1, c);
        }
        
        // right sentinel
        ms += "#$"; 

        // run Manacher’s algorithm
        runManacher();
    }

    void runManacher() {
        int n = ms.size();
        p.assign(n, 0);
        int l = 0, r = 0;

        for (int i = 1; i < n - 1; ++i) {
            
            // mirror of i around center (l + r)/2
            int mirror = l + r - i;

            // initialize p[i] based on its mirror 
            // if within bounds
            if (i < r)
                p[i] = min(r - i, p[mirror]);

            // expand palindrome centered at i
            while (ms[i + 1 + p[i]] == ms[i - 1 - p[i]]){
                ++p[i];
            }

            // update [l, r] if the palindrome expands 
            // beyond current r
            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }
    }

    // returns length of longest palindrome centered 
    // at 'cen' in original string
    // 'odd' = 1 → check for odd-length, 'odd' = 0 → even-length
    int getLongest(int cen, int odd) {
        
        // map original index to transformed string index
        int pos = 2 * cen + 2 + !odd;
        return p[pos];
    }

    // checks if s[l..r] is a palindrome in O(1)
    bool check(int l, int r) {
        int len = r - l + 1;
        int cen = (l + r) / 2;
        return len <= getLongest(cen, len % 2);
    }
};



vector<int> arregloSufijos(string T){ // De la clase de Victor, este es mío
    int n = T.length();
    vector<string> sufijos;
    for (int i = n; i >= 0; i--){
        sufijos.push_back(T.substr(i, n-i));
    }
    /*
    for (int i = 0; i < sufijos.size(); i++){
        cout << sufijos[i] << endl;
    }
    */
    sort(sufijos.begin(), sufijos.end()); //O(n log n) en teoría
    /*
    for (int i = 0; i < sufijos.size(); i++){
        cout << sufijos[i] << endl;
    }
    */
    vector<int> posiciones; 
    for (int i = 0; i < sufijos.size(); i++){
        posiciones.push_back(n - sufijos[i].length() +1);
        cout <<  sufijos[i] << " " << posiciones[i] << endl;
    }
    posiciones.erase(posiciones.begin());
    cout << "Posiciones: " << endl;
    for (int i = 0; i < posiciones.size(); i++){
        cout << posiciones[i] << " ";
    }
    cout << endl;
    return posiciones;
}







int main (){
    //-------------Extracción de texto desde archivos
    ifstream file;
    file.open("transmission1.txt");
    string line;
    string transmission1 = "";
    while(getline(file, line)){ //O(n)
        transmission1 += line;
    }
    file.close();  
    cout << transmission1 << endl;
    file.open("transmission2.txt");
    string line;
    string transmission2 = "";
    while(getline(file, line)){ //O(n)
        transmission2 += line;
    }
    file.close();  
    cout << transmission2 << endl;
    file.open("mcode1.txt");
    string line;
    string mcode1 = "";
    while(getline(file, line)){ //O(n)
        mcode1 += line;
    }
    file.close();  
    cout << mcode1 << endl;
    file.open("mcode2.txt");
    string mcode2 = "";
    while(getline(file, line)){ //O(n)
        mcode2 += line;
    }
    file.close();  
    cout << mcode2 << endl;
    file.open("mcode3.txt");
    string line; 
    string mcode3 = "";
    while(getline(file, line)){ //O(n)
        mcode3 += line;
    }
    file.close();  
    cout << mcode3 << endl;

    //--------------------Resultados

    //Parte 1: Deteccion de codigo malicioso en la transmision
    // reviar si existe algun tipo de los 3 codigos malisiosos en las 2 transmisiones
    
    cout << "parte 1" << endl; 
    //Tómenla por buena que no me aventé unos ifs asquerosos jajaja
    bool res1 = KnuthMorrisPratt(transmission1, mcode1) ? true : false;
    cout << res1 << endl;
    bool res2 = KnuthMorrisPratt(transmission1, mcode2) ? true : false;
    cout << res2 << endl;
    bool res3 = KnuthMorrisPratt(transmission1, mcode3) ? true : false;
    cout << res3 << endl;
    bool res4 = KnuthMorrisPratt(transmission2, mcode1) ? true : false;
    cout << res4 << endl;
    bool res5 = KnuthMorrisPratt(transmission2, mcode2) ? true : false;
    cout << res5 << endl;
    bool res6 = KnuthMorrisPratt(transmission2, mcode3) ? true : false;
    cout << res6 << endl;

    cout << "parte 2" << endl; //llamen a Manacher modificado 
    // posicionInicial posicionFinal (trnsmssn 1)
    // posicionInicial posicionFinal (trnsmssn 2)

    cout << "parte 3" << endl; //llamen a mi función mágica (chance la tengan que adaptar)
    // posInit posFin (substring común más largo entre trnsmssn)

    
    
    return 0;
}