#ifndef __WORDSPLIT_H__
#define __WORDSPLIT_H__

typedef unsigned short	UInt16
typedef unsigned int	UInt32

typedef struct _Word2id{
	UInt16 wordid; // 第二词wordid
	UInt16 fre; // Bigram计数
	struct Word2id *next; // 指向下一个二词节点的指针
};

typedef struct _Word1id{
	UInt32 fre; // 首词频度
	struct Word2id *word2listHead; // 第二词队列首指针
};

#endif
