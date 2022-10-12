# Filter_Image
This is the product of learning in CS50-Harvard.
When running the code, the image will be changed into the expected filter.

Command to run the code:
Run this command first: 
  $ make filter

Then:
To change the image to grayscale:
  $ ./filter -g INFILE.bmp OUTFILE.bmp

To change the image to sepia:
  $ ./filter -s INFILE.bmp OUTFILE.bmp

To reflect the image:
  $ ./filter -r INFILE.bmp OUTFILE.bmp

To blur the image:
  $ ./filter -b INFILE.bmp OUTFILE.bmp

Example: 
$ ./filter -g images/yard.bmp out.bmp
Change the yard.bmp to grayscale and export to out.bmp
