#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6;

bool bin[1024*MAXN];
char table[64] = {	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
					'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
					'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
					'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
				 };

void help()
{
	puts("usage: base64 [-h] [-e STRING] [-d STRING]");
	puts("");
	puts("optional arguments:");
	puts("  -h, --help\t\tshow this help message and exit");
	puts("  -e STRING\t\tthe string to be encrypted");
	puts("  -d STRING\t\tthe string to be decrypted");
	puts("Open source at: <https://github.com/heart4lor/base64>");
	puts("");
}

void encrypt(const char* str)
{
	puts("encrypted result:");
	int len = strlen(str);
	int pos = 0;
	for(int i = 0; i < len; i++)
	{
		char tmp[10];
		itoa(str[i], tmp, 2);
		int t_len = strlen(tmp);
		int patch = 8-t_len;
		while(patch--)
			bin[pos++] = 0;
		for(int i = 0; i < t_len; i++)
			bin[pos++] = tmp[i]-'0';
	}
	int patch = (6-(pos%6))%6;
	while(patch--)
		bin[pos++] = 0;
	len = 0;
	for(int i = 0; i < pos; i++)
		if(!((i+1)%6))
		{
			len++;
			int c = 0;
			for(int j = 0; j < 6; j++)
				if(bin[i-j])
					c += (int)pow(2, j);
			printf("%c", table[c]);
		}
	while(len++%4)
		printf("=");
	printf("\n\n");
}

void decrypt(const char* str)
{
	puts("decrypted result:");
	int len = strlen(str);
	int pos = 0;
	for(int i = len-1; i > 0; i--)
		if(str[i] == '=')
			len--;
		else
			break;
	for(int i = 0; i < len; i++)
	{
		char tmp[10];
		char c = str[i];
		int num;
		if(isupper(c))
			num = c-'A';
		else if(islower(c))
			num = c-'a'+26;
		else if(isalnum(c))
			num = c-'0'+52;
		else if(c=='+')
			num = 62;
		else if(c=='/')
			num = 63;
		itoa(num, tmp, 2);
		int t_len = strlen(tmp);
		int patch = 6-t_len;
		while(patch--)
			bin[pos++] = 0;
		for(int i = 0; i < t_len; i++)
			bin[pos++] = tmp[i]-'0';
	}
	len = 0;
	for(int i = 0; i < pos; i++)
		if(!((i+1)%8))
		{
			len++;
			char c = '\0';
			for(int j = 0; j < 8; j++)
				if(bin[i-j])
					c += (int)pow(2, j);
			printf("%c", c);
		}
	printf("\n\n");
}

int main(int argc, char const *argv[])
{
	if(argc==2 || argc==3)
	{
		if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
			help();
		else if(!strcmp(argv[1], "-e"))
			encrypt(argv[2]);
		else if(!strcmp(argv[1], "-d"))
			decrypt(argv[2]);
		else
		{
			printf("ERROR: option \"%s\" not recognized\n", argv[1]);
			help();
		}
	}
	else
	{
		printf("ERROR: option \"%s\" not recognized\n", argv[1]);
		help();
	}
	return 0;
}
