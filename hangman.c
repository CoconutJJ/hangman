#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_WORD_LEN 200
#define LIVES 10;

int lives = LIVES;



char *pickRandomWord(FILE *wordList) {

  // generate a random seed
  srand(time(NULL));

  // loop through the file characters and count the number new lines
  int ch, lncount = 0;

  // get a character
  while ((ch = fgetc(wordList)) != EOF && ((ch == '\n') ? ++lncount : 1))
    ;

  int line = (rand() % (lncount - 1)) + 1;
  int currln = 0;

  fseek(wordList, 0, SEEK_SET);

  char *word = malloc(MAX_WORD_LEN * sizeof(char));

  while (currln != line && ++currln &&
         fscanf(wordList, "%s\n", &(word[0])) != EOF)
    ;

  return word;
}

char *createWordBlanks(char *word) {

  char *wordBlanks = malloc(strlen(word) + 1);

  memset(wordBlanks, '_', strlen(word));

  wordBlanks[strlen(word)] = '\0';

  return wordBlanks;
}

int fillWordBlank(char *word, char *wordblank, char c) {
  int count = 0;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] == c) {

      if (wordblank[i] != '_')
        return -1;

      wordblank[i] = c;
      count++;
    }
  }

  return count;
}

int main(int argc, char **argv) {

  FILE *wordlist = fopen("wordlist.txt", "r");
  char *word = pickRandomWord(wordlist);
  char *blanks = createWordBlanks(word);

  int filledChars;
  int totalCharsFilled = 0;

  char c;
  while (1) {

    printf("%s\n\n", blanks);
    printf("Guess a letter:\n");
    int guess = getchar();

    scanf("%c", &c);

    char dump[80];
    

    filledChars = fillWordBlank(word, blanks, guess);

    if (filledChars == 0) {
      lives = lives - 1;

      if (lives == 0) {
        printf("You are dead!\n");
        break;
      } else {
        printf("Incorrect. Lives remaining %d\n", lives);
      }
    } else {
      totalCharsFilled += filledChars;
      printf("%d spots filled.\n", filledChars);
      if (totalCharsFilled == strlen(word)) {
        printf("Win!");
        exit(EXIT_SUCCESS);
      }
    }
  }
}