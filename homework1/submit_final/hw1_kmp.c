#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S_MAX 10000001
#define P_MAX 3001
char string[S_MAX];
char pattern[P_MAX];

int* fail(int p_len);
int match(int s_len, int p_len, int failure[], int idx_arr[]);

int main(){
	FILE *fp_string = fopen("string.txt", "r");
	FILE *fp_pat = fopen("pattern.txt","r");
	if (fp_string == NULL){
		printf("ERROR : string.txt file doesn't exist");
		exit(1);
	}
	if (fp_pat == NULL){
		printf("ERROR : pattern.txt file doesn't exist");
		exit(1);
	}
	fgets(string, sizeof(string), fp_string);
	fgets(pattern, sizeof(pattern), fp_pat);

	int s_len = strlen(string);
	int p_len = strlen(pattern);
    for (int i = 0; i < s_len; i++){//trim newline
		if(string[i] == '\t' || string[i] == '\n') {
			string[i] = '\0';
		}
	}
    for (int i = 0; i < p_len; i++){
		if(pattern[i] == '\t' || pattern[i] == '\n') {
			pattern[i] = '\0';
		}
	}
    s_len = strlen(string);
    p_len = strlen(pattern);

	int* idx_arr = (int*)malloc(sizeof(int)*s_len);
	for (int i = 0; i < s_len; i++){
		idx_arr[i] = -1;
	}
    
    int* failure = fail(p_len);
    int num = match(s_len, p_len, failure, idx_arr);

    FILE *fp_out = fopen("result_kmp.txt", "w");
    fprintf(fp_out,"%d\n", num);
    for(int i = 0; i < num; i++){
        fprintf(fp_out, "%d ", idx_arr[i]);
    }

    fclose(fp_string);
	fclose(fp_pat);
	fclose(fp_out);
    return 0;
}


int* fail(int p_len){
    int* failure = (int*)malloc(sizeof(int)*p_len);
    failure[0] = -1;
    int i = -1; int j = 1;
    while(j < p_len){
        while(pattern[i+1] != pattern[j]){
            if (i == -1) {
                break;
            }
            i = failure[i];    
        }
        if(pattern[j] == pattern[i+1]){
            failure[j++] = i + 1;
            i++;
        }
        else{
            failure[j++] = -1;
        }
    }
    return failure;
}

int match(int s_len, int p_len, int failure[], int idx_arr[]){
    int i = 0; int j = 0; int i_start = -1; int cur = 0;

    while(i < s_len){
        if(string[i] == pattern[j]){
            if(i_start == -1) i_start = i;
            i++; j++;
        }
        else if(j == 0){
            i++;
            i_start = -1;
        }         
        else   {
            j = failure[j-1] + 1;
            i_start = i - j;
        }
            
        if(p_len == j){
            idx_arr[cur++] = i_start;
            i = i_start + 1;
            i_start = -1;
            j = 0;
        }
    }
    return cur;
}
