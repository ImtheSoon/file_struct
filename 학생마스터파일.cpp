#include <stdio.h>

typedef struct {
	int number;
	char name[10];
	char phone[10];
	
}Person;
 
Person list[]={ 
	{201811111,"������","33730067"},{201811122,"��  ��","84512191"},{201811133,"������","31501722"},{201811144,"������","73384391"},
	{201811155,"���߱�","28437551"},{201811166,"������","78265390"},{201811177,"������","77195632"},{201811188,"������","99817456"},
	{201811199,"�̼���","53741121"},{201811100,"ȫ�浿","77839216"},
};

int main (void){
	size_t size, count;
	Person sperson;
	FILE *fp=NULL;
	fp=fopen("student_master.bin","wb");
	if(fp==NULL){
		fprintf(stderr,"������ ������ �� �� �����ϴ�.");
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
			printf("�й��� %d �̸��� %s ��ȭ��ȣ�� %s�Դϴ�.\n",sperson.number,sperson.name,sperson.phone);
	}
		fclose(fp);
		return 0;
	
}
