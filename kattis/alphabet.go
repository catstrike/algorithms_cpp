package main

import (
	"bufio"
	"fmt"
	"os"
)

const AlphabetSize = int('z' - 'a' + 1)

func alphabetLetter(i int) rune {
	return rune('a' + i)
}

func min(a, b int) int {
	if a < b {
		return a
	}

	return b
}

func alphabet(inputString string) int {
	input := []rune(inputString)

	rows := AlphabetSize + 1
	columns := len(input) + 1

	previousRow := make([]int, columns)
	currentRow := make([]int, columns)

	for i := 1; i < rows; i++ {
		currentRow[0] = i

		for j := 1; j < columns; j++ {
			if input[j-1] == alphabetLetter(i-1) {
				currentRow[j] = previousRow[j-1]
				continue
			}

			currentRow[j] = min(previousRow[j]+1, currentRow[j-1])
		}

		currentRow, previousRow = previousRow, currentRow
	}

	return previousRow[columns-1]
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')

	fmt.Println(alphabet(input))
}
