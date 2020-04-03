/**
	Command line interface for working with NBT files, version 0.1
**/

#include <stdio.h>
#include <stdlib.h>

//Utility methods for reading data

unsigned short readShort(FILE *fp){
	char byteOne = fgetc(fp);
	char byteTwo = fgetc(fp);

	unsigned short ret = (short) byteOne;
	ret = ret << 8;

	ret += (short) byteTwo;	
	
	return ret;
	
}

int readInt(FILE *fp){

	unsigned int ret = 0;
	
	for(int i = 0; i < 4; i++){
		ret = ret << 8;
		ret += (short) fgetc(fp);
	}	

	return ret;

}

long readLong(FILE *fp){
	unsigned long ret = 0;
	
	for(int i = 0; i < 4; i++){
		ret = ret << 8;
		ret += (short) fgetc(fp);
	}	

	return ret;
}

//Methods for keeping track of data indentsk

int indentLevel = 0;

void printIndent(){
	for(int i = 0; i < indentLevel;i++){
		printf("     ");	
	}
}

//Some function prototyping to allow easier organization

int nextTag(FILE *fp); 
int readPayloadOfTag(int id, FILE *fp);

//All of our tag methods, each one process a payload, then returns

int tag_byte(FILE *fp){
	char in = fgetc(fp);

	printf("%d\n", in);

	return 0;
}

int tag_short(FILE *fp){
	short payload = readShort(fp);

	printf("%d\n", payload);

	return 0;
}

int tag_int(FILE *fp){
	int payload = readInt(fp);

	printf("%d\n", payload);
}

int tag_long(FILE *fp){
	long payload = readInt(fp);

	printf("%ld\n", payload);
}

int tag_float(FILE *fp){
	printf("FLoat being skipped\n");
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
}

int tag_double(FILE *fp){	
	printf("Double being skipped\n");
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
}

int tag_byte_array(FILE *fp){

	printf("Ecountred byte array,killing");
	exit(0);
	return 0;
}

int tag_string(FILE *fp){

	
	short stringLength = readShort(fp);


	char *name = malloc(stringLength);
	char *nameStart = name;

	if(name == NULL){
		printf("Failed memory allocation\n");
		exit(0);
	}

	for(short i = 0; i < stringLength;i++){
		char nextCharacter = fgetc(fp);	
		*name = nextCharacter;
		name += 1;
	}

	printf("%s\n", nameStart);

}

int tag_list(FILE *fp){
	int tagId = (short) fgetc(fp);

	int length = readInt(fp);

	if(length == 0){
		printf("\n");
		return 0;
	}

	for(int i = 0;i < length;i++){
		readPayloadOfTag(tagId, fp);		
	}	
}

int tag_compound(FILE *fp){

	indentLevel += 1;
	int tag = nextTag(fp);
	while(tag != 0){
		printIndent();
		tag = nextTag(fp);
	}
	indentLevel -= 1;
	
	return 0;
}

int tag_int_array(FILE *fp){
	int length = readInt(fp);

	if(length == 0){
		printf("\n");
		return 0;
	}
	
	indentLevel += 1;

	for(int i = 0;i<length;i++){
		int payload = readInt(fp);
		printIndent();
		printf("%d\n", payload);	
	}

	indentLevel -= 1;

	return 0;	
}

int tag_long_array(FILE *fp){
	int length = readInt(fp);
	
	if(length == 0){
		printf("\n");
		return 0;
	}

	indentLevel += 1;

	for(int i = 0;i<length;i++){
		long payload = readLong(fp);
		printIndent();
		printf("%ld\n", payload);	
	}

	indentLevel -= 1;

	return 0;
} 

//This is where we store our parallel array structure for prototyping the functions
#define numberOfTags 13

int (*tagMethods[numberOfTags])(FILE *fp) = {
	NULL,
	&tag_byte,
	&tag_short,
	&tag_int,
	&tag_long,
	&tag_float,
	&tag_double,
	&tag_byte_array,
	&tag_string,
	&tag_list,
	&tag_compound,
	&tag_int_array,
	&tag_long_array
};

//This is our method for handling the naming of tags
char *processName(FILE *fp){
	char firstByte = fgetc(fp);
	char secondByte = fgetc(fp);

	unsigned short stringLength = firstByte;
	stringLength = stringLength << 8;

	stringLength += (short) secondByte;

	char *name = malloc(stringLength);
	char *nameStart = name;

	if(name == NULL){
		printf("Failed memory allocation\n");
		exit(0);
	}

	for(short i = 0; i < stringLength;i++){
		char nextCharacter = fgetc(fp);	
		*name = nextCharacter;
		name += 1;
	}

	return nameStart;
	
}

//Primary method for getting a next tag, can recursively be called by tag handler methods, return is the tag id
int nextTag(FILE *fp){
	short nextTagId = fgetc(fp);

	if(nextTagId == 0){ // If end tag, then we can never have a string or a payload
		return 0;
	}

	
	char* name = processName(fp);

	printf("%s : ", name);

	tagMethods[nextTagId](fp);		

	return nextTagId;
}

//This is a secondary method for processing tags without ids
int readPayloadOfTag(int id, FILE *fp){
	
	tagMethods[id](fp);	

	return 0;		
}

//Methods for user command line inteface

int main(int argc, char* *argv){
	FILE *playerNbt;

	playerNbt = fopen("player.nbt", "r");

	printf("Started\n");
	
	nextTag(playerNbt);	

}
