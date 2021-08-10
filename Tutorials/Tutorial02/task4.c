#include <stdio.h>
#include <string.h>
#include "task4_unit_code.h"
//#include <task4_unit_code.h>

/*task4_unit_code.h*/

// function prototype
int compare_unit_code(Unitcode unitcode1, Unitcode unitcode2);
void print_output_msg(int matched);



int main(){
	
	// Declare 2 Unitcode var, and initialise them.
	Unitcode operating_system, parallel_computing;
	
	operating_system.FacID = "FIT";
	operating_system.UnitID = 2100;
	
	parallel_computing.FacID = "FIT";
	parallel_computing.UnitID = 2100;
	
	// print output msg based on 
	print_output_msg(compare_unit_code(operating_system, parallel_computing));

	return 0;
}


/* 
Given 2 unitcode, this function compares their facid and unitid if both values
are equivalent return 1, else return 0.
*/
int compare_unit_code(Unitcode unitcode1, Unitcode unitcode2){
	// strcmp:
	// return 0 is both strings are equal and return < 0 if str1 compares less than str2
	// create a if else such that, 0 -> true and not 0 --> false
	int fac_id_matched = strcmp(unitcode1.FacID, unitcode2.FacID) == 0 ? 1 : 0;

	// return 1 if matching, 0 if not matching
	int unit_code_matched = unitcode1.UnitID == unitcode2.UnitID;

	return unit_code_matched && fac_id_matched;
}



// if argument integer is 1 return equal msg else not equal msg.
void print_output_msg(int matched){

	if (matched){
		printf("Both Unitcodes are equivalent.\n");
	}else{
		printf("Both Unitcode are not equivalent.\n");
	}
}




