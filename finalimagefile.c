//Author Eli Biggs & Grace Bottoms
#include <stdio.h>

#define maxrows 200
#define maxcols 200
void displayimage(),dimimage(),brightenimage(),cropimage(),saveimage(),readimage();

void displayimage(int (*image)[maxcols], int rows, int cols)
{
	printf("Displayed image: Rows %d,Cols %d,\n", rows, cols);
	printf(" \n");
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++)
			printf("%d", image[i][k]);

		printf("\n");
	}
}

void dimimage(int (*image)[maxcols], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
				if(image[i][k]>0) {
					image[i][k]--;
				}
			}
	}
}

void brightenimage(int (*image)[maxcols], int rows, int cols){
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
				if(image[i][k]<4) {
					image[i][k]++;
				}
			}
	}
}

void cropimage(int (*image)[maxcols], int *rows, int *cols)
{
	int toprow, bottomrow, leftcol, rightcol;
    
	printf("Enter rows to crop from top: ");
	scanf("%d", &toprow);
	printf("Enter rows to crop from bottom: ");
	scanf("%d", &bottomrow);
	printf("Enter columns to crop from left: ");
	scanf("%d", &leftcol);
	printf("Enter columns to crop from right: ");
	scanf("%d", &rightcol);
    
	printf("Croped image:*rows %d,*cols %d\n",*rows,*cols);
	if(toprow + bottomrow <= *rows && leftcol + rightcol <= *cols) {
		*rows -= (toprow + bottomrow);
		*cols -= (leftcol + rightcol);
	
		
		for (int i = toprow; i < *rows + 1; ++i)
			for (int k = leftcol; k < *cols + 1; ++k) {
				
				image[i-toprow][k-leftcol] = image[i][k];
			}	
	} 
	else {
		printf("Bad crop try again.\n");
	}
}

void readimage(FILE *heps, int (*image)[maxcols], int *rows, int *cols)
{
	char c;
	int newcols = 0;
	
	*rows = 0;
	*cols = 0;

	while ((fscanf(heps, "%c", &c) != EOF) && *rows < maxrows){
		if (c >= '0' && c <= '4') {
			if(newcols < maxcols){
				image[*rows][newcols++] = c - '0';
						
			}
		}
		else if (c == '\r') {
			continue;
		}
		else if (c == '\n') {
					
			if (*rows == 0)
				*cols = newcols;

			(*rows)++;
			newcols = 0;
					
		}	
		else {
			(*rows)++;
					
		}
	}
			
}

void saveimage(FILE *heps, int (*image)[maxcols], int rows, int cols)
{
	printf("saveimage:rows %d,cols %d\n", rows, cols);
	for (int i = 0; i < rows; ++i) {
		for (int k = 0; k < cols; ++k)
			fprintf(heps, "%d", image[i][k]);

		fprintf(heps, "\n");
	}
	printf("Image saved.\n");
}

int main() {
	FILE *heps;
	int image[maxrows][maxcols];
	int rows = 0, cols = 0;
	int choice, choice2;
	char newfile[100];
	int iseditted = 0;
	while(choice != '0') {
		printf("1. Load image\n");
		printf("2. Display image\n");
		printf("3. Editing Menu\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		fflush(stdin);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				heps = fopen("testimage.txt", "r");

				if(heps == NULL) {
					printf("Error opening file!\n");
					return 1;
				}

				readimage(heps, image, &rows, &cols);
				fclose(heps);
				printf("File loaded!, rows %d, cols %d\n", rows, cols);
				break;

			case 2:
				printf(" \n");
				displayimage(image, rows, cols);

			break;
			case 3:
				do {
					printf("Editing Menu:\n");
					printf("1. Crop\n");
					printf("2. Brighten image\n");
					printf("3. Dim image\n");
					printf("4. Save image to file\n");
					printf("5. Back to Menu\n");
					printf("Enter choice: ");
					fflush(stdin);
					scanf("%d", &choice2);

					switch (choice2) {
						case 1: 
							cropimage(image, &rows, &cols);
							iseditted=1;                                   
							printf("Image cropped:\n");
							displayimage(image, rows, cols);
							break;
							
						case 2:
							
							brightenimage(image, rows, cols);
							iseditted=1;
							printf("Brightened Image:\n");
							displayimage(image, rows, cols);
							break;
							
						case 3:
							
							dimimage(image, rows, cols);
							iseditted=1;
							printf("Dimmed Image:\n");
							displayimage(image, rows, cols);
							break;
	
						case 4:
							if(iseditted) {
								printf("Enter the file name to save: ");
								scanf("%s", newfile);
								heps = fopen(newfile, "w");
								if(heps == NULL) {
									printf("Error opening file.\n");
									return 1;
								}
								saveimage(heps, image, rows, cols);
								fclose(heps);
							} 
							else
							   	printf("Edit the image first.\n");

							break;
						case 5:                                     
						break; 							
						default:
							printf("Invalid choice!\n");
						break;

					}	

				} while (choice2 != 5);
				break;

			case 5:
				return 0;

			default:
				printf("Invalid choice!\n");
				return 1;
		}
	}
	printf("Goodbye");
	return 0;
}
