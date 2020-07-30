#include "../src/jsonvalidation.h"
#include <stdio.h>
#include <tap.h>

int main () {
    int no_files = 7;
    char* files[] = {
        "../data/map3x3-syntaxproblem.json",
        "../data/map3x3-badincoming.json",
        "../data/map3x3-badroot.json",
        "../data/map3x3-duplicateid.json",
        "../data/map3x3-missinglayers.json",
        "../data/map3x3-badoutgoing.json",
        "../data/map3x3.json",
    };
    int validation_result[] = {
        2,
        18,
        3,
        30,
        10,
        20,
        0
    };
    
    for (int i = 0; i < no_files; ++i) {
        FILE *input = fopen(files[i], "r");
        int error_no = jsonvalidation_validate_file(input);
        
        printf("Validation du fichier %s\n", files[i]);
        printf("Code d'erreur recherché : %i\n", validation_result[i]);
        printf("Code d'erreur reçu de la validation : %i", error_no);
        printf("\n\n");
        
        fclose(input);
    }
    
    done_testing();
}
