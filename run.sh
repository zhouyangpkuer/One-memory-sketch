#!/bin/bash
# ./main	250000	8	1	3
# ./main	125000	16	1	3
# ./main	83340	24	1	3

# ./main	750000	8	1	3
# echo -e "750000	8	1	3 finish 1"

# ./main	375000	16	1	3
# echo -e "375000	16	1	3 finish 2"

# ./main	250000	24	1	3
# echo -e "250000	24	1	3 finish 3"

# ./main	1000000	8	3	3
# echo -e "finish 4"

# ./main	187500	32	1	3

# ./main	93750	64	1	3
rm -f ../result/error_analysis.txt

./main	93750	64	6	6 >> ../result/error_analysis.txt
./main	93750	64	8	8 >> ../result/error_analysis.txt
./main	93750	64	10	10 >> ../result/error_analysis.txt
./main	93750	64	12	12 >> ../result/error_analysis.txt
./main	93750	64	14	14 >> ../result/error_analysis.txt
./main	93750	64	16	16 >> ../result/error_analysis.txt

./main	187500	32	6	6 >> ../result/error_analysis.txt
./main	187500	32	8	8 >> ../result/error_analysis.txt
./main	187500	32	10	10 >> ../result/error_analysis.txt
./main	187500	32	12	12 >> ../result/error_analysis.txt
./main	187500	32	14	14 >> ../result/error_analysis.txt
./main	187500	32	16	16 >> ../result/error_analysis.txt



