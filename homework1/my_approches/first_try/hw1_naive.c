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
	int* idx_arr = (int*)malloc(sizeof(int)*s_len);
	for (int i = 0; i < s_len; i++){
		idx_arr[i] = -1;
	}
	for (int i = 0; i < p_len; i++){
		if(pattern[i] == '\t' || pattern[i] == '\n') {
			pattern[i] = '\0';
			p_len--;
		}
	}
	int cnt = naive(s_len, p_len, idx_arr);
	printf("%d\n", cnt);
	
	int i = 0;
	while (idx_arr[i] != -1){
		printf("%d ", idx_arr[i++]);
	}

	
	return 0;
}

int naive(int s_len, int p_len, int idx_arr[]){
	int cnt = 0;
	int s_idx = 0;
	int head_m = 0;
	int i = 0; int j = 0; int i_start = 0;
	for (; string[i_start] != '\0'; i_start++){
		i = i_start;
		
		for(; pattern[j] != '\0'; j++){		
			if(string[i] == pattern[j]){
				if(head_m != 1){
					s_idx = i;
					head_m = 1;
				}
				i++;
			}
			else{
				j = 0;
				head_m = 0;
				break;
			}
		}
		if (pattern[j] == '\0'){
			idx_arr[cnt] = s_idx;
			head_m = 0;
			cnt++;
			j = 0;
			//printf("%d\n", s_idx);
		}
	}
	return cnt;
}
