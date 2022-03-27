#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S_MAX 10000001
#define P_MAX 3001
char string[S_MAX];
char pattern[P_MAX];


int naive(int , int, int[]);

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

	int cnt = naive(s_len, p_len, idx_arr);

	FILE *fp_out = fopen("result_naive.txt", "w");
	fprintf(fp_out, "%d\n", cnt);
	
	int i = 0;
	while (idx_arr[i] != -1){
		fprintf(fp_out, "%d ", idx_arr[i++]);
	}

	fclose(fp_string);
	fclose(fp_pat);
	fclose(fp_out);
	return 0;
}

int naive(int s_len, int p_len, int idx_arr[]){
	int cnt = 0;
	int s_idx = 0;
	int head_m = 0;
	int i = 0; int j = 0; int i_comp = 0;
	while (string[i] != '\0'){
	
		
		for(; pattern[j] != '\0'; j++){		
			if(string[i_comp] == pattern[j]){
				if(head_m != 1){
					s_idx = i;
					head_m = 1;
					i_comp = i;
				}
				i_comp++;
			}
			else{
				i_comp = ++i;
				j = 0;
				head_m = 0;
				break;
			}
		}
		if (pattern[j] == '\0'){
			idx_arr[cnt] = s_idx;
			i_comp = s_idx + 1;
			head_m = 0;
			cnt++;
			i++;
			j = 0;
		}
	}
	return cnt;
}
