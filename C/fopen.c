#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp1;
	FILE *fp2;
	FILE *fp3;

	if ((fp1 = fopen("c1.txt", "r")) == NULL)
	{
		printf("Cannot open file1!\n");
		exit(1);
	}

	if ((fp2 = fopen("c2.txt", "r")) == NULL)
	{
		printf("Cannot open file2!\n");
		exit(1);
	}

    if ((fp3 = fopen("c3.txt", "w")) == NULL)
	{
		printf("Cannot open file3!\n");
		exit(1);
	}

    char ch1;
	char ch2;
	char ch3_1;
	char ch3_2;

	ch1 = fgetc(fp1);
	ch2 = fgetc(fp2);

    int num1;
	int num2;
	int num3;

	while (ch1 != EOF && ch2 != EOF)
	{
        if (ch1 < '0' || ch1 > '9' || ch2 < '0' || ch2 > '9')
		{
            num1 = 0;
			num2 = 0;
			fputc(ch1, fp3);
		}
		else
		{
            num1 = num1 * 10 + (ch1 - '0');
            num2 = num2 * 10 + (ch2 - '0');

            if (num1 > 9 || num2 > 9)
			{
				num3 = num1 + num2;
				ch3_1 = ((num3 % 10) + '0');
				ch3_2 = ((num3 / 10) + '0');

				fputc(ch3_1, fp3);
				fputc(ch3_2, fp3);
			}
		}

		ch1 = fgetc(fp1);
		ch2 = fgetc(fp2);
	}

    fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}