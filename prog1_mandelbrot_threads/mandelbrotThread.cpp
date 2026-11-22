#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

void mandelbrotSerial(float x0, float y0, float x1, float y1, 
                      int width, int height, int startY, int numRows, 
                      int maxIterations, unsigned char* output);

void mandelbrotRow(float x0, float y0, float x1, float y1, int width, int height, 
                   int y, int maxIterations, unsigned char* output);

void workerThreadStartInterleaved(float x0, float y0, float x1, float y1,
                                  int width, int height, int startY, int numRows,
                                  int maxIterations, unsigned char* output, 
                                  int threadId, int numThreads) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int y = startY + threadId; y < startY + numRows; y += numThreads) {
        mandelbrotRow(x0, y0, x1, y1, width, height, y, maxIterations, output);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "  [Thread " << threadId << "] Time: " << diff.count() << " sec" << std::endl;
}

void mandelbrotThread(float x0, float y0, float x1, float y1, 
                      int width, int height, int startY, int numRows, 
                      int maxIterations, unsigned char* output, int numThreads) {
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(workerThreadStartInterleaved, 
                                      x0, y0, x1, y1, width, height, 
                                      startY, numRows, maxIterations, output, 
                                      i, numThreads));
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
}