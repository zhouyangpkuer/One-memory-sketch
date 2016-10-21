#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "cmsketch.h"
#include "csketch.h"
#include "cusketch.h"
#include "cmlsketch.h"
#include "filter.h"
using namespace std;

const char * filename_FlowTraffic = "../../../new/sourceData/insert_uni_filted.txt";
const char * filename_result_CM = "../../result/resCM.txt";
const char * filename_result_CU = "../../result/resCU.txt";
const char * filename_result_CML = "../../result/resCML.txt";
const char * filename_result_C = "../../result/resC.txt";

int main()
{
	// filter();
	// cout << "0" << endl;
	CUSketch cusketch(1 << 14, 8, 1, 3);

	// cout << "1" << endl;

	CMSketch cmsketch(1 << 14, 8, 1, 3);
	CMLSketch cmlsketch(1 << 14, 8, 1, 3);
	CSketch csketch(1 << 14, 8, 1, 3);
	// cout << "1.5" << endl;

	FILE *file_FlowTraffic = fopen(filename_FlowTraffic, "r");
	FILE *file_result_CM = fopen(filename_result_CM, "w");
	FILE *file_result_CU = fopen(filename_result_CU, "w");
	FILE *file_result_CML = fopen(filename_result_CML, "w");
	FILE *file_result_C = fopen(filename_result_C, "w");

    char str[1000];
    int val, valCM, valCU, valCML, valC;

	// cout << "2" << endl;

    for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        cmsketch.Insert((const char *)str);
        cusketch.Insert((const char *)str);
        cmlsketch.Insert((const char *)str);
        csketch.Insert((const char *)str);
    }
    rewind(file_FlowTraffic);

	// cout << "3" << endl;

	for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        valCM = cmsketch.Query((const char *)str);
        valCU = cusketch.Query((const char *)str);
        valCML = cmlsketch.Query((const char *)str);
        valC = csketch.Query((const char *)str);
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        fprintf(file_result_CU, "%d\t%d\n", val, valCU);
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);
        fprintf(file_result_C, "%d\t%d\n", val, valC);
    }

    fclose(file_FlowTraffic);
    fclose(file_result_CM);
    fclose(file_result_CU);
    fclose(file_result_CML);
    fclose(file_result_C);
	return 0;
}