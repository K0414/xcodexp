#include <stdio.h>
#include <string.h>

static char *Haab_months[] = { "pop", "no", "zip", "zotz", "tzec", "xul",
						"yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac",
						"kankin", "muan", "pax", "koyab", "cumhu", "uayet"
};

static char *Tzolkin_days[] = { "imix", "ik", "akbal", "kan", "chicchan",
						"cimi", "manik", "lamat", "muluk", "ok", "chuen",
						"eb", "ben", "ix", "mem", "cib", "caban", "eznab",
						"canac", "ahau"
	
};

int getHaabMonth(char *month);

int main()
{
	int total_days,i,n;
	int Hday,Hyear;
	char Hmonth[100];
	
	scanf("%d", &n);
	printf("%d\n", n);
	
	for(i=0; i<n; i++) {
		scanf("%d. %s %d", &Hday, Hmonth, &Hyear);
		total_days = 365 * Hyear
					+ (getHaabMonth(Hmonth) - 1) * 20
					+ Hday;
					
		printf("%d %s %d\n", (total_days % 260 % 13) + 1
							, Tzolkin_days[total_days % 260 % 20]
							, total_days / 260);
	}
	
	return 0;
}

// return 1..19
int getHaabMonth(char *month)
{
	int i;
	
	for(i=0; i<19; i++) {
		if(!strcmp(Haab_months[i], month))
			return i+1;
	}
	
	return 0;
}
