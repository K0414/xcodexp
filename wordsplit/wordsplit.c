#include <stdio.h>
#include "wordsplit.h"

#define MAX_WORD_NUM	256

static char *test_string = "ax ih n#ax ih s n";

char *next_word(char *);
int get_word_id(char *);
struct Word2id *search_word2(int, pWord2id);

// 首词节点数组
struct Word1id TheWord1Id[MAX_WORD_NUM];

int
main(){
	char *ptr = test_string;
	UInt16 word1id=word2id=0;
	Word2id *res=0;
	
	// make sure ptr points to a passage
	// containing more than 2 words.
	while(*ptr){
		word1id = get_word_id(ptr);
		word2id = get_word_id(next_word(ptr));
		
		TheWord1Id[word1id-1].fre++;
		
		res = search_word2(word2id, TheWord1Id[word1id-1].word2listHead);
		if(res){
			
		}
		else{
		
		}
	}
	
	return 0;
}

char*
next_word(char *passage){
	while(' ' != *passage && '#' != *passage)
		passage++;
	
	while(' ' == *passage || '#' == *passage)
		passage++;
		
	return passage;
}

int
get_word_id(char *word){

}

struct Word2id*
search_word2(int word2id, pWord2id list){

}
