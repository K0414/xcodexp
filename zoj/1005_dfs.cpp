#include <stdio.h>
enum OPERATOR{
START = 1,
FILL_A = 2,
FILL_B = 3,
EMPTY_A = 4,
EMPTY_B = 5,
POUR_A_B = 6,
POUR_B_A = 7
};

int gVA, gVB, gVDes;
//0x0 0 000 000
//      t    a     b
//gVisit中的值表示上一个状态(a,b)通过方法t达到目前的状态
int gVisit[1001][1001];

void print(int a, int b)
{
 if (a == 0 && b == 0)
  return;
 else{
  print((gVisit[a][b] & 0x00fff000) >> 12, (gVisit[a][b]&0x00000fff));
  switch((gVisit[a][b] & 0x0f000000) >> 24){
   case FILL_A:
    printf("fill A\n");
    break;
   case FILL_B:
    printf("fill B\n");
    break;
   case EMPTY_A:
    printf("empty A\n");
    break;
   case EMPTY_B:
    printf("empty B\n");
    break;
   case POUR_A_B:
    printf("pour A B\n");
    break;
   case POUR_B_A:
    printf("pour B A\n");
    break;
  }
 }
}
int search(int a, int b, int la, int lb, enum OPERATOR op)
{
 if (gVisit[a][b])
  return 0;
 gVisit[a][b] = ((int)op << 24) | la << 12 | lb;

 if (a == gVDes || b == gVDes){
  print(a, b);
  return 1;
 }

 if (a < gVA && search(gVA, b, a, b, FILL_A))
  return 1;
 if (b < gVB && search(a, gVB, a, b, FILL_B))
  return 1;
 if (a > 0 && search(0, b, a, b, EMPTY_A))
  return 1;
 if (b > 0 && search(a, 0, a, b, EMPTY_B))
  return 1;
 if (a > 0 && b < gVB && search((a + b < gVB ? 0 : a + b - gVB), (a + b < gVB ? a + b : gVB), a, b, POUR_A_B))
  return 1;
 if (a < gVA && b > 0 && search((a + b < gVA ? a + b : gVA), (a + b < gVA ? 0 : a + b - gVA), a, b, POUR_B_A))
  return 1;
 return 0;
}
int main()
{
 while (scanf("%d %d %d", &gVA, &gVB, &gVDes) != EOF){
  int i, j;
  for (i = 0; i < 1001; ++i)
   for (j = 0; j < 1001; ++j)
    gVisit[i][j] = 0;
  if (search(0, 0, 0, 0, START))
   printf("success\n");
 }
 return 0;
}