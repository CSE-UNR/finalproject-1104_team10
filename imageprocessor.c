//Author Eli Biggs
#include <stdio.h>

#define maxrows 200
#define maxcols 200

void readimage(FILE *heps, int (*image)[maxcols], int *rows, int *cols) {
    int next;

    *rows = 0;
    *cols = 0;

    while ((next = getc(heps)) != EOF && *rows < maxrows && *cols < maxcols) {
        if (next == '\n') {
            (*rows)++;
            *cols = 0;
        } else if (next >= '0' && next <= '4') {
            image[*rows][*cols] = next - '0';
            (*cols)++;
        }
   		 }
	}
void dimimage(int (*image)[maxcols], int rows, int cols){
}
void brightenimage(int (*image)[maxcols], int rows, int cols){
}

void displayimage(int (*image)[maxcols], int rows, int cols) {
   
   for (int i = 0; i <= rows; i++) {
       for (int k = 0; k < maxcols; k++) {
           printf("%d", image[i][k]);
       }
        printf("\n");
    		}
	}

void crop(int (*image)[maxcols], int *rows, int *cols) {
    int toprow, bottomrow, leftcol, rightcol;
    
    printf("Enter number of rows to crop from the top: ");
    scanf("%d", &toprow);
    printf("Enter number of rows to crop from the bottom: ");
    scanf("%d", &bottomrow);
    printf("Enter number of columns to crop from the left: ");
    scanf("%d", &leftcol);
    printf("Enter number of columns to crop from the right: ");
    scanf("%d", &rightcol);
    
    if (toprow + bottomrow <= *rows && leftcol + rightcol <= *cols) {
        *rows -= (toprow + bottomrow);
        *cols -= (leftcol + rightcol);
        
     
        for (int i = toprow; i < *rows; i++) {
            for (int k = leftcol; k < *cols; k++) {
                image[i-toprow][k-leftcol] = image[i][k];
            }
        }
        
        
    } else {
        printf("Bad crop try again.\n");
    }
}

void saveimage(FILE *heps, int (*image)[maxcols], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
   		 for (int k = 0; k < cols; k++) {
         fprintf(heps, "%d", image[i][k]);
       }
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
	while(choice != '0'){
    printf("1. Load image\n");
    printf("2. Display image\n");
    printf("3. Editing Menu\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            heps = fopen("testimage.txt", "r");
            if (heps == NULL) {
                printf("Error opening file!\n");
                return 1;
            }

            readimage(heps, image, &rows, &cols);
            fclose(heps);
            printf("File loaded!\n");
            break;
        case 2:
            printf("image:\n");
            displayimage(image, rows, cols);
            break;
        case 3:
            do {
                printf("Editing Menu:\n");
                printf("1. Crop\n");
                printf("2. Save image to file\n");                //change this when adding more options like dim
                printf("3. Back to Menu\n");
                printf("Enter choice: ");
                scanf("%d", &choice2);

                switch (choice2) {
                    case 1: 
                 crop(image, &rows, &cols);
                        iseditted = 1;                                   //prob remove this restriction
                        printf("Image cropped:\n");
                        displayimage(image, rows, cols);
                        break;
                    case 2:
                        if (iseditted) {
                            printf("Enter the file name to save: ");
                            scanf("%s", newfile);
                            heps = fopen(newfile, "w");
                            if (heps == NULL) {
                                printf("Error opening file.\n");
                                return 1;
                            }
                            saveimage(heps, image, rows, cols);
                            fclose(heps);
                            } 
                            else {
                            printf("Edit the image first.\n");
                       	 	}
             break;
	case 3:                                                        //sidenote: fix indenting before monday
       break; 							// yeah no thats gunna be a monday thing, sorry
    	  default:
      	printf("Invalid choice!\n");
                        break;
                }
            } while (choice2 != 3);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
}
printf("Goodbye");
    return 0;
}
