%%cu

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int Siz = 100;
int main()
{
    for( ;Siz < 1001; Siz+=100){
    string arr[Siz];
    for (int i = 0; i < Siz; i++) {
        arr[i] = "A new report on the state of American youth says teenagers are very concerned about the direction their nation is taking. They feel the upcoming presidential election will have as big impact on their lives, as the presidential election in 2004.The survey released by the Horatio Alger Association of Distinguished Americans looked at the views of more than 1000 young people aged 13 to l9. According to that study, 62 percent of the U.S. teens believed the Kerry-Bush election in 2004 would make a large difference in the direction of the country and 70 percent said they cared who would win.Allan Rivlin, a senior vice president with Peter Hart Research, says today young people are more involved with their society and know what is happening. He notes, They are paying attention to the Iraq war. The young people surveyed also expressed concern over the employment and recession situation in America. But Rivlin says their greatest area of apprehension has to do with issues like gay marriage and abortion . These social issues topped the list of concerns among the young.One promising revelation of Rivlin’s report is that the U.S. teenagers have a high opinion of their parents in general. In the report, 77 percent of teens say they get along with their parents or guardians. They have a great deal of admiration for their parents as well.Overwhelmingly students say they have good relations with their family, says Rivlin, and when we ask them to pick a role model, it’s not sports stars or entertainment figures that get picked most. Fifty-one percent say their parents are their role model. Also notable, the researcher says, is the fact that for the first time we see dads catching up with moms in terms of who the young people name as their role modelsRivlin says, the survey suggests that even though American youth is facing great pressure to conform, to get good grades, and to look a certain way. But still, the young find the support networks they need."; 
    }
    printf("Size = %d; Symbols: %d\n", Siz, sizeof(arr));
    string host_text[Siz];
    string* dev_text;

    cudaMalloc((void**)&dev_text, Siz * sizeof(string));

    for (int i = 0; i < Siz; i++)
        host_text[i] = arr[i];
    

    cudaEvent_t start, stop;
    float elapsedTime;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    cudaMemcpy(dev_text, host_text, Siz * sizeof(string), cudaMemcpyHostToDevice);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime, start, stop);

    printf("Elapsed time from CPU to GPU: %.4f millseconds\n", elapsedTime);
    float x = 1 / elapsedTime;
    printf("Speed is %.3f GB/s\n\n", (float) (sizeof(arr)) * x * 1000 / 1024 / 1024 / 1024 );
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaEvent_t start2, stop2;
    float elapsedTime2;

    cudaEventCreate(&start2);
    cudaEventCreate(&stop2);
    cudaEventRecord(start2, 0);

    cudaMemcpy(host_text, dev_text, Siz * sizeof(int),cudaMemcpyDeviceToHost);
    cudaEventRecord(stop2, 0);
    cudaEventSynchronize(stop2);
    cudaEventElapsedTime(&elapsedTime2, start2, stop2);

    printf("Elapsed time from GPU to CPU: %.4f millseconds\n", elapsedTime2);
    x = 1 / elapsedTime2;
    printf("Speed is %.3f GB/s\n\n", (float) (sizeof(arr)) * x * 1000 / 1024 / 1024 / 1024 );
    cudaEventDestroy(start2);
    cudaEventDestroy(stop2);
    cudaFree(dev_text);
    printf("______________________________\n");
    }
    printf("______________________________\n");
    return 0;
}

