/*
 * readPGM.c
 *
 *  Created on: Apr 12, 2014
 *      Author: oo
 */

#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"
/*
char * szFileName : name of image file, [must not null value]
int **image : one dimension array for image information,
              [memory all by this function]
int * row : number of row, [must not null value]
int * col : number of column, [must not null value]
int * maxcolor : maximum value of color number, such as 256
                 means 0-255, [must not null value]
return : 0-success, 1 : failed
*/

int*  getImage(char* szFileName, int* row, int* col ,int* maxcolor)
{
   *row = 0;
   *col = 0;
   int i;
   int j;
   //int lineFlag = 0; //0-Empty line
   char ch;
   //char pre=' ';
   FILE * fpText;
   int* image;

   if ((NULL == szFileName)
       || (NULL == row)
       || (NULL == col)
       || (NULL == maxcolor))
   {

         printf("\aERROR error parameter. \a\n");
       return NULL;
   }

   fpText = fopen(szFileName, "rb");
   if( fpText == NULL )
   {
      printf("\aERROR can not open image file. \a\n");
      return NULL;
   }

   ch = fgetc(fpText); //skip 'p'
   if ((ch != 'p') && (ch != 'P'))
   {
      printf("\aERROR invalid image file(%s). \a\n", szFileName);
      return NULL;

   }

   ch = fgetc(fpText); //skip '5/6'
   ch = fgetc(fpText); //skip 'space'

   //get width
   fscanf(fpText,"%d",col);
   ch = fgetc(fpText); //skip 'enter'
   fscanf(fpText,"%d",row);
   ch = fgetc(fpText); //skip 'enter'
   fscanf(fpText,"%d",maxcolor);
   ch = fgetc(fpText); //skip 'enter'


      (*maxcolor)++;

   if ((*row <= 0) || (*col <= 0) || (*maxcolor <= 0))
   {
      printf("\aERROR invalid image file(%s). \a\n", szFileName);
      return NULL;
   }

   image = (int*)malloc(sizeof( int) * (*col) * (*row) );

   if( (image) == NULL )
   {
      printf("\aERROR alloc memory error. \a\n");
      return NULL;
   }

   for (i = 0; i < *row; i++)
   {
     for (j = 0; j < *col; j++)
     {

       ((image)[i*(*col) + j] = fgetc(fpText));
       //printf("%d ", ((image)[i*(*col) + j] ));
     }
   }

   if ( fclose( fpText ) == EOF )
   {
      printf( "\aERROR closing file (%s) \n",szFileName) ;
     free(image);
      return NULL;
   }      // fclose( fpText );

   return image;
}


