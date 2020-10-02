#include "vector.h"
namespace VectMath {


	vector sum(vector a, vector b)
	{
		vector result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		return result;
	}

	vector mult(vector a, vector b)
	{
		vector result;
		result.x = a.x * b.x;
		result.y = a.y * b.y;
		return result;
	}

	vector mult(vector a, float b)
	{
		vector result;
		result.x = a.x * b;
		result.y = a.y * b;
		return result;
	}
}