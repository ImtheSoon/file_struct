#include <stdio.h>

typedef struct {
	int number;
	char name[10];
	char phone[10];
	
}Person;
 
Person list[]={ 
	{201811111,"강감찬","33730067"},{201811122,"김  구","84512191"},{201811133,"김유신","31501722"},{201811144,"문익점","73384391"},
	{201811155,"안중근","28437551"},{201811166,"유관순","78265390"},{201811177,"윤동주","77195632"},{201811188,"윤봉길","99817456"},
	{201811199,"이순신","53741121"},{201811100,"홍길동","77839216"},
};

int main (void){
	size_t size, count;
	Person sperson;
	FILE *fp=NULL;
	fp=fopen("student_master.bin","wb");
	if(fp==NULL){
		fprintf(stderr,"마스터 파일을 열 수 없습니다.");
		return 1; 
	} 
	
	size = sizeof(list[0]);
	count = sizeof(list)/sizeof(list[0]);
	fwrite(list, size, count, fp);
	fclose(fp);
	fp =fopen("student_master.bin", "rb");
	while(1){
		fread(&sperson, sizeof(Person), 1, fp);
		if(feof(fp))
			break;
			printf("학번은 %d 이름은 %s 전화번호는 %s입니다.\n",sperson.number,sperson.name,sperson.phone);
	}
		fclose(fp);
		return 0;
	
}
