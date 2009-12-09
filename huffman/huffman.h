/****************************************************

              Huffman Coding Class
    
    Originally coded by Liu Fanchao, OUC.
    U can contact me via email: asklux@gmail.com, or
    Come to http://www.flyx.cn to leave a message.

    if it works,it is coded by lfc.
    if it doesn't work,I don't know who modified it.


****************************************************/

#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <iostream>
using namespace std;

// due to the header,
// the target file may be
// larger than the original one
typedef struct _HuffmanHeader{
  char magic[4]; // 'H','U','F','F'
  unsigned long fileLen;// destination file length
  int nElemCount;
  unsigned long nCodeLen; // Total bits of the code
}HuffmanHeader,*PHuffmanHeader;

typedef struct _Node{
  unsigned long weight;
  unsigned char value;
  _Node *parent,*lchild,*rchild;
}Node,*PNode;

typedef struct _HuffmanCode{
  unsigned long ElemCode;
  int nLength;
}HuffmanCode,*PHuffmanCode;

typedef struct _HeaderWeight{
  unsigned char value;
  unsigned long weight;
}HeaderWeight,*PHeaderWeight;

class CHuffman{
 public:
  CHuffman(unsigned char *pSrc, int nSrcLen);
  CHuffman(unsigned char *pSrc);
  ~CHuffman();

 private:
  unsigned char *m_pSrc;
  int m_nSrcLen;
  int m_nElemCount;
  int m_nFileLen;
  PNode m_nodes;
  PHuffmanCode m_codeTable;
  bool CalcWeight();
  bool BuildHuffmanTree();
  bool GetCodeTable();
  bool Select(int nLastIndex, PNode *s1, PNode *s2);

 public:
  unsigned char *Compress(int &nDestLen);
  bool Decompress(unsigned char *fileBuffer);
  bool PrintTable();
};

#endif
