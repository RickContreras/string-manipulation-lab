package main

import (
	"fmt"
	"os"
	"strings"
	"unicode"
)

// Índices de cada vocal para el arreglo de conteo
const (
	IndexA = iota
	IndexE
	IndexI
	IndexO
	IndexU
)

// isVowel verifica si el carácter es una vocal
func isVowel(r rune) bool {
	switch unicode.ToLower(r) {
	case 'a', 'e', 'i', 'o', 'u':
		return true
	default:
		return false
	}
}

// sanitize limpia la cadena: solo deja letras y espacios
func sanitize(s string) string {
	var builder strings.Builder
	for _, r := range s {
		if unicode.IsLetter(r) || unicode.IsSpace(r) {
			builder.WriteRune(r)
		}
	}
	return builder.String()
}

// reverse invierte una cadena de texto (maneja UTF-8)
func reverse(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

// countLetters analiza la cadena y devuelve conteos
func countLetters(s string) (vowels, consonants int, vowelCounts [5]int) {
	for _, r := range s {
		if unicode.IsLetter(r) {
			lower := unicode.ToLower(r)
			if isVowel(lower) {
				vowels++
				switch lower {
				case 'a':
					vowelCounts[IndexA]++
				case 'e':
					vowelCounts[IndexE]++
				case 'i':
					vowelCounts[IndexI]++
				case 'o':
					vowelCounts[IndexO]++
				case 'u':
					vowelCounts[IndexU]++
				}
			} else {
				consonants++
			}
		}
	}
	return
}

// replaceSpaces reemplaza espacios con guiones bajos
func replaceSpaces(s string) string {
	return strings.ReplaceAll(s, " ", "_")
}

// buildOutput construye el string de salida final
func buildOutput(cleaned string, vowels, consonants int, vowelCounts [5]int, modified string) string {
	var builder strings.Builder

	builder.WriteString(cleaned)

	if vowels > 0 {
		builder.WriteString(fmt.Sprintf(" %d", vowels))
	}
	for _, count := range vowelCounts {
		if count > 0 {
			builder.WriteString(fmt.Sprintf(" %d", count))
		}
	}
	if consonants > 0 {
		builder.WriteString(fmt.Sprintf(" %d", consonants))
	}
	builder.WriteString(" " + modified)

	return builder.String()
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Por favor, proporciona una cadena como argumento al ejecutar el programa.")
		return
	}

	// Entrada y preprocesamiento
	input := os.Args[1]
	sanitized := sanitize(input)
	reversed := reverse(sanitized)

	// Conteos y transformación
	vowels, consonants, vowelCounts := countLetters(reversed)
	modified := replaceSpaces(reversed)

	// Construcción e impresión del resultado
	result := buildOutput(reversed, vowels, consonants, vowelCounts, modified)
	fmt.Println(result)
}