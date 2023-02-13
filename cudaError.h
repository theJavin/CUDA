//#include "../cudaError.h"
void errorCheck(const char *file, int line)
{
	cudaError_t  error;
	error = cudaGetLastError();

	if(error != cudaSuccess)
	{
		printf("\n CUDA ERROR: %s = %s\n", cudaGetErrorString(error), file, line);
		exit(0);
	}
}