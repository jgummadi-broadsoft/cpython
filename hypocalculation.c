//C program to implement hypotenuse & store sorted to a file
/*

Make a program, which reads from an input file length of legs (A and B) of a right-angled
triangle. Calculate length of the hypotenuse using Pythagoras’s law (hypotenuse² = legA²
+ LegB²). Name of the input and output file is given as command line arguments.
Constrains:
• Lengths in the input file are foots (1 foot = 0.3048 meters)
• All lengths in the output file must be in meters.
• Number of the rows in the input file varies and overall length of the file is not limited.
• An operation system has not been chosen yet, so application must be implemented so,
that it is as easy to port as possible
• Format of the input file is:
legA LegB
5.9 1 4.51
5.10 6.82

• Format of the output file must be:
legA legB hypotenuse
30.48 30.48 43.1052

• Rows in the output file must be arranged according to the hypotenuse in ascending order.

*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

/* Structure for a Data */
struct Data
{
	double legA;
	double legB;
	double legC;
	struct Data *next;
};

/*  Inserts data at the beginning*/
void insertDataBegin(struct Data **start_ref, double xdata, double ydata, double zdata);

/* Sorts using bubble for given data*/
void doBubbleSort(struct Data *start);

/* Swap two data's*/
void dataSwap(struct Data *a, struct Data *b);

/*  Write input data to a file*/
void writeToFile(const char*, struct Data *start);

int main(int argc,char* argv[])
{
    char * line = NULL;
    const double ftom = 0.3048;
    size_t len = 0;
    ssize_t read;
    double x, y, z;
    FILE *fpIn;
	struct Data *start = NULL;

    if(argc <=2 )
    {
        printf("\n Provide input and output files");
        exit(EXIT_FAILURE);
    }
    fpIn = fopen(argv[1], "r");
    if (fpIn == NULL) {
        printf("\n file not exists");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fpIn)) != -1)
    {
        int i = 0;
         char *token = strtok(line, " ");
         char *data[2];

         while (token)
             {
               data[i++] = token;
               token = strtok (NULL, "-");
             }
         x = (atof(data[0])) * ftom;
         y = (atof(data[1])) * ftom;
         z = (sqrt((x*x)+(y*y))) * ftom;
         insertDataBegin(&start, x, y, z);
    }
	doBubbleSort(start);
	writeToFile(argv[2], start);
    fclose(fpIn);
	return 0;
}

void insertDataBegin(struct Data **start_ref, double xdata, double ydata, double zdata)
{
	struct Data *ptr1 = (struct Data*)malloc(sizeof(struct Data));
	ptr1 ->legA = xdata;
	ptr1 ->legB = ydata;
	ptr1 ->legC = zdata;
	ptr1->next = *start_ref;
	*start_ref = ptr1;
}

void writeToFile(const char *filename, struct Data *start)
{
	struct Data *temp = start;
	FILE *fpOt;

	fpOt = fopen(filename, "a");
	fprintf(fpOt,"%s \t %s  \t %s \n", "legA", "legB", "hypotenuse");
	while (temp!=NULL)
	{
		fprintf(fpOt,"%f %f %f \n",temp->legA, temp->legB, temp->legC);
		temp = temp->next;
	}
	fclose(fpOt);
}

void doBubbleSort(struct Data *start)
{
	int swap, i;
	struct Data *ptr;
	struct Data *lptr = NULL;

	if (start == NULL)
		return;
	do
	{
		swap = 0;
		ptr = start;
		while (ptr->next != lptr)
		{
			if (ptr->legC > ptr->next->legC)
			{
				dataSwap(ptr, ptr->next);
				swap = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
	while (swap);
}

void dataSwap(struct Data *a, struct Data *b)
{
	float temp = a->legC;
	a->legC = b->legC;
	b->legC = temp;
}