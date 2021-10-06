#include<stdio.h>

typedef struct {
	char code;
	int num;
	char name[10];
	char phone[10];
}TPerson;

TPerson list[] = {
	{'C',201811133,"김좌진","66781833"}, {'D',201811144,"문익점","73384391"}, 
	{'I',201811155,"최  영","71345219"}, {'I',201811555,"장보고","85432855"},
	};

int main(void){
	size_t size, count;
	TPerson sperson;
	FILE *fp=NULL;
	fp=fopen("trans.bin","wb");
	if(fp==NULL){
		fprintf(stderr,"마스터 파일을 열 수 없습니다.");
		return 1; 
	} 
	
	size = sizeof(list[0]);
	count = sizeof(list)/sizeof(list[0]);
	fwrite(list, size, count, fp);
	fclose(fp);
	fp =fopen("trans.bin", "rb");
	while(1){
		fread(&sperson, sizeof(TPerson), 1, fp);
		if(feof(fp))
			break;
			printf("코드는 %c 학번은 %d 이름은 %s 전화번호는 %s입니다.\n",sperson.code,sperson.num,sperson.name,sperson.phone);
	}
		return 0;
	
}
