// Macha's Utilities
int log10(int x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}

void delay(int duration)
{
	int x, y;

	for (x = 0; x < duration; x++)
	{
		for (y=0; y<duration; y++)
		{}
	}
}

void printdelay(char *input, int duration, int app)
{
	size_t length = strlen(input);
	char str[2];
	int i;
	for(i = 0; i < length; i++)
	{
		str[0] = input[i];
		str[1] = '\0';
		printf("%s",str);
		delay(duration);
	}
	if (app == TRUE)
	{
		printf("\n");
	}
}
