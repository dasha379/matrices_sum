#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <fstream>

int main(){
    int n = 4, m = 5;
    int matrixSize = n * m;
    std::vector<int> a(matrixSize);
    std::vector<int> b(matrixSize);
    std::vector<int> c(matrixSize);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            a[i*m + j] = rand() % 20;
            b[i * m + j] = rand() % 20;
        }
    }

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    auto device = devices.front();

    std::string src = "__kernel void sum_matrices(__global const int * a, __global const int * b, __global int * c, const int m){ "
                "int i = get_global_id(0);"
                "int j = get_global_id(1);"
                "int index = i*m + j;"
                "c[index] = a[index] + b[index];"
                "}";
    cl::Program::Sources sources;
    sources.push_back({src.c_str(), src.length()});


    cl::Context context(device);
    cl::Program program(context, sources);
    program.build("-cl-std=CL1.2");
    cl::Kernel kernel(program, "sum_matrices");
    
    cl::Buffer bufferA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * matrixSize, a.data());
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * matrixSize, b.data());
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(int)*matrixSize);

    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, m);

    cl::CommandQueue queue(context, device);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(n, m));
    queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, sizeof(int) * matrixSize, c.data());

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            std::cout << a[i*m+ j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            std::cout << b[i*m+ j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            std::cout << c[i*m+ j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
