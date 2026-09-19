#include <stdio.h>

int nums[4];


int main(void){
	int id=0;
	int N, i, sum=0;
	scanf("%d",&N);
	int res = -999999999;
	for(i = 0; i < N; i++){
		if(i >= 4) sum -= nums[i%4];
		scanf("%d",&nums[i%4]);
		sum += nums[i%4];
		if(i >= 3 && res < sum) res = sum;
	}
	printf("%d\n", res);
	return 0;
}
