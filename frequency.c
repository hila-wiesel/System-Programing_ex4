#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"

#define NUM_LETTERS 26
#define LONGEST_WORD 45

typedef enum {FALSE=0, TRUE=1} boolean;
char words[LONGEST_WORD];


int main(int argc, char *argv[])
{
    struct Trie* head = newTrieNode(NULL);
    if (head == NULL){
        free_node(head);
        ///exist!
    }
    char str[LONGEST_WORD];
    int len = 0;
    while ((len = getWord(words)) != -1){
        memcpy(str, words, len);
        str[len] = 0;
        insert(head, str);   
    }
    if (argc ==1){
        printWords(head);
    }
    else if (argc ==2 && *argv[1]=='r'){
        printWords_r(head);
    }
    free_TRIE(head);
    return 0;
}

struct Trie
{
    int isWord;    // 1 when node is a word node
    struct Trie* character[NUM_LETTERS];
    int count;
    struct Trie* prev;
    char word[LONGEST_WORD];
};


struct Trie* newTrieNode(struct Trie* prev)
{
    struct Trie* node = (struct Trie*)calloc(1,sizeof(struct Trie));
    if (node != NULL){
        node->isWord = 0;
        node->count = 0;
        node->prev = prev;
        for (int i = 0; i < NUM_LETTERS; i++)
            node->character[i] = NULL;
    }
    return node;
}

int getWord(char word[]){
    char c;
    int len = 0;
    boolean end = TRUE;
    while(scanf("%c", &c) ==1){
        if (c == ' ' || c == '\t' || c == '\n'){
            return len;
        }
        c = lower(c);
        //check if c isn't a letter:
        int index = (int)c-(int)'a';
        if (index<0 || index>25){
            continue;
        }

        end = FALSE;
        word[len]=c;
        ++len;
    }
    if (end){
        return -1;
    }
    return len;
}

void insert(struct Trie *head, char* str)
{
    // start from root node
    struct Trie* curr = head;
    char *str_start = str;
    int i = 0;
    if (!*str) return;      // when str is null
    while (*str)
    {
        // create a new node if path doesn't exists
        if (curr->character[*str - 'a'] == NULL){
            curr->character[*str - 'a'] = newTrieNode(curr);
            if (curr->character[*str - 'a'] == NULL){
                free_TRIE(head);
                ///exist!
            }
        }
 
        // go to next node and to next character
        curr = curr->character[*str - 'a'];
        str++;
        i++;
    }
    
    // mark previuse node as word
    struct Trie* prev = curr->prev;
    prev->isWord = 1;
    prev->count += 1;
    memcpy(prev->word, str_start, i);

}

char lower(char c){
    int a = c;
    if ((a >= 65) && (a <= 90))
        a = a + 32; 
    return a;
}  


void printWords(struct Trie *root){
    if (root == NULL){
        return;
    }
    if (root->count != 0){
        printf("%s %d\n", root->word, root->count);    
        }
    for (int i=0; i<NUM_LETTERS; ++i){
        if(root->character[i] != NULL){
            printWords(root->character[i]);    
        }
    }
}

void printWords_r(struct Trie *root){
    if (root == NULL){
        return;
    }
    for (int i=NUM_LETTERS-1; i>=0; --i){
        if(root->character[i] != NULL){
            printWords_r(root->character[i]);
        }
    }
    if (root->count != 0){    
        printf("%s %d\n", root->word, root->count);
    }
}


void free_node(struct Trie* p){
    free(p);
}

void free_TRIE(struct Trie *root){
    if (root == NULL){
        return;
    }
    for (int i=0; i<NUM_LETTERS; ++i){
        free_TRIE(root->character[i]);
    }
    free_node(root);
}

