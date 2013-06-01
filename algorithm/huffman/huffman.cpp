/****************************************************

              Huffman Coding Class
    
    Originally coded by Liu Fanchao, OUC.
    U can contact me via email: asklux@gmail.com, or
    Come to http://www.flyx.cn to leave a message.

    if it works,it is coded by lfc.
    if it doesn't work,I don't know who modified it.


****************************************************/

#include "huffman.h"
#include "main.h"
#include <cstring>

CHuffman::CHuffman(unsigned char *pSrc, int nSrcLen)
{
  m_pSrc = pSrc;
  m_nSrcLen = nSrcLen;
  m_nElemCount = 0;

  // allocate 0xff*2+1 nodes and set to 0
  // should be 511, 0xff*2+1 will overflow
  m_nodes = new Node[511];
  m_codeTable = new HuffmanCode[256];
  memset(m_nodes, 0, 511*sizeof(Node));
  memset(m_codeTable, 0, 256*sizeof(HuffmanCode));
}

CHuffman::CHuffman(unsigned char *pSrc)
{
  m_pSrc = pSrc;
  m_nSrcLen = 0;
  m_nFileLen = ((PHuffmanHeader)pSrc)->fileLen;

  m_nodes = new Node[511];
  m_nElemCount = ((PHuffmanHeader)pSrc)->nElemCount;
  m_codeTable = NULL;
  memset(m_nodes, 0, 511*sizeof(Node));
}

bool CHuffman::Select(int nLastIndex, PNode *s1, PNode *s2)
{
  // select 2 nodes with lowest weight
  int i,tmp;

  // search for s1
  for(i=0; i<=nLastIndex; i++)
    {
      if(m_nodes[i].weight!=0 && m_nodes[i].parent==0)
	{
	  tmp=m_nodes[i].weight;
	  *s1=&m_nodes[i];
	  break;
	}
    }
  for(i=0; i<=nLastIndex; i++)
    {
      if(m_nodes[i].parent != 0)
	continue;
      if(m_nodes[i].weight>0 && m_nodes[i].weight<tmp)
	{
	  tmp=m_nodes[i].weight;
	  *s1=&m_nodes[i];
	}
    }
  // search for s2
  for(i=0; i<=nLastIndex; i++)
    {
      if(m_nodes[i].weight>0 && m_nodes[i].parent==0 && *s1!=&m_nodes[i])
	{
	  tmp=m_nodes[i].weight;
	  *s2=&m_nodes[i];
	  break;
	}
      // all nodes have been attached to the tree
      if(i==nLastIndex)
	return false;
    }
  for(i=0; i<=nLastIndex; i++)
    {
      if(m_nodes[i].parent != 0)
	continue;
      if(&m_nodes[i]==*s1)
	continue;
      if(m_nodes[i].weight>0 && m_nodes[i].weight<tmp)
	{
	  tmp=m_nodes[i].weight;
	  *s2=&m_nodes[i];
	}
    }

  return true;
}

bool CHuffman::CalcWeight()
{
  // get the weight of each element
  int i;
  for(i=0; i<m_nSrcLen; i++)
    {
      m_nodes[m_pSrc[i]].weight++;
    }

  return true;
}

bool CHuffman::BuildHuffmanTree()
{
  int i;
  Node *s1,*s2;
  for(i=0; i < 256; i++)
    {
      m_nodes[i].value = (unsigned char)i;
    }
  for(i=256; i<=510; i++)
    {
      if(!Select(i-1,&s1,&s2))
	break;
      s1->parent=&m_nodes[i];
      s2->parent=&m_nodes[i];
      m_nodes[i].lchild=s1;
      m_nodes[i].rchild=s2;
      m_nodes[i].weight=s1->weight + s2->weight;
    }
  return true;
}

bool CHuffman::GetCodeTable()
{
  int i;
  PNode tmpNode;
  for(i=0; i<=255; i++)
    {
      if(m_nodes[i].weight>0)
	{
	  tmpNode=&m_nodes[i];
	  while(tmpNode->parent!=0)
	    {
	      //m_codeTable[i].ElemCode |= (((tmpNode==tmpNode->parent->lchild)?((unsigned long)0):((unsigned long)1))<<m_codeTable[i].nLength);
	      m_codeTable[i].ElemCode <<= 1;
	      m_codeTable[i].ElemCode |= ((tmpNode==tmpNode->parent->lchild)?((unsigned long)0):((unsigned long)1));
	      m_codeTable[i].nLength++;
	      tmpNode=tmpNode->parent;
	    }
	}
    }
  return true;
}

