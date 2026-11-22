#include <cstdio>
#include <cstdlib>
#include <string>

void mandelbrotSerial(float x0, float y0, float x1, float y1, 
                      int width, int height, int startY, int numRows, 
                      int maxIterations, unsigned char* output);

void mandelbrotThread(float x0, float y0, float x1, float y1, 
                      int width, int height, int startY, int numRows, 
                      int maxIterations, unsigned char* output, int numThreads);

int main(int argc, char* argv[]) {
    int view = 1;
    int numThreads = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--view" && i + 1 < argc) {
            view = std::atoi(argv[++i]);
        } else if (arg == "--threads" && i + 1 < argc) {
            numThreads = std::atoi(argv[++i]);
        }
    }

    float x0 = -1.0f, x1 = 1.0f, y0 = -1.0f, y1 = 1.0f;
    int width = 1600, height = 1200, maxIterations = 256;

    if (view == 1) {
        x0 = -1.5f; x1 = 0.5f; y0 = -1.0f; y1 = 1.0f;
    } else if (view == 2) {
        x0 = -0.75f; x1 = -0.72f; y0 = 0.1f; y1 = 0.13f;
    }

    unsigned char* output = new unsigned char[width * height];

    if (numThreads == 0) {
        mandelbrotSerial(x0, y0, x1, y1, width, height, 0, height, maxIterations, output);
    } else {
        mandelbrotThread(x0, y0, x1, y1, width, height, 0, height, maxIterations, output, numThreads);
    }

    FILE* file = fopen("mandelbrot-serial.ppm", "wb");
    if (file) {
        fprintf(file, "P6\n%d %d\n255\n", width, height);
        for (int i = 0; i < width * height; ++i) {
            fputc(output[i], file);
            fputc(output[i], file);
            fputc(output[i], file);
        }
        fclose(file);
    }

    delete[] output;
    return 0;
}