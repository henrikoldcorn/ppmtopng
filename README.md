# ppmtopng

Usage: 
  ppmtopng inputfile.ppm outputfile.png
  
 Warning: outputfile.png will be overwritten!


ppmtopng uses lodepng by Lode Vandevenne, http://lodev.org/lodepng/

The program assumes data-only ppm files with a P3 header, i.e. no comments, invalid files or empty lines. This program has absolutely no error-checking; if the file should end prematurely, or contain unexpected data, bad things may happen.  

For an example see test.ppm (and .png). 

Why might this be useful? I use it so then other programs (i.e. raymarching, raytracing etc.) don't have to worry about outputting in a decently small and more complicated format. ppmtopng then converts to a rather smaller but still lossless image. A simple script can tie everything together. Example: fancy_graphics_program > out.ppm && ppmtopng out.ppm out.png
