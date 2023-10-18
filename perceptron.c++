#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
//index data[][0] actual value
//index data[][1] expected result
float data[][2] = { 
    { 0,  0   },
    { 2,  4   },
    { 3,  6   },
    { 4,  8   },
    { 5,  10  },
    { 6,  12  },
    { 7,  14  },
    { 8,  16  },
    { 9,  18  },
    { 10, 20  },
    };
float data2[][2] = { 
    { 0,  0   },
    { 3,  9   },
    { 6,  18   },
    { 9,  27  },
    { 12, 36  },
    { 15, 75  },
    { 18, 54  },
    { 21, 63  },

    };

float data_count = sizeof(data) / sizeof(data[0]);
float data_count2 = sizeof(data2) / sizeof(data2[0]);

float rand_float(void) {
    return (float) rand() / (float) RAND_MAX;
}

float cost(float weight) {

    float result = 0.0f;
    for(size_t i = 0; i < data_count; ++i) {
        float x = data[i][0];
        float y = x * weight;
        float d = y - data[i][1];

        result += d * d; //squaring it amplifies errors


    }

    result /= data_count;
    return result;
}

float w() {
    srand(69);
    float weight = rand_float() * 10.0f;

    float shift = 1e-3; //goal: stir the weight towards 0
    float rate = 1e-3;
    for(size_t i = 0; i < 100; ++i) {
        float differenceCost = 
        (cost(weight + shift) - cost(weight)) / shift;
        //finite difference: f(x + b) - f(x + a)
        //gives approximation of the derivative
        weight -= rate * differenceCost;
        printf("margin: %f result: %f \n", cost(weight), weight);
    }
    return weight;
}

int main (){

    float weight = w();
    for(size_t i = 0; i < data_count; ++i) {
        double actual = data[i][0] * weight;
        printf("expected: %f actual: %f \n", data[i][1], actual);
    }

    for(size_t i = 0; i < data_count2; ++i) {
        double actual = data2[i][0] * weight;
        printf("expected: %f actual: %f \n", data2[i][1], actual);
    }
    return 0;
}