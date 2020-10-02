#pragma once
namespace VectMath
{

    struct vector {
        float x, y = 0;
    };

     vector sum(vector a, vector b);
     vector mult(vector a, vector b);
     vector mult(vector a, float b);


}

