#ifndef _FILTER_H
#define _FILTER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include "params.h"
// #include <iterator>
using namespace std;

// vector<string> query_str;
map<string, int> mp;

const char *filename_FlowTraffic_raw = "../../../new/sourceData/insert_zipf.txt";
const char *filename_FlowTraffic_query = "../../../new/sourceData/query_zipf.txt";

const char *filename_FlowTraffic_filted = "../../../new/sourceData/insert_zipf_filted.txt";

void filter()
{
    FILE *file_FlowTraffic_raw = fopen(filename_FlowTraffic_raw, "r");
    FILE *file_FlowTraffic_query = fopen(filename_FlowTraffic_query, "r");

    FILE *file_FlowTraffic_filted = fopen(filename_FlowTraffic_filted, "w");
    
    char str[1000];
    string user;
    int val;

    for(int i = 0; i < N_INSERT; i++)
    {
        fscanf(file_FlowTraffic_raw, "%s %d", str, &val);
        user = string(str);
        mp[user]++;
    }

    for(int i = 0; i < N_QUERY; i++)
    {
        fscanf(file_FlowTraffic_query, "%s", str);
        user = string(str);
        val = mp[user];
        fprintf(file_FlowTraffic_filted, "%s %d\n", user.c_str(), val);
    }

    fclose(file_FlowTraffic_raw);
    fclose(file_FlowTraffic_filted);
    return ;
}

#endif//_FILTER_H;