#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// Función para verificar si un carácter es una vocal
bool is_vowel(char ch) {
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

// Función para invertir una cadena
void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        swap(str[i], str[len - i - 1]);
    }
}

// Función para limpiar una cadena, eliminando caracteres no alfabéticos ni espacios
void sanitize_string(char* dst, const char* src) {
    while (*src) {
        if (isalpha(*src) || isspace(*src)) {
            *dst++ = *src;
        }
        ++src;
    }
    *dst = '\0';
}

// Función para contar vocales, consonantes y el número de cada vocal
void count_letters(const char* str, int& vowel_count, int& consonant_count, int vowel_counts[5]) {
    vowel_count = consonant_count = 0;
    memset(vowel_counts, 0, 5 * sizeof(int)); // Inicializa el conteo de vocales a 0

    while (*str) {
        if (isalpha(*str)) {
            char lower = tolower(*str);
            if (is_vowel(lower)) {
                ++vowel_count;
                switch (lower) {
                    case 'a': ++vowel_counts[0]; break;
                    case 'e': ++vowel_counts[1]; break;
                    case 'i': ++vowel_counts[2]; break;
                    case 'o': ++vowel_counts[3]; break;
                    case 'u': ++vowel_counts[4]; break;
                }
            } else {
                ++consonant_count;
            }
        }
        ++str;
    }
}

// Función para reemplazar espacios en blanco por guiones bajos
void replace_spaces(char* str) {
    while (*str) {
        if (*str == ' ') *str = '_';
        ++str;
    }
}

int main(int argc, char* argv[]) {
    // Verifica si se proporcionó un argumento
    if (argc < 2) {
        cout << "Por favor, proporciona una cadena como argumento al ejecutar el programa." << endl;
        return 1;
    }

    const int MAX_LEN = 100;
    char original[MAX_LEN + 1];
    char cleaned[MAX_LEN + 1];
    
    // Copia la cadena de entrada y asegura que no exceda el tamaño máximo
    strncpy(original, argv[1], MAX_LEN);
    original[MAX_LEN] = '\0';

    // Limpia y procesa la cadena
    sanitize_string(cleaned, original);
    reverse_string(cleaned);

    int vowels = 0, consonants = 0;
    int vowel_counts[5] = {0}; // Para contar 'a', 'e', 'i', 'o', 'u'
    count_letters(cleaned, vowels, consonants, vowel_counts);

    char modified[MAX_LEN + 1];
    strncpy(modified, cleaned, MAX_LEN);
    modified[MAX_LEN] = '\0';
    replace_spaces(modified);

    // Imprime la cadena procesada
    cout << cleaned << " ";

    // Imprime el conteo total de vocales
    if (vowels > 0) cout << vowels << " ";

    // Imprime el conteo de vocales individuales si no son 0
    const char* vowels_list = "aeiou";
    for (int i = 0; i < 5; ++i) {
        if (vowel_counts[i] > 0) {
            cout << vowel_counts[i] << " ";
        }
    }

    // Imprime el conteo total de consonantes
    if (consonants > 0) cout << consonants << " ";

    // Imprime la cadena modificada con espacios reemplazados
    cout << modified << endl;

    return 0;
}