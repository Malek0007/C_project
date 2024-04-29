#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define alpha 3
#define num_iterations 400000
#define num_features 5
double high[274]={0} , low[274]={0} , open[274]={0}  , vol[274]={0} , marketcap[274]={0} , matrice[274][5]={1} ;
int test = 1;

// Function to normalize a column
void normalize_column(double* column, int num_rows) {
    double max_value = column[0];
    double min_value = column[0];
    for (int i = 0; i < num_rows; i++) {
        if (column[i] > max_value) {
            max_value = column[i];
        }
        if (column[i] < min_value) {
            min_value = column[i];
        }
    }
    double range = max_value - min_value;
    for (int i = 0; i < num_rows; i++) {
        column[i] = (column[i] - min_value) / range;
    }
}

double data (){

	FILE* fp = fopen("coin_Cosmos.csv", "r");
	if (!fp){
        test = 0 ;
        }
	else {
		char buffer[10024];
		int row = 0;
		int column = 0;
        int tab = 0 ;
		while (fgets(buffer, 10024 , fp )) {
			column = 0;
			row++;
			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ",");

			while (value) {
				value = strtok(NULL, ",");
				column++;
                if (column==4)
                {
                    high[tab]= atof(value);
                }
                if (column==5)
                {
                    low[tab]= atof(value);
                }
                if (column==6)
                {
                    open[tab]= atof(value);
                }
                if (column==8)
                {
                    vol[tab]= atof(value);
                }
                if (column==9)
                {
                    marketcap[tab]= atof(value);
                }
            }
            tab++;
		}
		// Close the file
		fclose(fp);
	}

    // Normalize each column
    normalize_column(high, 274);
    normalize_column(low, 274);
    normalize_column(open, 274);
    normalize_column(vol, 274);
    normalize_column(marketcap, 274);

    // Put the normalized data in the matrice
    for(int i = 1 ; i <275 ; i++){
        matrice[i][1]=high[i];
        matrice[i][2]=low[i];
        matrice[i][3]=open[i];
        matrice[i][4]=vol[i];
    }
}
int main()
{ data();
    if (test == 0){
        printf("Can't open file\n");
    }else{

    double  h=0, cost_train=0 , cost_test = 0;
    double theta[num_features];
    double x_sum[num_features], y_sum = 0, xy_sum = 0;


    for (int i = 0; i < num_features; i++)
    {
        theta[i] = 10000;
        x_sum[i] = 0;
    }

    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_features; j++)
        {
            x_sum[j] = 0;
        }
        y_sum = 0;
        xy_sum = 0;

        for (int j = 0; j < 120; j++)
        {
            h = 0;
            for (int k = 0; k < num_features; k++)
            {
                 h += theta[k] * matrice[j][k];

            }

            for (int k = 0; k < num_features; k++)
            {
                x_sum[k] +=(h - marketcap[j])*matrice[j][k];
            }
            y_sum += h - marketcap[j];
            xy_sum += (h - marketcap[j]) * (h - marketcap[j]);
        }

        cost_train = xy_sum / 120;
        for (int j = 0; j < num_features; j++)
        {
            theta[j] = theta[j] - (alpha *x_sum[j] ) / 120;
        }
    }
    printf("le cost_train = %lf \n" , cost_train);
    for (int j = 0; j < num_features; j++)
        {
            x_sum[j] = 0;
        }
        y_sum = 0;
        xy_sum = 0;

        for (int j = 120; j < 270; j++)
        {
            h = 0;
            for (int k = 0; k < num_features; k++)
            {
                 h += theta[k] * matrice[j][k];

            }

            for (int k = 0; k < num_features; k++)
            {
                x_sum[k] +=(h - marketcap[j])*matrice[j][k];
            }
            y_sum += h - marketcap[j];
            xy_sum += (h - marketcap[j]) * (h - marketcap[j]);
        }

        cost_test = xy_sum / 150;
        printf("le cost_test = %lf \n" , cost_test);
    printf("\nTheta values: ");
    for (int i = 0; i < num_features; i++)
    {
        printf("%lf ", theta[i]);
    }
    printf("\nEquation of line: y = ");
    for (int i = 1; i < num_features; i++)
    {
        printf("(%lf * x%d) + ", theta[i], i);
    }
    printf("%lf" , theta[0]);
	return 0;
    }
}
