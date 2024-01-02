/*package main

import (
	"fmt"
	"strings"
	"unicode/utf8"
)

func isHebrew(r rune) bool {
	a := "א"

	t := "ת"

	return r >= rune(a[0]) && r <= rune(t[0])
}

func reverseHebrewWords(input string) string {
	words := strings.Fields(input) // Split string into words

	for i, word := range words {
		runes := []rune(word)
		reversed := make([]rune, 0, len(runes))
		if isHebrew(rune(word[0])) {

			fmt.Println("Is hebrew checking")
			// Reverse Hebrew word
			for i := len(runes) - 1; i >= 0; i-- {
				if isHebrew(runes[i]) {
					reversed = append(reversed, runes[i])
				}
			}

		}
		words[i] = string(reversed)
	}

	return strings.Join(words, " ") // Reconstruct the string with reversed Hebrew words
}

func main() {
	input := "הפלחה-'חא תלד ש''מק 5 םותסש םימותסש סיסב תטלפ ה''ופ הנכוב עורז ה''ופ :ללוכ םילפינ+ םותסש תפלחה"
	fmt.Println(input)
	fmt.Println(utf8.ValidString(input))
	reversed := reverseHebrewWords(input)
	fmt.Println(utf8.ValidString(reversed))
	fmt.Println(reversed)
}*/

package main

import (
	"fmt"
	"strings"
	"unicode"
)

func reverseHebrewWords(s string) string {
	words := strings.Fields(s)
	sentense := make([]string, len(words))
	engSentense := make([]string, len(words))
	for i, word := range words {
		runes := []rune(word)
		if unicode.Is(unicode.Hebrew, runes[0]) && !unicode.IsPunct(runes[0]) {
			for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
				runes[i], runes[j] = runes[j], runes[i]
			}
			words[i] = string(runes)
		} else if len(runes) > 1 {
			if unicode.Is(unicode.Hebrew, runes[1]) && !unicode.IsPunct(runes[1]) {
				for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
					runes[i], runes[j] = runes[j], runes[i]
				}
				words[i] = string(runes)
			}
		}

	}
	for i, j, k := 0, len(words)-1, 0; i < len(words); i, j = i+1, j-1 {
		runes := []rune(words[i])
		if len(runes) <= 1 {
			if unicode.Is(unicode.Hebrew, runes[0]) {
				sentense[j] = words[i]
			} else {
				sentense[j] = ""
				fmt.Println("Not hebrew word: ", words[i])
				engSentense[k] = words[i]
				k++
			}
		} else {
			if unicode.Is(unicode.Hebrew, runes[1]) {
				sentense[j] = words[i]
			} else {
				sentense[j] = ""
				fmt.Println("Not hebrew word: ", words[i])
				engSentense[k] = words[i]
				k++
			}
		}

	}
	fmt.Println(engSentense)
	for i, j := 0, 0; i < len(sentense); i++ {
		if sentense[i] == "" {
			sentense[i] = engSentense[j]
			j++
		}
	}
	return strings.Join(sentense, " ")
}

func main() {
	s := "הפלחהA 170/120/95- רוטנרטלא הניעט תקידב ילופ ה''ופ תועוצר ה''ופ :ללוכ רוטנרטלא הסכמ ךומנ ןאמב ירוחא שוגפ ה''ופ"
	fmt.Println(reverseHebrewWords(s))
	s = "הנקתה 92-160 .ט.ה יפל יראלולס רטואר"
	fmt.Println(reverseHebrewWords(s))
}
