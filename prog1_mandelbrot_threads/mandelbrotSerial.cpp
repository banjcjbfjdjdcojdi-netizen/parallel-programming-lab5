#include <cstdio>
#include <cmath>

void mandelbrotSerial(float x0, float y0, float x1, float y1, 
                      int width, int height, int startY, int numRows, 
                      int maxIterations, unsigned char* output) {
    
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

    for (int j = startY; j < startY + numRows; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = x0 + i * dx;
            float y = y0 + j * dy;

            int index = j * width + i;
            float cr = x;
            float ci = y;
            float zr = 0.0f;
            float zi = 0.0f;
            int iter = 0;

            while (iter < maxIterations && (zr * zr + zi * zi) < 4.0f) {
                float temp = zr * zr - zi * zi + cr;
                zi = 2.0f * zr * zi + ci;
                zr = temp;
                iter++;
            }

            output[index] = (unsigned char)((iter * 255) / maxIterations);
        }
    }
}

void mandelbrotRow(float x0, float y0, float x1, float y1, int width, int height, 
                   int y, int maxIterations, unsigned char* output) {
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;
    float ci = y0 + y * dy;
    
    for (int i = 0; i < width; ++i) {
        float cr = x0 + i * dx;
        float zr = 0.0f;
        float zi = 0.0f;
        int iter = 0;

        while (iter < maxIterations && (zr * zr + zi * zi) < 4.0f) {
            float temp = zr * zr - zi * zi + cr;
            zi = 2.0f * zr * zi + ci;
            zr = temp;
            iter++;
        }
        int index = y * width + i;
        output[index] = (unsigned char)((iter * 255) / maxIterations);
    }
}