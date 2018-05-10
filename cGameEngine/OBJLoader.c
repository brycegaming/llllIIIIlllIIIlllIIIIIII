#include "include/OBJLoader.h"
#include "string.h"
	
unsigned int strLength(char* string){
	for(int i = 0; i < 10000; i++){
		if(string[i] == '\n')
			return i;
	}
	return 0;
}

ModelData OBJLoadData(const char* filename){
	FILE* fileIn = fopen(filename, "rb");
	if(!fileIn){
		printf("Failed to open file\n");
		exit(-1);
	}

	fseek(fileIn, 0, SEEK_END);
	long numBytes = ftell(fileIn);
	fseek(fileIn,0, SEEK_SET);

	char* data = malloc(numBytes+1);
	data[numBytes] = '\n';
	
	if(!fread(data, 1, numBytes, fileIn)){
		printf("Failed to load data\n");
		exit(-1);
	}
	
	//create linked lists
	ModelData filedat;
	memset(&filedat, 0x0, sizeof(ModelData));
	vec3LL* tVertListL = NULL;
	vec2LL* tTexListL = NULL;
	vec3LL* tNormListL = NULL;
	indLL* tIndListL = NULL;
	indLL* tTexIndListL = NULL;
	indLL* tNormIndListL = NULL;

	//get parse data
	unsigned int dataPtr = 0;
	do{
		unsigned int stringLen = strLength(&data[dataPtr]);
		char* cString = malloc(stringLen+1);
		cString[stringLen] = 0x0;
		memcpy(cString, &data[dataPtr], stringLen);

		int subStringPtr = 1;
		switch(*cString){
		case('v'):{
			switch(cString[subStringPtr]){
			case(' '):{
				subStringPtr++;	
				char dta[30];
				char* dtaS = dta;
				int dPtr = 0;
				for(int i = subStringPtr; i < stringLen; i++){
					if(cString[i] == ' '){
						dtaS[dPtr] = 0x0;
						dPtr = 0;
						dtaS += 10;
					}else{
						dtaS[dPtr] = cString[i];
						dPtr++;
					}
				}
				vec3LL* tVertList = malloc(sizeof(vec3LL));
				tVertList->next = NULL;

				tVertList->x = atof(dta);
				tVertList->y = atof(&dta[10]);
				tVertList->z = atof(&dta[20]);
				
				if(!filedat.vertList){
					filedat.vertList = tVertList;
				}else{
					tVertListL->next = tVertList;
				}
				tVertListL = tVertList;
			}
			break;
			case('t'):{
				subStringPtr+=2;
				char dta[20];
				char* dtaS = dta;
				int dPtr = 0;
				for(int i = subStringPtr; i < stringLen; i++){
					if(cString[i] == ' '){
						dtaS[dPtr] = 0x0;
						dPtr = 0;
						dtaS += 10;
					}else{
						dtaS[dPtr] = cString[i];
						dPtr++;
					}
				}
				vec2LL* tTexList = malloc(sizeof(vec2LL));
				tTexList->next = NULL;

				tTexList->x = atof(dta);
				tTexList->y = atof(&dta[10]);

				if(!filedat.texList){
					filedat.texList = tTexList;
				}else{
					tTexListL->next = tTexList;
				}
				tTexListL = tTexList;
			}
			break;
			case('n'):{
				subStringPtr+=2;	
				char dta[30];
				char* dtaS = dta;
				int dPtr = 0;
				for(int i = subStringPtr; i < stringLen; i++){
					if(cString[i] == ' '){
						dtaS[dPtr] = 0x0;
						dPtr = 0;
						dtaS += 10;
					}else{
						dtaS[dPtr] = cString[i];
						dPtr++;
					}
				}
				vec3LL* tNormList = malloc(sizeof(vec3LL));
				tNormList->next = NULL;

				tNormList->x = atof(dta);
				tNormList->y = atof(&dta[10]);
				tNormList->z = atof(&dta[20]);
				
				if(!filedat.normList){
					filedat.normList = tNormList;
				}else{
					tNormListL->next = tNormList;
				}
				tNormListL = tNormList;
			}
			break;
			}
		}
		break;
		case('f'):{
			subStringPtr++;
			char dataType = 1;
			char dBool = 0;
			char dBool1 = 0;
			char dBool2 = 1; //controls data type adding
			for(int i = subStringPtr; i < stringLen; i++){
				if(cString[i] == ' '){
					cString[i] = 0x0;
					dBool2 = 0;
				}else if(cString[i] == '/'){
					if(dBool2){
						if(!dBool&&dBool1){
							dataType += 2;
						}else{
							dataType += 1;
						}
					}
					cString[i] = 0x0;
					dBool = 0;
					dBool1 = 1;
				}else{
					dBool = 1;
				}
			}
			if(dataType == 4){
				printf("Datatype 4 detected: expected texCoords, current face data x//x\n");
				exit(0);
			}

			//Store data
			unsigned int orderedIndData[dataType * 3];
			int daPointer = 0;
			char boolOID = 0;
			for(int x = subStringPtr; x < stringLen; x++){
				if(cString[x] == 0x0){
					boolOID = 0;
					daPointer++;
				}else{
					if(!boolOID){
						orderedIndData[daPointer] = atoi(&cString[x]);
					}
					boolOID = 1;
				}
			}
			indLL* tIndDat = malloc(sizeof(indLL)*dataType * 3);
			for(int i = 0; i < dataType; i++){
				indLL* indTPTR = &tIndDat[3*i];
				indTPTR[0].next = &indTPTR[1];
				indTPTR[1].next = &indTPTR[2];
				indTPTR[2].next = NULL;

				indTPTR[0].ind = orderedIndData[i];
				indTPTR[1].ind = orderedIndData[i+dataType];
				indTPTR[2].ind = orderedIndData[i+dataType*2];
					
				if(i == 0){
					if(!filedat.indList){
						filedat.indList = &indTPTR[0];
					}else{
						tIndListL->next = &indTPTR[0];
					}
					tIndListL = &indTPTR[2];
				}
				if(i == 1){
					if(!filedat.texIndList){
						filedat.texIndList = &indTPTR[0];
					}else{
						tTexIndListL->next = &indTPTR[0];
					}
					tTexIndListL = &indTPTR[2];
				}
				if(i == 2){
					if(!filedat.normIndList){
						filedat.normIndList = &indTPTR[0];
					}else{
						tNormIndListL->next = &indTPTR[0];
					}
					tNormIndListL = &indTPTR[2];
				}
			}
		}
		break;
		default:
		break;
		}
		
		free(cString);
		//account for whitespace
		dataPtr += stringLen + 1;
	}while(dataPtr < numBytes);

	free(data);
	fclose(fileIn);
	return filedat;
}

void OBJFreeData(ModelData* fd){ //Frees data in fileData struct 
	vec3LL* head = fd->vertList;
	while(head){
		vec3LL* temp = head; 
		head = head->next; //set head to next element
		free(temp); //free data
	}

	vec3LL* head1 = fd->normList;
	while(head1){
		vec3LL* temp = head1; 
		head1 = head1->next; //set head to next element
		free(temp); //free data
	}

	vec2LL* head2 = fd->texList;
	while(head2){
		vec2LL* temp = head2; 
		head2 = head2->next; //set head to next element
		free(temp); //free data
	}

	indLL* head3 = fd->indList;
	while(head3){
		indLL* temp = head3;
		head3 = temp;
		for(int x = 0; x < 3; x++){
			head3 = head3->next;	
		}
		free(temp);
	}
}
