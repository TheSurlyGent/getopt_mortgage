/*
	Eduardo Aparicio
	PID: 5645176
	I solemly swear this is all my work
	usage: "Usage: mortgagepmt[-s] - r rate[-d downpayment] price"	
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int debug = 0;
double addPMI(double mortgagepmt,double price)
{
	double pmi;
	pmi = 0.01 * price;
	pmi /= 12;	
	mortgagepmt = mortgagepmt + pmi;
	return mortgagepmt;
}
int
main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0; 
	int  sflag=0, rflag = 0, dflag=0;
	double mortgagepmt;	
	double term = 30;
    double rate;
	double mRate;
	double downpayment;
	double price;
	static char usage[] = "Usage: mortgagepmt[-s] - r rate[-d downpayment] price";

	while ((c = getopt(argc, argv, "sr:d:")) != -1)
		switch (c) {
		
		case 's':
			sflag = 1;
			term = 15;
			break;

		case 'r':
			rflag = 1;
			rate = atof(optarg);
			rate = rate / 100;
			break;

		case 'd':
			dflag = 1;
		    downpayment = atof(optarg);
			break;

		case '?':
			err = 1;
			break;
		}
	if (rflag == 0) 
	{	/* -r was mandatory */
		fprintf(stderr, "%s: missing -r option\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
		
			
	} 
	else if (err) 
	{
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
 	
	price = atof(argv[optind]);

	if(downpayment > price)
	{
		printf("Error downpayment cannot be greater than price\n");
		exit(1);
	}
	price = price - downpayment;

	mRate = rate / 12;//step 1
	mortgagepmt = mRate;
	//printf("%.10f\n",mortgagepmt);
	mortgagepmt = mortgagepmt + 1; //step 2
	//printf("%.10f\n",mortgagepmt);
	double numPayments;
	numPayments = term * 12; // step 3
	//printf("%.0f\n",numPayments);
	mortgagepmt = pow(mortgagepmt,- numPayments);// step 4
	//printf("%.10f\n",mortgagepmt);
	mortgagepmt = 1 - mortgagepmt;// step 5
	//printf("%.10f\n",mortgagepmt);
	mortgagepmt = mRate / mortgagepmt; //step 6
	//printf("%.10f\n",mortgagepmt);
	mortgagepmt *= price;
	//printf("%.2f\n",mortgagepmt);

	if(downpayment < price * 0.2 )//20% of price
	mortgagepmt = addPMI(mortgagepmt,price);

	printf("The payment on a loan of $%.2f with and iterest rate of %.3f%% for a term of %.0f years will be $%.2f \n",price,rate*100,term,mortgagepmt );

	exit(0);
}
