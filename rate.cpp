//
//  main.cpp
//  proj5
//
//  Created by Monica Bellare on 11/9/18.
//  Copyright © 2018 Monica Bellare. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

void rotateLeft(char word[][MAX_WORD_LENGTH+1], int n, int start) { // for makeProper
    for(int i = start; i < n; i++) {
        if(i != n-1) {
            for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
                word[i][j] = word[i+1][j];
            }
        }
        else {
            for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
                //word[n-1][j] = ' '; // makes last element empty (as it's now irrelevant and considered removed)
                word[n-1][0] = '\0';
            }
        }
    }
}

void rotateIntLeft(int nums[], int n, int start) { // for makeProper
    for(int i = start; i < n-1; i++) {
        nums[i] = nums[i+1];
    }
    nums[n-1] = -1;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns) {
    if(nPatterns < 0)
        return 0;
    
    for(int i = 0; i < nPatterns; i++) {
        for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
            if(word1[i][j] != '\0') {
                if(!isalpha(word1[i][j]))
                    word1[i][0] = '\0'; // if any character in this word is not a letter, make first character in word zero byte
            }
            else
                break;
        }
        for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
            if(word2[i][j] != '\0') {
                if(!isalpha(word2[i][j]))
                    word1[i][0] = '\0'; // same for this word in word1 for word2[][]
            }
            else
                break;
        }
        if(separation[i] < 0) // if any number in this array is negative, make first character in word1 zero byte
            word1[i][0] = '\0';
    }
    
    for (int i = 0; i < nPatterns; i++) // making all elements in word1 lowercase
    {
        for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
            if(word1[i][j] != '\0')
                word1[i][j] = tolower(word1[i][j]);
            else
                break;
        }
    }
    
    for (int i = 0; i < nPatterns; i++) // making all elements in word2 lowercase
    {
        for(int j = 0; j < MAX_WORD_LENGTH+1; j++) {
            if(word2[i][j] != '\0')
                word2[i][j] = tolower(word2[i][j]);
            else
                break;
        }
    }
    
    // checks if two pairs of words in word1 and word2 are identical - with same places
    bool same = false;
    for(int i = 0; i < nPatterns; i++) {
        for(int j = i+1; j < nPatterns; j++) {
            if(strlen(word1[i]) == strlen(word1[j])) {
                same = true;
                for(int k = 0; k < strlen(word1[i]); k++) {
                    if(word1[i][k] != word1[j][k])
                        same = false; // if any two characters don't match, make false
                }
                if(same) {
                    if(strlen(word2[i]) == strlen(word2[j])) { // now checks if corresponding words are also equal
                        for(int k = 0; k < strlen(word2[i]); k++) {
                            if(word2[i][k] != word2[j][k])
                                same = false; // if any two characters don't match, make false
                        }
                    }
                    else
                        same = false; // if the corresponding words have different lengths
                }
                if(same) { // if both pairs of words are equal
                    if(separation[i] < separation[j]) {
                        word1[i][0] = '\0'; // will later remove this index from word1 & word2
                    }
                    else
                        word1[j][0] = '\0'; // will later remove this index from word1 & word2 (if greater than OR equal to)
                }
                same = false;
            }
        }
    }
    
    // checks if two pairs of words in word1 and word2 are identical - with opposite places
    same = false;
    for(int i = 0; i < nPatterns; i++) {
        for(int j = 0; j < nPatterns; j++) {
            if((strlen(word1[i]) == strlen(word2[j])) && j != i) {
                same = true;
                for(int k = 0; k < strlen(word1[i]); k++) {
                    if(word1[i][k] != word2[j][k])
                        same = false; // if any two characters don't match, make false
                }
                if(same) {
                    if(strlen(word2[i]) == strlen(word1[j])) { // now checks if corresponding words are also equal
                        for(int k = 0; k < strlen(word2[i]); k++) {
                            if(word2[i][k] != word1[j][k])
                                same = false; // if any two characters don't match, make false
                        }
                    }
                    else
                        same = false; // if the corresponding words have different lengths
                }
                if(same) { // if both pairs of words are equal
                    if(separation[i] < separation[j]) {
                        word1[i][0] = '\0'; // will later remove this index from word1 & word2
                    }
                    else
                        word1[j][0] = '\0'; // will later remove this index from word1 & word2 (if greater than OR equal to)
                }
                same = false;
            }
        }
    }
    
    int updated = nPatterns;
    
    int i = 0;
    while(i < updated) {
        if(word1[i][0] == '\0' || word2[i][0] == '\0') {
            rotateLeft(word1, updated, i);
            rotateLeft(word2, updated, i);
            rotateIntLeft(separation, updated, i);
            i--;
            updated--;
        }
        i++;
    }
    
    return updated;
}

