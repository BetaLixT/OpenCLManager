__kernel void initializeArray(__global int* input, __global int* output, const unsigned int count) {
   int i = get_global_id(0);                                                  
   if(i < count) { 
       
       for (int j = 0; j < i * 20; j++)
       {
           input[i]++;
       }
       barrier(0);

       int j = get_local_id(0);
       
       
       if (j == 0)
       {
           int group = get_group_id(0);
           int size = get_local_size(0);
           output[group] = 0;

           for (int p = group * size; p < (group * size) + size && p < count; p++)
           {
               output[group] += input[p];
           }
       }
    }                                             
}
