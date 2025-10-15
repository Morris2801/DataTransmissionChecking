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
    if(m == 0) return 0; // Si el patron es vacio, se encuentra en la posicion 0

    // Preprocesamiento
    vector<int> lps(m, 0);  // Longest Proper Prefix which is also Suffix
    for(int i = 1, len = 0; i < m; ){
        if(P[i] == P[len]){
            lps[i++] = ++len;
        } else if(len){
            len = lps[len-1];
        } else {
            lps[i++] = 0;
        }
    }
    // AlgoritmoFull
    int i = 0; // index para  T
    int j = 0;     // index para P
    while (i < n) {
        if (P[j] == T[i]) {
            i++;
            j++;
        }
        if (j == m) {
            // Patrón encontrado en índice (i - j)
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

    // funcion agregada para obtener las posiciones del palindromo mas largo - LE
    pair<int, int> getLongestPalindrome() {
        int maxLen = 0, centerIndex = 0;
        for (int i = 1; i < (int)p.size() - 1; i++) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                centerIndex = i;
            }
        }
        int start = (centerIndex - maxLen) / 2; // traducir a indice en el string original
        return {start + 1, start + maxLen}; // devolver posiciones
    }
};



vector<int> arregloSufijos(string T){ // De la clase de Victor, este es mío
    int n = T.length();
    vector<string> sufijos;
    for (int i = n; i >= 0; i--){
        sufijos.push_back(T.substr(i, n-i));
    }
    sort(sufijos.begin(), sufijos.end()); //O(n log n) en teoría
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


// programacion dinamica para encontrar el substring comun mas largo
// Libro p.237 - 240  Aplicacion de tecnicas de diseno
// adaptado para que devuelva dos valores
pair<int,int> longestCommonSubString(string A, string B){
    //incializar una matriz LCS de tamano, longitud del string 1 por la longitud del string 2 una matriz de filas A y columnas B
    int n = A.size();
    int m = B.size();
    vector<vector<int>> LCS(n, vector<int>(m, 0));
    int maxLen = 0;
    int endPos;

    for(int i=0; i<n; i++){
        // preguntamos el caracter del string A en la posicion i es igual al caracter del string B en 0
        if(A[i] == B[0]){
            // si, si entonces asignamos 1 en la posicion i,0 de la matriz, marcanos primera columna
            LCS[i][0] = 1;
            maxLen = 1;
        }
        else{
            LCS[i][0] = 0;
        }
    }
    for (int j =0; j<m; j++){
        if(A[0]==B[j]){
            //marcamos la primera fila
            LCS[0][j] =1;
            maxLen = max(maxLen,1);
        }
        else{
            LCS[0][j] =0;
        }
    }
    for (int i = 1; i<n; i++){ // O(n*m) for anidados
        for(int j=1; j<m; j++){
            if(A[i] == B[j]){

                // si los caracteres coinciden extendemos el subString
                LCS[i][j] = LCS[i-1][j-1] + 1; //usamos la diagornal ya calculada y como esa digaonal ya tiene un valor le sumanos 1 a la posicon actual
                if(LCS[i][j] >maxLen ){
                    maxLen = LCS[i][j]; //actualizamos el maximo
                    endPos = i; //guardamos donde termina el primer string A
                }
            }
            else LCS [i][j] = 0;
        }
    }

    //caulcar posiciones
    int startPos = endPos -maxLen+1;
    return  {startPos+1 , endPos+1};
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
    string transmission2 = "";
    while(getline(file, line)){ //O(n)
        transmission2 += line;
    }
    file.close();  
    cout << transmission2 << endl;
    file.open("mcode1.txt");
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
    string mcode3 = "";
    while(getline(file, line)){ //O(n)
        mcode3 += line;
    }
    file.close();  
    cout << mcode3 << endl;

    //--------------------Resultados
    cout << "parte 1" << endl; 
    //Tómenla por buena que no me aventé unos ifs asquerosos jajaja
    // corregí lo de que el ternario KMP devuelve -1 si no se encontró el patrón - LE
    int pos;
    pos = KnuthMorrisPratt(transmission1, mcode1);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;
    pos = KnuthMorrisPratt(transmission1, mcode2);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;
    pos = KnuthMorrisPratt(transmission1, mcode3);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;
    pos = KnuthMorrisPratt(transmission2, mcode1);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;
    pos = KnuthMorrisPratt(transmission2, mcode2);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;
    pos = KnuthMorrisPratt(transmission2, mcode3);
    cout << ((pos >= 0) ? ("true " + to_string(pos + 1)) : "false") << endl;

    cout << "\nparte 2" << endl; //llamen a Manacher modificado
    // aqui ya se llamo al Manacher (no supe si por modificado era cambiar todo para que no fuera el de G4G) y llame a la func que hice del palindromo - LE
    {
        Manacher M1(transmission1);
        auto pal1 = M1.getLongestPalindrome();
        cout << pal1.first << " " << pal1.second << endl;

        Manacher M2(transmission2);
        auto pal2 = M2.getLongestPalindrome();
        cout << pal2.first << " " << pal2.second << endl;
    }

    cout << "parte 3" << endl; //llamen a mi función mágica (chance la tengan que adaptar)
    // posInit posFin (substring común más largo entre trnsmssn)
    
    pair<int, int> lcs = longestCommonSubString(transmission1, transmission2);
    cout << lcs.first << " " << lcs.second <<endl;
    return 0;
}