bool wordMatch(char doc[][50], const char wordTwo[][MAX_WORD_LENGTH+1], int pos1, int pos2) {
    long len = strlen(wordTwo[pos2]);
    bool ret = true;
    
    if(strlen(doc[pos1]) == strlen(wordTwo[pos2])) {
        for(int i = 0; i < len; i++) {
            if(doc[pos1][i] != wordTwo[pos2][i]) {
                ret = false;
            }
        }
    }
    else
        return false;
    
    return ret;
}

bool patternMatch(int positions[][250], char doc[][50], int size, int pos, const char wordTwo[][MAX_WORD_LENGTH+1], const int sep[]) { // for rate
    // if sep is greater than the space before or after the first word, only check the space that is there
    int matches = 0;
    int j = 0;
    
    for(int i = 0; i < 250; i++) {
        if(positions[pos][i] != -1) {
            while(j <= sep[pos]) { // < ?
                // check for each previous and next word in doc to see if it matches word two
                if(((positions[pos][i]-j-1) >= 0) || ((positions[pos][i]+j+1) < size)) { // checks if either such chars exist
                    if((positions[pos][i]-j-1) >= 0 && (positions[pos][i]+j+1) >= size) { // if only the preceeding char exisits
                        if(wordMatch(doc, wordTwo, (positions[pos][i]-j-1), pos)) {
                            matches++;
                            j++;
                        }
                        else
                            j++; // +1
                    }
                    else if((positions[pos][i]-j-1) < 0 && (positions[pos][i]+j+1) < size) { // if only the succeeding char exists
                        if(wordMatch(doc, wordTwo, (positions[pos][i]+j+1), pos)) {
                            matches++;
                            j++;
                        }
                        else
                            j++;
                    }
                    else { // if both chars exist
                        if((wordMatch(doc, wordTwo, (positions[pos][i]-j-1), pos)) || (wordMatch(doc, wordTwo, (positions[pos][i]+j+1), pos))) {
                            matches++;
                            j++;
                        }
                        else
                            j++;
                    }
                }
                else
                    j = sep[pos]+1; // get out of loop if such chars don't exist
            }
            j = 0;
        }
        else
            i = 250; // have reached end of matches for this first word (get out of for loop)
    }
    
    if(matches == 0)//
        return false;
    else
        return true;
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns) {
    char cleanDoc[252];
    
    int place = 0;
    cleanDoc[place] = '\0';
    for(int i = 0; document[i] != '\0'; i++) {
        if(document[i] == ' ') {
            if(place > 0 && document[i+1] != '\0') { // doesn't add comma if first element isn't letter or if it's the last element
                if((document[i+1] != ' ') && isalpha(cleanDoc[place-1])) { // adds into doc if next char in document is not a space and previous char in cleanDoc isn't a space (if there are multiple spaces before a letter, only adds the one directly before)
                    cleanDoc[place] = tolower(document[i]);
                    place++;
                }
            }
        }
        else if(isalpha(document[i])) {
            cleanDoc[place] = tolower(document[i]); // adds all letters (also makes lowercase)
            place++;
        }
    }
    
    if(cleanDoc[0] != '\0') { // if length is longer than 0
        cleanDoc[place] = ' '; // making last element a space
        place++;
        cleanDoc[place] = '\0'; // making actual last element a zero-byte
    }

    int numWords = 0;
    
    for(int i = 0; i < place; i++) { // going through all elements in cleanDoc to count the number of spaces which is equivalent to the number of words
        if(cleanDoc[i] == ' ')
            numWords++; // increment number of words in cleanDoc
    }
    
    int curPlace = 0;
    
    char cleanDocWords[252][50]; // 2D char array to hold all words in cleanDoc //assuming no words are longer than 49 characters
    for(int i = 0; i < numWords; i++) {
        for(int j = 0; j < 50; j++) {
            if(cleanDoc[curPlace] != ' ') {
                cleanDocWords[i][j] = cleanDoc[curPlace]; // add this letter
                curPlace++;
            }
            else {
                cleanDocWords[i][j] = '\0';
                curPlace++;
                j = 50; // go to the next row because this word is complete
            }
        }
    }
    
    int firstWordsMatch[1000][250]; // 2D array to hold all indexes in document that match the first letter of word - R: each word ; C: pos of matching words in cleanDocWords to this word (if any)
    
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 250; j++) {
            firstWordsMatch[i][j] = -1; // setting all initial values to -1 for checking later
        }
    }
    
    int posFirst = 0; // int to hold column position in 2D int array
    bool first = true;

    long len = 0;
    for(int i = 0; i < nPatterns; i++) { // adding to int array to hold all instances of word1 matches in cleanDocWords
        len = strlen(word1[i]);
        for(int j = 0; j < numWords; j++) {
            if(strlen(word1[i]) == strlen(cleanDocWords[j])) {
                for(int k = 0; k < len; k++) {
                    if(word1[i][k] != cleanDocWords[j][k])
                        first = false;
                }
                if(first) {
                    firstWordsMatch[i][posFirst] = j; // row (word) in cleanDocWords that matches word1 @ row i
                    posFirst++;
                }
            }
            first = true;
        }
        posFirst = 0;
    }
    
    int patterns = 0;

    for(int i = 0; i < nPatterns; i++) {
        if(patternMatch(firstWordsMatch, cleanDocWords, numWords, i, word2, separation)) {
            patterns++;
        }
    }
    
    return patterns;
}

