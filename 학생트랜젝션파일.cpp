#include<stdio.h>

typedef struct {
	char code;
	int num;
	char name[10];
	char phone[10];
}TPerson;

TPerson list[] = {
	{'C',201811133,"������","66781833"}, {'D',201811144,"������","73384391"}, 
	{'I',201811155,"��  ��","71345219"}, {'I',201811555,"�庸��","85432855"},
	};

int main(void){
	size_t size, count;
	TPerson sperson;
	FILE *fp=NULL;
	fp=fopen("trans.bin","wb");
	if(fp==NULL){
		fprintf(stderr,"������ ������ �� �� �����ϴ�.");
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
			printf("�ڵ�� %c �й��� %d �̸��� %s ��ȭ��ȣ�� %s�Դϴ�.\n",sperson.code,sperson.num,sperson.name,sperson.phone);
	}
		return 0;
	
}
