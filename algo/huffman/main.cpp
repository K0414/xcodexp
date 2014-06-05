/***********************************************************

              Huffman Coding Demo
    
    Originally coded by Liu Fanchao, OUC.
    U can contact me via email: asklux@gmail.com, or
    Come to http://www.flyx.cn to leave a message.

    Usage:
        ./huffman [OPTION] -s SOURCE -t TARGET
     or ./huffman -v STRING
     or ./huffman -a

     OPTION:
                 -c         Compress a file.
                            SOURCE specifies the file 
                            to be compressed.
                            TARGET specifies the name 
                            of the compressed file.

                 -d         Decompress a file.
                            SOURCE specifier a file
                            compressed by this program.
                            TARGET specifies the name
                            of the decompressed file.

     ./huffman -v STRING    Print the huffman code of
                            each character in STRING.

     ./huffman -a           About the program and team
                            members.             

***********************************************************/

#include <stdio.h>
#include <cstring>
#include <getopt.h>
#include "main.h"
#include "huffman.h"

void usage();

int main(int argc,char *argv[])
{
  int next;
  int cflag,dflag,sflag,tflag,vflag,aflag;
  char *source,*dest,*srcstr;
  const char *const s_options = "cds:t:v:a";

  cflag=dflag=sflag=tflag=vflag=aflag=0;

  while((next = getopt(argc, argv, s_options)) != EOF)
    {
      switch(next)
	{
	case 'c':
	  cflag = 1;
	  break;
	case 'd':
	  dflag = 1;
	  break;
	case 's':
	  sflag = 1;
	  source = new char[strlen(optarg) + 1];
	  strcpy(source,optarg);
	  break;
	case 't':
	  tflag = 1;
	  dest = new char[strlen(optarg) + 1];
	  strcpy(dest,optarg);
	  break;
	case 'v':
	  vflag = 1;
	  srcstr = new char[strlen(optarg) + 1];
	  strcpy(srcstr,optarg);
	  break;
	case 'a':
	  aflag = 1;
	  break;
	default:
	  break;
	}
    }
  
  if(aflag)
    {
      cout<<"Team Members:"<<endl;
      cout<<"\tLiu Fanchao(Author)"<<endl;
      cout<<"\tLi Song"<<endl;
      cout<<"\tChen Pang"<<endl;
      cout<<"\tFan Huiyang"<<endl;
      cout<<"\tWang Bin"<<endl;
      return 0;
    }

  if(vflag)
    {
      if(strlen(srcstr)<=0)
	{
	  usage();
	  return 1;
	}
      CHuffman *vHuffman = new CHuffman((unsigned char *)srcstr,strlen(srcstr));
      vHuffman->PrintTable();
      return 0;
    }

  int i,tmpLen,nBase,nSrcLen,nDestLen;
  unsigned char *pDest;
  FILE *srcfp,*desfp;

  if(cflag)
    {
      /*
	-= Compress =-
      */
      if(!sflag || !tflag)
	{
	  usage();
	  return 1;
	}

      if(strlen(source)<=0 || strlen(dest)<=0)
	{
	  usage();
	  return 1;
	}

      if((srcfp=fopen(source,"r"))==NULL)
	{
	  cout<<"Read source file error!"<<endl;
	  return 1;
	}

#ifdef _DEBUG
      cout<<"source file name: "<<source<<endl;
#endif

      if((desfp=fopen(dest,"w+"))==NULL)
	{
	  cout<<"Write target file error!"<<endl;
	  return 1;
	}

      fseek(srcfp, 0, SEEK_END);
      nSrcLen=ftell(srcfp);
      fseek(srcfp, 0, SEEK_SET);
#ifdef _DEBUG
      cout<<"source file length: "<<nSrcLen<<endl;
#endif
      unsigned char *srcBuffer=new unsigned char[nSrcLen];
      cout<<"Reading source file..."<<endl;
      fread(srcBuffer,1,nSrcLen,srcfp);
      CHuffman *pHuffman = new CHuffman(srcBuffer, nSrcLen);
      cout<<"Compressing file..."<<endl;
      pDest = pHuffman->Compress(nDestLen);
      cout<<"Writing file..."<<endl;
      fwrite(pDest,1,nDestLen,desfp);
      cout<<"Done!"<<endl<<endl;

      cout<<"Source file length:\n\t<";
      tmpLen = nSrcLen;
      nBase = tmpLen / 25;
      while(tmpLen/nBase)
	{
	  cout<<"=";
	  tmpLen -= nBase;
	}
      cout<<"> "<<nSrcLen<<" Bytes"<<endl;
      cout<<"Target file length:\n\t<";
      tmpLen = nDestLen;
      while(tmpLen/nBase)
	{
	  cout<<"=";
	  tmpLen -= nBase;
	}
      cout<<"> "<<nDestLen<<" Bytes"<<endl;
      cout.setf(ios::fixed);
      cout.precision(2);
      cout<<"Compression rate: "<<((float)nDestLen)/nSrcLen<<endl<<endl;

      delete srcBuffer;
      delete pDest;
      fclose(srcfp);
      fclose(desfp);

      return 0;
    }

  if(dflag)
    {
      /*
	-= Decompress =-
      */
      if(!sflag || !tflag)
	{
	  usage();
	  return 1;
	}

      if(strlen(source)<=0 || strlen(dest)<=0)
	{
	  usage();
	  return 1;
	}

      if((srcfp=fopen(source,"r"))==NULL)
	{
	  cout<<"Read source file error!"<<endl;
	  return 1;
	}
      
#ifdef _DEBUG
      cout<<"source file name: "<<source<<endl;
#endif
      
      fseek(srcfp, 0, SEEK_END);
      nSrcLen=ftell(srcfp);
      fseek(srcfp, 0, SEEK_SET);
#ifdef _DEBUG
      cout<<"source file length:"<<nSrcLen<<endl;
#endif
      unsigned char *deBuffer = new unsigned char[nSrcLen];
      cout<<"Reading source file..."<<endl;
      fread(deBuffer,1,nSrcLen,srcfp);
      
      PHuffmanHeader pHeader = (PHuffmanHeader)deBuffer;
      cout<<"Checking file type..."<<endl;
#ifdef _DEBUG
      cout<<"magic string: ";
      for(i=0; i<4; i++)
	cout<<pHeader->magic[i];
      cout<<endl;
#endif
      if(pHeader->magic[0] != 'H'
	 || pHeader->magic[1] != 'U'
	 || pHeader->magic[2] != 'F'
	 || pHeader->magic[3] != 'F')
	{
	  cout<<"Source file not valid!"<<endl;
	  return 1;
	}
      
      if((desfp=fopen(dest,"w+"))==NULL)
	{
	  cout<<"Write target file error!"<<endl;
	  return 1;
	}
      
      unsigned char *fileBuffer = new unsigned char[pHeader->fileLen];
      CHuffman *deHuffman = new CHuffman(deBuffer);
      cout<<"Decompressing file..."<<endl;
      deHuffman->Decompress(fileBuffer);
      cout<<"Writing target file..."<<endl;
      fwrite(fileBuffer,1,pHeader->fileLen,desfp);
      cout<<"Done!"<<endl;
      delete deBuffer;
      delete fileBuffer;
      fclose(srcfp);
      fclose(desfp);
      return 0;
    }

  usage();
  return 0;
}

void usage()
{
  cout<<endl;
  cout<<" Usage:"<<endl;
  cout<<"        ./huffman [OPTION] -s SOURCE -t TARGET"<<endl;
  cout<<"     or ./huffman -v STRING"<<endl;
  cout<<"     or ./huffman -a"<<endl;
  cout<<endl;
  cout<<" OPTION:"<<endl;
  cout<<"              -c         Compress a file."<<endl;
  cout<<"                         SOURCE specifies the file to be compressed."<<endl;
  cout<<"                         TARGET specifies the name of the compressed file."<<endl;
  cout<<endl;
  cout<<"              -d         Decompress a file."<<endl;
  cout<<"                         SOURCE specifies a file compressed by this program."<<endl;
  cout<<"                         TARGET specifies the name of the decompressed file."<<endl;
  cout<<endl;
  cout<<"  ./huffman -v STRING    Print the huffman code of each character in STRING."<<endl;
  cout<<endl;
  cout<<"  ./huffman -a           About the program and team members."<<endl;
  cout<<endl;        
}
