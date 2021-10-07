#include<stdio.h>
#include<string.h>
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

int main(void){
	FILE *old_master_file, *trans_file, *new_master_file;
	Person mperson, mperson1;
	TPerson tmperson;
	
	old_master_file = fopen("student_master.bin", "rb");
	trans_file = fopen("trans.bin", "rb");
	new_master_file = fopen("new_student_master.bin", "wb");
	
	if(old_master_file == NULL || trans_file == NULL ||
		new_master_file == NULL){
		
		return ERROR;
	}
		
	fread(&tmperson, sizeof(TPerson), 1, trans_file);
	fread(&mperson, sizeof(Person), 1, old_master_file);
	
	while(!(feof(old_master_file)) && !(feof(trans_file))){
		if(mperson.number < tmperson.person.number){
			fwrite(&mperson, sizeof(Person), 1, new_master_file);
			fread(&mperson, sizeof(Person), 1, old_master_file);			
		}
		else if(mperson.number == tmperson.person.number){
			switch(tmperson.code){
				case 'I':
					printf("error : 중복된 레코드키 %d 삽입\n",tmperson.person.number);
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					break;
				case 'C':
					mperson1.number = tmperson.person.number;
					strcpy(mperson1.name,tmperson.person.name);
					strcpy(mperson1.phone,tmperson.person.phone);
					fwrite(&mperson1, sizeof(Person), 1, new_master_file);
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					fread(&mperson, sizeof(Person), 1, old_master_file);
					break;
				case 'D':
					fread(&mperson, sizeof(Person), 1, old_master_file);
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					break;
				default:
					printf("error : 잘못된 업데이트 코드\n");
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
			}
		}
		else if(mperson.number > tmperson.person.number){
			switch(tmperson.code){			
				case 'I':
					mperson1.number = tmperson.person.number;
					strcpy(mperson1.name,tmperson.person.name);
					strcpy(mperson1.phone,tmperson.person.phone);
					fwrite(&mperson1, sizeof(Person), 1, new_master_file);
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					break; 
				case 'C':
					printf("error : 트랜스 키에 일치하는 마스터 레코드 없음\n");
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					break;
				case 'D':
					printf("error : 트랜스 키에 일치하는 마스터 레코드 없음\n");
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
					break;
				default:
					printf("error : 잘못된 업데이트 코드\n");
					fread(&tmperson, sizeof(TPerson), 1, trans_file);
				}
		}
		
	}
	while(!(feof(old_master_file)) && (feof(trans_file))){
		fwrite(&mperson, sizeof(Person), 1, new_master_file);
		fread(&mperson, sizeof(Person), 1, old_master_file);
	}
	
	while((feof(old_master_file)) && !(feof(trans_file))){
		switch(tmperson.code){			
			case 'I':
				mperson1.number = tmperson.person.number;
				strcpy(mperson1.name,tmperson.person.name);
				strcpy(mperson1.phone,tmperson.person.phone);
				fwrite(&mperson1, sizeof(Person), 1, new_master_file);
				fread(&tmperson, sizeof(TPerson), 1, trans_file);
				break; 
			case 'C':
				printf("error : 트랜스 키에 일치하는 마스터 레코드 없음\n");
				fread(&tmperson, sizeof(TPerson), 1, trans_file);
				break;
			case 'D':
				printf("error : 트랜스 키에 일치하는 마스터 레코드 없음\n");
				fread(&tmperson, sizeof(TPerson), 1, trans_file);
				break;
			default:
				printf("error : 잘못된 업데이트 코드\n");
				fread(&tmperson, sizeof(TPerson), 1, trans_file);
				}
	}
	fclose(old_master_file);
	fclose(trans_file);
	fclose(new_master_file);
	
	new_master_file = fopen("new_student_master.bin", "rb");
	
	while(1){
		fread(&mperson, sizeof(Person), 1, new_master_file);
		if(feof(new_master_file)){
			break;
		}
		printf("학번은 %d 이름은 %s 전화번호는 %s입니다.\n", mperson.number, mperson.name, mperson.phone);	
	}
	
	fclose(new_master_file);
	return 0;
}


