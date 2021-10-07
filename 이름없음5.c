#include<stdio.h>
#define ERROR -1

typedef struct{
	int number;
	char name[10];
	char phone[10];
} Person;

typedef struct{
	char code;
	Person person;
} TPerson;



void sequentialUpdate();

void getNextTrans();

void getNextMaster();

void noMatch();

FILE *old_master_file, *trans_file, *new_master_file;
Person mperson;
TPerson tmperson;

int main(void){
	
	
	old_master_file = fopen("student_master.bin", "rb");
	trans_file = fopen("trans.bin", "rb");
	new_master_file = fopen("new_student_master.bin", "wb");
	
	if(old_master_file == NULL || trans_file == NULL ||
		new_master_file == NULL){
		
		return ERROR;
	}
	
	sequentialUpdate();
		
	fclose(old_master_file);
	fclose(trans_file);
	fclose(new_master_file);
	
	new_master_file = fopen("new_student_master.bin", "rb");
	
	while(1){
		fread(&mperson, sizeof(Person), 1, new_master_file);
		if(feof(new_master_file)){
			break;
		}
		printf("�й��� %d �̸��� %s ��ȭ��ȣ�� %s�Դϴ�.\n", mperson.number, mperson.name, mperson.phone);	
	}
	
	fclose(new_master_file);
	return 0;
}

void sequentialUpdate(){
	getNextTrans();
	getNextMaster();
	
	
	while(!(mperson.name == EOF) && !(tmperson.person.name == EOF)){
		if(mperson.number < tmperson.person.number){
			fwrite(&mperson, sizeof(Person), 1, new_master_file);
			getNextMaster();			
		}
		else if(mperson.number == tmperson.person.number){
			switch(tmperson.code){
				case 'I':
					printf("error : �ߺ��� ���ڵ�Ű %d ����\n",tmperson.person.number);
					getNextTrans();
					break;
				case 'C':					
					fwrite(&tmperson, sizeof(TPerson), 1, new_master_file);
					getNextTrans();
					getNextMaster();
					break;
				case 'D':
					getNextMaster();
					getNextTrans();
					break;
				default:
					printf("error : �߸��� ������Ʈ �ڵ�\n");
					getNextTrans();
			}
		}
		else if(mperson.number > tmperson.person.number){
			noMatch();
		}
		
	}
	while(!(mperson.name == EOF)){
		fwrite(&mperson, sizeof(Person), 1, new_master_file);
		getNextMaster();
	}
}

void getNextTrans(){
	if(feof(trans_file)){
		tmperson.person.name[10] = EOF;
	}
	else{
		fread(&tmperson, sizeof(TPerson), 1, trans_file);
	}
} 

void getNextMaster(){
	if(feof(old_master_file)){
		mperson.name[10] = EOF;
	}
	else{
		fread(&mperson, sizeof(Person), 1, old_master_file);
	}
}

void noMatch(){
	switch(tmperson.code){			
				case 'I':					
					fwrite(&tmperson, sizeof(TPerson), 1, new_master_file);
					getNextTrans();
					break; 
				case 'C':

				case 'D':
					printf("error : Ʈ���� Ű�� ��ġ�ϴ� ������ ���ڵ� ����\n");
					getNextTrans();
					break;
				default:
					printf("error : �߸��� ������Ʈ �ڵ�\n");
					getNextTrans();
				}
}