int main() {
    
    // TESTING makeProper
    
    // opposite matching words, different separation values
    char a1[][21] = {"hello", "monica", "hi", "happy", "okay"};
    char a2[][21] = {"hi", "word", "hellO", "hi", "yay"};
    int a3[5] = {1, 2, 3, 0, 1};
    assert(makeProper(a1, a2, a3, 5) == 4);
    
    // separation value < 0
    int a4[5] = {1, -2, 3, 0, 1};
    assert(makeProper(a1, a2, a4, 5) == 3);
    
    // same position matching words, separation values equal
    char b1[][21] = {"hello", "monica", "Hello", "happy", "okay"};
    char b2[][21] = {"hi", "word", "HI", "hi", "yay"};
    int b3[5] = {1, 2, 1, 0, 1};
    assert(makeProper(b1, b2, b3, 5) == 4);
    
    // words in word1 and word2 have same word at same position
    char c1[][21] = {"hello", "monica", "Hello", "happy", "okay"};
    char c2[][21] = {"hi", "word", "HI", "HAPPY", "yay"};
    int c3[5] = {1, 2, 1, 0, 1};
    assert(makeProper(c1, c2, c3, 5) == 4);
    
    // empty word in first 2D cstring
    char d1[][21] = {"hello", "", "Hello", "happy", "okay"};
    char d2[][21] = {"hi", "word", "HI", "HAPPY", "yay"};
    int d3[5] = {1, 2, 1, 0, 1};
    assert(makeProper(d1, d2, d3, 5) == 3);
    
    // empty word in second 2D cstring
    char e1[][21] = {"hello", "wow", "Hello", "happy", "yay"};
    char e2[][21] = {"hi", "", "HI", "HAPPY", "ok"};
    int e3[5] = {1, 2, 1, 0, 1};
    assert(makeProper(e1, e2, e3, 5) == 3);
    
    
    // more than two of same pattern
    char f1[][21] = {"hello", "wow", "Hello", "hi", "yay"};
    char f2[][21] = {"hi", "", "HI", "heLLo", "ok"};
    int f3[5] = {1, 2, 1, 0, 1};
    assert(makeProper(f1, f2, f3, 5) == 2);
    
    // TESTING rate
    
    // extra spaces before in doc
    char g1[][21] = {"the", "cat", "jumped", "down", "from"};
    char g2[][21] = {"cat", "hello", "my", "name", "is"};
    int g3[5] = {1, 2, 1, 0, 0};
    assert(rate("  the adorable cat has a furry tail.", g1, g2, g3, 5) == 1);
    
    // extra spaces in b/w
    assert(rate("  the adorable    cat has a furry tail.", g1, g2, g3, 5) == 1);
    
    // extra spaces after in doc
    assert(rate("  the adorable cat has a furry tail.    ", g1, g2, g3, 5) == 1);
    
    // several non alphabetical characters
    assert(rate("thE! cat has a?@#$ furry tail.", g1, g2, g3, 5) == 1);
    
    // empty doc
    assert(rate("", g1, g2, g3, 5) == 0);
    
    // matching words at the exact separation value
    assert(rate("the adorable cat has a HELLO furry tail.", g1, g2, g3, 5) == 2);
    
    // matching words at greater than separation value
    assert(rate("jumped cat has my furry tail.", g1, g2, g3, 5) == 0);
    
    // matching words (word2 comes before word1)
    assert(rate("is from these are random words!", g1, g2, g3, 5) == 1);
    
    // multiple of one match (only counts one)
    assert(rate("she jumped these my hello my jumped", g1, g2, g3, 5) == 1);
    
    // word longer than 20
    assert(rate("she jumped nveigwfyribfuhdalsritwgirthhrtlongword my jumped", g1, g2, g3, 5) == 1);
    
    // word appears within another word (does not count)
    assert(rate("cat helloMyNameIsMonica these my hello my ok", g1, g2, g3, 5) == 0);
    
    cerr << "success";
}

