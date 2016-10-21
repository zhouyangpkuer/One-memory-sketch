#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "cmsketch.h"
#include "csketch.h"
#include "cusketch.h"
#include "cmlsketch.h"
#include "cmsketch_nonconflict.h"
#include "csketch_nonconflict.h"
#include "cusketch_nonconflict.h"
#include "cmlsketch_nonconflict.h"
#include "pfsketch_cu.h"
#include "filter.h"
using namespace std;

const char * filename_FlowTraffic = "../insert_uni_filted.txt";
const char * filename_result_CM = "../result/resCM.txt";
const char * filename_result_CU = "../result/resCU.txt";
const char * filename_result_CML = "../result/resCML.txt";
const char * filename_result_C = "../result/resC.txt";
const char * filename_result_PF = "../result/resPF.txt";

// #define CM
// #define CU
// #define CML
// #define C
#define PF

int main()
{
    FILE *file_FlowTraffic = fopen(filename_FlowTraffic, "r");
    
#ifdef CM
    FILE *file_result_CM = fopen(filename_result_CM, "w");
    NCMSketch cmsketch(1 << 19, 8, 1, 3);
#endif

#ifdef CU
    FILE *file_result_CU = fopen(filename_result_CU, "w");
    NCUSketch cusketch(1 << 19, 8, 1, 3);
#endif

#ifdef CML
    FILE *file_result_CML = fopen(filename_result_CML, "w");
	NCMLSketch cmlsketch(1 << 19, 8, 1, 3);
#endif

#ifdef C
    FILE *file_result_C = fopen(filename_result_C, "w");
	NCSketch csketch(1 << 19, 8, 1, 3);
#endif 

#ifdef PF
    FILE *file_result_PF = fopen(filename_result_PF, "w");
	PFSketch_cu pfsketch(1 << 19, 8, 2, 8);
#endif

    char str[1000];
    int val, valCM, valCU, valCML, valC, valPF;

    for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        for(int j = 0; j < val; j++)
        {
            #ifdef CM
            cmsketch.Insert((const char *)str);
            #endif 

            #ifdef CU
            cusketch.Insert((const char *)str);
            #endif

            #ifdef CML
            cmlsketch.Insert((const char *)str);
            #endif

            #ifdef C
            csketch.Insert((const char *)str);
            #endif

            #ifdef PF
            pfsketch.Insert((const char *)str);
            #endif
        }
    }
    rewind(file_FlowTraffic);

	for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        #ifdef CM   
        valCM = cmsketch.Query((const char *)str);
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        #endif

        #ifdef CU
        valCU = cusketch.Query((const char *)str);
        fprintf(file_result_CU, "%d\t%d\n", val, valCU);
        #endif 

        #ifdef CML
        valCML = cmlsketch.Query((const char *)str);
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);
        #endif

        #ifdef C
        valC = csketch.Query((const char *)str);
        fprintf(file_result_C, "%d\t%d\n", val, valC);
        #endif

        #ifdef PF
        valPF = pfsketch.Query((const char *)str);
        fprintf(file_result_PF, "%d\t%d\n", val, valPF);
        #endif
    }

#ifdef CM
    fclose(file_result_CM);
#endif

#ifdef CU
    fclose(file_result_CU);
#endif

#ifdef CML
    fclose(file_result_CML);
#endif

#ifdef C
    fclose(file_result_C);
#endif 

#ifdef PF
    fclose(file_result_PF);
#endif

	return 0;
}