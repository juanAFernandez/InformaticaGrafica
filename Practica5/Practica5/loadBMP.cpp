/*
 * LoadBMP.cpp: Load a 24-bit BMP image into imageData array.
 */
#include <stdio.h>
#include <stdlib.h>


#pragma pack(2)  // 2 byte packing
typedef struct {
   unsigned char magic1;   // 'B'
   unsigned char magic2;   // 'M'
   unsigned int size;      // File size
   unsigned short int reserved1, reserved2;
   unsigned int pixelOffset; // offset to image data
} Header;

#pragma pack() // Default packing
typedef struct {
   unsigned int size;    // Size of this info header
   int cols, rows;       // cols and rows of image
   unsigned short int planes;
   unsigned short int bitsPerPixel; // number of bits per pixel
   unsigned int compression;
   unsigned int cmpSize;
   int xScale, yScale;
   unsigned int numColors;
   unsigned int importantColors;
} InfoHeader;

// Destination to be defined in the calling program
extern unsigned char *imageData;
extern int imageRows, imageCols;

void loadBMP(char *filename) {
   Header header;
   InfoHeader infoHeader;
   FILE *fin;
   fin = fopen(filename, "rb+");
   if (fin == NULL) {
      printf("Error opening image file: %s\n", filename);
      exit(1);
   }

   // Process header
   fread(&header, sizeof(header), 1, fin);
   // Test if this is really a BMP file
   if (!((header.magic1 == 'B') && (header.magic2 == 'M'))) {
      printf("Not a valid BMP file: %s\n", filename);
      exit(1);
   }

   // Process Info Header
   fread(&infoHeader, sizeof(infoHeader), 1, fin);
   // Test if this is a 24-bit uncompressed BMP file
   if (!((infoHeader.bitsPerPixel == 24) && !infoHeader.compression)) {
      printf("Cannot handle this type of BMP file\n");
      exit(1);
   }

   imageRows = infoHeader.rows;
   imageCols = infoHeader.cols;
   imageData = (unsigned char*)malloc(3 * sizeof(unsigned char) * infoHeader.cols * infoHeader.rows);
   int count = 0;
   for (int row = 0; row < infoHeader.rows; row++) {
      for (int col = 0; col < infoHeader.cols; col++) {
         fread(imageData + count + 2, sizeof(unsigned char), 1, fin); // blue
         fread(imageData + count + 1, sizeof(unsigned char), 1, fin); // green
         fread(imageData + count, sizeof(unsigned char), 1, fin);     // red
         count = count + 3;
      }
   }
}