unsigned char *CHuffman::Compress(int &nDestLen)
{
  int i;
  CalcWeight();
  BuildHuffmanTree();
  GetCodeTable();

#ifdef _DEBUG
  int j;
  cout<<"The huffman codes of each element are as follows:"<<endl;
  for(i=0; i<=255; i++)
    {
      if(m_codeTable[i].nLength>0)
	{
	  if(i>=0x20 && i<=0x7E)
	    cout<<"\t"<<(char)i<<hex<<"(0x"<<i<<")\t: ";
	  else
	    cout<<"\t"<<hex<<"(0x"<<i<<")\t: ";
	  for(j=m_codeTable[i].nLength-1; j>=0; j--)
	    {
	      cout<<((m_codeTable[i].ElemCode)>>j)%2;
	    }
	  cout<<endl;
	}
    }
  cout<<endl;
  cout<<"print table finished..."<<endl;
#endif

  unsigned long nIndex=0;
  unsigned char *buffer=new unsigned char[m_nSrcLen];
  memset(buffer, 0, m_nSrcLen);
  // set HEADER
  PHuffmanHeader pHeader = new HuffmanHeader;
  pHeader->magic[0]='H';
  pHeader->magic[1]='U';
  pHeader->magic[2]='F';
  pHeader->magic[3]='F';
  pHeader->fileLen=m_nSrcLen;

  pHeader->nElemCount=0;
  for(i=0; i<=255; i++)
    {
      if(m_codeTable[i].nLength>0)
	pHeader->nElemCount++;
    }

  // set destination buffer according to m_codeTable
  for(i=0; i<m_nSrcLen; i++)
    {
      // code length should not be longer than sizeof(long)
      *((unsigned long *)(buffer+(nIndex>>3))) |= m_codeTable[m_pSrc[i]].ElemCode << (nIndex&7);
      nIndex+=m_codeTable[m_pSrc[i]].nLength;
    }

#ifdef _DEBUG
  cout<<"generate code finished..."<<endl;
#endif

  pHeader->nCodeLen=nIndex;
  nDestLen=sizeof(HuffmanHeader)
    +pHeader->nElemCount*sizeof(HeaderWeight)
    +(nIndex>>3)+((nIndex&7)?1:0);

  unsigned char *pDest=new unsigned char[ nDestLen ];
  memcpy(pDest, pHeader, sizeof(HuffmanHeader));
  HeaderWeight tmpHead;
  int t=0;
  for(i=0; i<=255; i++)
    {
      if(m_codeTable[i].nLength>0)
	{
	  tmpHead.value = (unsigned char)i;
	  tmpHead.weight = m_nodes[i].weight;
	  memcpy(pDest+sizeof(HuffmanHeader)+t*sizeof(HeaderWeight),
		 &tmpHead,
		 sizeof(HeaderWeight));
	  t++;
	}
    }
  memcpy(pDest + sizeof(HuffmanHeader) + pHeader->nElemCount*sizeof(HeaderWeight),
	 buffer, (nIndex>>3)+((nIndex&7)?1:0));
  delete buffer;
  delete pHeader;

  return pDest;
}

bool CHuffman::Decompress(unsigned char *fileBuffer)
{
  int i,j;

  PHeaderWeight HWPtr = (PHeaderWeight)(m_pSrc+sizeof(HuffmanHeader));
  for(i=0; i<m_nElemCount; i++)
    {
      m_nodes[(HWPtr+i)->value].weight = (HWPtr+i)->weight;
    }

  BuildHuffmanTree();

  PNode pRoot;
  pRoot = &m_nodes[HWPtr->value];
  while(pRoot->parent)
    pRoot = pRoot->parent;

  // decode
  unsigned char *ptr = m_pSrc+sizeof(HuffmanHeader)+m_nElemCount*sizeof(HeaderWeight);
  unsigned long nCodeLen = ((PHuffmanHeader)m_pSrc)->nCodeLen;
  unsigned long nIndex = 0;
  unsigned long nFileCur = 0;
  PNode pTmpNode;
  unsigned long nCode;
  while(nIndex < nCodeLen)
    {
      // KEY
      nCode = (*((unsigned long *)(ptr+(nIndex>>3)))>>(nIndex&7));
      pTmpNode = pRoot;
      while(pTmpNode->lchild)// binary tree, both lchild and right child must exist
	{
	  pTmpNode = (nCode&1) ? pTmpNode->rchild : pTmpNode->lchild;
	  nCode >>= 1;
	  nIndex++;
	}
      fileBuffer[nFileCur++] = pTmpNode->value;
    }
#ifdef _DEBUG
  cout<<"File length: "<<nFileCur<<endl;
#endif
  return true;
}

bool CHuffman::PrintTable()
{
  int i,j;
  CalcWeight();
  BuildHuffmanTree();
  GetCodeTable();

  unsigned long nBase = 0;
  for(i=0; i<256; i++)
    nBase += m_nodes[i].weight;

  cout<<endl;
  cout<<"\tChar\tFreq\tCode"<<endl<<endl;
  for(i=0; i<=255; i++)
    {
      if(m_codeTable[i].nLength>0)
	{
	  cout.setf(ios::fixed);
	  cout.precision(2);
	  cout<<"\t "<<(char)i<<"\t"<<((float)m_nodes[i].weight)/nBase<<"\t";
	  for(j=m_codeTable[i].nLength-1; j>=0; j--)
	    {
	      cout<<((m_codeTable[i].ElemCode)>>j)%2;
	    }
	  cout<<endl;
	}
    }
  cout<<endl;

  return true;
}

CHuffman::~CHuffman()
{
  delete m_nodes;
  delete m_codeTable;
}
