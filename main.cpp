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

int main()
{
	// filter();
	// cout << "0" << endl;
	NCUSketch cusketch(1 << 19, 8, 1, 3);

	// cout << "1" << endl;

	NCMSketch cmsketch(1 << 19, 8, 1, 3);
	NCMLSketch cmlsketch(1 << 19, 8, 1, 3);
	NCSketch csketch(1 << 19, 8, 1, 3);
	PFSketch_cu pfsketch(1 << 19, 8, 2, 8);
	// cout << "1.5" << endl;

	FILE *file_FlowTraffic = fopen(filename_FlowTraffic, "r");
	FILE *file_result_CM = fopen(filename_result_CM, "w");
	FILE *file_result_CU = fopen(filename_result_CU, "w");
	FILE *file_result_CML = fopen(filename_result_CML, "w");
	FILE *file_result_C = fopen(filename_result_C, "w");
	FILE *file_result_PF = fopen(filename_result_PF, "w");

    char str[1000];
    int val, valCM, valCU, valCML, valC, valPF;

	// cout << "2" << endl;

    for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic, "%s %d", str, &val);
        cmsketch.Insert((const char *)str);
        cusketch.Insert((const char *)str);
        cmlsketch.Insert((const char *)str);
        csketch.Insert((const char *)str);
        pfsketch.Insert((const char *)str);
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
        valPF = pfsketch.Query((const char *)str);
        fprintf(file_result_CM, "%d\t%d\n", val, valCM);
        fprintf(file_result_CU, "%d\t%d\n", val, valCU);
        fprintf(file_result_CML, "%d\t%d\n", val, valCML);
        fprintf(file_result_C, "%d\t%d\n", val, valC);
        fprintf(file_result_PF, "%d\t%d\n", val, valPF);
    }

    fclose(file_FlowTraffic);
    fclose(file_result_CM);
    fclose(file_result_CU);
    fclose(file_result_CML);
    fclose(file_result_C);
    fclose(file_result_PF);
	return 0;
}