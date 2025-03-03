__kernel void sum_matrices(__global const int * a, __global const int * b, __global int * c, const int m){
    int i = get_global_id(0);
    int j = get_global_id(1);
    int index = i*m + j;
    c[index] = a[index] + b[index];
} 