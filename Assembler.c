#include <stdio.h>
#include <string.h>
int flg;
void converter(float a);
void bin_convf(int a);
void bin_conv(int a);
void operand_assm(char a[], int i,FILE *f);
void operand_check(char a[], int i);
void type_check(char a[], int i);
void assemble_M(char a[], FILE *f);
void label_assm(int a, FILE *f);
int flg1[10],ic=0;
char R[8];
char F[8];
char A[8]; //My entire RAM :P
char B[8];
char C[8];
char D[8];
char E[8];
char F[8];
char G[8];
char H[8];
char F1[8];
char F2[8];
char F3[8];
char F4[8];
char F5[8];
char F6[8];
char F7[8];
char F8[8];
char flag[8];
long int stk[8], prog_ctr;  
int main(){
	printf("Should you choose to have a label, make it a single variable.\n");
	printf("Also, start the code, after label, from next line\n");
	int flag,j=1,m=0,cnt,cnt1=0;
	FILE *isa, *framework, *output, *input;
    char opc[12],temp[12],oc[3],ipt[3],tmp[3],ip[3],temp1[12];
    isa = fopen("ISA2.txt", "r");
    input = fopen("input.txt", "r");
    framework = fopen("fwork.txt", "r");
    output = fopen("output.txt", "w");
    if (!isa){
	return 1;
	}
    if (!output){
    return 1;	
    }
    if (!input){
    return 1;	
    }
	if (!framework){
	return 1;	
	} 
    do{
    	fscanf(input, "%s", temp);
    	strcpy(temp1,temp);
    	strncpy(ipt,temp,3);
    	rewind(isa);
    	cnt=0;
    	do{
    		j++;
    		cnt++;
			ipt[3]='\0';
    		fscanf(isa, "%s", opc);
    		strncpy(oc,opc,3);
    		oc[3]='\0';
    		int g = strncmp(ipt,oc,3);	
    		//7728059747
    		if(g==0){
    			//fscanf(isa, "%s", opc);
    			assemble_M(opc,output);
    			operand_check(temp,cnt);
    			type_check(temp1,cnt);
    			operand_assm(temp,cnt,output);
    			flag=0;
    			break;
    		}
    		else if(ipt[1]==':'){
    			fprintf(output, "%s\n", " ");
    			flg1[ic] = (int)ipt[0];
    			ic++;
    			flag=0;
    			if(ic==11){
    				printf("Do not use more different labels now. Overwrite possible.\n");
    			}
    			break;
    		}
    		flag =1;
    	}while(!feof(isa));
    	if(flag==1){
    		printf("Syntax error. Line : %d No such command exists.\n",cnt1);
    		flg = 1;
    	}
    	cnt1++;
    }while(!feof(input));
    if(flg==1){
    	int dd;
    	printf("It seems there were errors. Enter 1 for help 0 for none.\n");
    	scanf("%d",&dd);
    	if(dd==1){
    		FILE *g;
    		g= fopen("help.txt","r");
    		char d[0]; int f1=0;
    		do{
    		fscanf(g,"%s",d);
    		printf("%s",d);
    		int l1 = strlen(d);
    		if(d[l1]=='\0'){
    			printf(" ");
    		}
    		}while(!feof(g));
    	}
    }
    fclose(isa);
    fclose(input);
    fclose(output);
    printf("OpCodes converted.");
    getch();
}
void assemble_M(char a[], FILE *f){
	char b, o[8];
	int i=4,j=0;
	while(i<12){
		o[j] =a[i];
		j++;
		i++;
	}
	o[j+1]='\0';
	fprintf(f, "%s\n", o);
}
void operand_check(char a[], int i){
	int h=0;
	if(i>7 && i<33 || i==3 || i==4 || i==41 || i==42){
		if(a[3]=='_'){
			h=1;
		}
		if(h==1){
			printf("Number of operands (1) perfect.\n");
			return;
		}
		else if(h!=1){
			printf("Number of operands exceed (or preceed)(1) limit.-%d\n",h);
			return;
		}		
	}
	else if(i>32 && i<41 || i>0 && i<8 && i!=3 && i!=4){
		h=0;
		if(a[3]=='_'){
			h=1;
			if(i==1||i==5||i==6){
				int g=4;
				while(a[g]!='\0'){
					if(a[g]=='_' && g>4){
						h++;
					}
					g++;
				}
			}
			else if(i==2||i==7|| (i>35 && i<41)){
				int g=4;
				while(a[g]!='\0'){
					if(a[g]=='_' && g>4){
						h++;
					}
					g++;
				}
			}
			else if(i==33||i==34||i==35){
				int g=4;
				while(a[g]!='\0' && g>4){
					if(a[g]=='_'){
						h++;
					}
					g++;
				}
			}
		}
		if(h==2){
			printf("Number of operands(2) perfect.\n");
			return;
		}
		else if(h!=2){
			printf("Number of operands exceed (or preceed)(2) limit.-%d\n",h);
			return;
		}	
	}
	else if(i>52 && i<66 || i==82){
		h=0;
		while(a[h]!='\0'){
			if(a[h]=='_'){
				h++;	
			}
		}
		if(h==0){
			printf("Number of operands(0) perfect.\n");
			return;
		}
		else if(h!=0){
			printf("Number of operands exceed (or preceed)(0) limit.-%d\n",h);
			return;
		}	
	}
	else if(i>42&& i<53 || i>65 && i< 82){
		h=0;
		if(a[3]=='_'){
			h=1;
		}
		if(h==1){
			printf("Number of operands(1-) perfect.\n");
			return;
		}
		else if(h!=1){
			printf("Number of operands exceed (or preceed)(1-) limit.\n",h);
			return;
		}	
	}
}
void type_check(char a[], int i){
	int t=0,k=0;
	int err=0;
	char b[12],c[4];
	if(i>7 && i<33){
		int t=0;
		int j=4;
		if(a[3]!='_' || a[4]=='\0'){
			printf("Wrong operands error.\n");
		}
		else{
			while(a[j]!='_' && t<4){
			c[t]=a[j] ;
			t++; j++;
			}
			c[t]='\0';
			k=atoi(c);
			if(k>2047){
				printf("Error: Out of range of addresses.\n");
				err=1;return;
			}
			else{
				printf("Operand perfect\n");
				return;
			}
		}
	}
	else if(i>65 && i<82){
		t=0;
		if(a[5]!='\0'){
			printf("Error: Not a lable form.\n");
			err=1;
			return;
		}
		else{
			int fg = (int)a[4];
			int df =0;
			while(df<10){
			if(fg!=flg1[df]){
				printf("Error: Not valid 'Label' name, or 'Label' undefined.\n");
				err=1;
				return;
			}
			else{
				printf("Operand perfect\n");
				return;
			}	
			df++;
			}
		}
	}
	else if(i>52 && i<66 || i==82 || i==83){
		t=0;
		if(a[3]!='\0'){
			printf("Error: No arguement required.\n");
			err=1;
			return;
		}
		else{
			printf("Operand perfect\n");
			return;
		}
	}
	else if(i>45 && i<53 || i==3 || i==4){
		t=0;
		if(a[5]!='\0'){
			printf("Syntax error in operands.\n");
			err=1;
			printf("-%d-\n",i);
			return;
		}
		else{
		int fg = (int)a[4];
		if(fg <65 || fg > 80){
			printf("Error: Not valid register name.\n");
			err=1;
		}
		else{
			printf("Operand perfect\n");
			return;
		}
		}
	}
	else if(i>42 && i<46){
		t=0;
		int h=0,j=4;
		if(a[3]!='_' || a[4]=='\0'){
			printf("Error in synatx.\n");
			return;
		}
		while(a[j]!='_' && h<3){
			c[h]=a[j] ;
			h++; j++;
			}
		c[h]='\0';
		k= atoi(c);
		if(k>511){
			printf("Error: Data limit exceeds.\n");
			err=1;
			return;
		}
		else{
			printf("Operand perfect\n");
			return;
		}
	}
	else if(i==41 || i==42){
		int h=0,j=4;
		if(a[3]!='_' || a[4]=='\0'){
			printf("Error in synatx.\n");
			return;
		}
		while(a[j]!='_' && h<4){
			c[h]=a[j] ;
			h++; j++;
			}
		c[h]='\0';
		k= atoi(c);
		if(k>1023){
			printf("Error: Data limit exceeds.\n");
			err=1;
			return;
		}
		else{
			printf("Operand perfect\n");
			return;
		}	
	}
	else if(i>35 && i<41 || i==2 || i==7){
		t=0;
		if(a[7]!='\0'){
			printf("Syntax error in operands.\n");
			err=1;
			//printf("-%d-\n",i);
			return;
		}
		int fg = (int)a[4];
		int gf = (int)a[6];
		if(fg <65 || fg > 80 || gf <65|| gf >80){
			printf("Error: Not valid register name.\n");
			err=1;
		}
		else{
			printf("Operand perfect\n");
			return;
		}
	}
	else if(i==33 || i==34 || i==35){
		t=0;
		if(a[3]!='_' || a[4]=='\0'){
			printf("Error in synatx.\n");
			return;
		}
		int g=4,h=1;
		while(a[g]!='\0'){
			if(a[g]=='_'){
				h++;
				break;
			}
			g++;
		}
		int fg = (int)a[g+1];
		if(fg <65 || fg > 80){
			printf("Error: Not valid register name.\n");
			err=1;
		}
		else{
			int h=0,j=8;
			while(a[j]!='_' && h<2){
			c[h]=a[j] ;
			h++; j++;
			}
			c[h]='\0';
			k= atoi(c);
			if(k>63){
				printf("Error: Data limit exceeds.\n");
				err=1;
			return;
			}
			else{
			printf("Operand perfect.\n");
			return;
			}		
		}
	}
	else if(i==1 || i==5 || i ==6){
		if(a[3]!='_' || a[4]=='\0'){
			printf("Error in synatx.\n");
			return;
		}
		int g=4,h=1;
		while(a[g]!='\0'){
			if(a[g]=='_'){
				h++;
				break;
			}
			g++;
		}
		int fg = (int)a[g+1];
		if(fg <65 || fg > 80){
			printf("Error: Not valid register name.\n");
			err=1;
		}
		else{
			int h=0,j=4;
			while(a[j]!='_' && h<3){
			c[h]=a[j] ;
			h++; j++;
			}
			c[h]='\0';
			k= atoi(c);
			if(k>127){
				printf("Error: Data limit exceeds.\n");
				err=1;
			return;
			}
			else{
			printf("Operand perfect.\n");
			return;
			}	
		}
	}
	if(err==1){
		int dd;
    	printf("It seems there were errors. Enter 1 for help 0 for none.\n");
    	scanf("%d",&dd);
    	if(dd==1){
    		FILE *g;
    		g= fopen("help.txt","r");
    		char d[0]; int f1=0;
    		do{
    		fscanf(g,"%s",d);
    		printf("%s",d);
    		int l1 = strlen(d);
    		if(d[l1]=='\0'){
    			printf(" ");
    		}
    		}while(!feof(g));
    	}	
	}
}
void operand_assm(char a[], int i,FILE *f){
	//printf("-*%d*-\n",i);
	FILE *op1;
	op1 = fopen("fwork.txt", "r");
	int t=0,k=0;
	char b[8],c[4];
	if(i>6 && i<33){
		int j=4;
		while(a[j]!='_' && t<4){
			 c[t]=a[j];
			t++; j++;
		}
		c[t]='\0';
		k=atoi(c);
		if(k<2047){
			converter(k);
			fprintf(f, "%s\n", R);
			printf("Operand Added.\n");
			return;
		}
		else{
			printf("Large operand.\n");
		}
	}
	else if(i>65 && i<82){
		if(a[5]=='\0'){
			int hj = (int)a[4];
			label_assm(hj,f);
			printf("Operand Added.\n");
			return;
		}
		else{
			printf("Wrong operand.\n");
		}
	}
	else if(i>52 && i<66){
		if(a[3]!='\0'){
			return;
		}
	}
	else if(i>45 && i<53 || i==3 || i==4){
		int fg = (int)a[4];
		if(fg >64 || fg < 81){
			converter(fg-64);
			fprintf(f,"%s\n",R);
		}
		else{
			printf("Wrong operand.\n");
		}
	}
	else if(i>42 && i<46){
		int h=0,j=4;
		while(a[j]!='_' && h<3){
			c[h]=a[j];
			h++; j++;
		}
		c[h]='\0';
		k= atoi(c);
		if(k<=511){
			converter(k);
			fprintf(f,"%s\n",R);
			printf("Operand Added.\n");
			return;
		}
		else{
			printf("Large operand.\n");
		}
	}
	else if(i==41 || i==42){
		int h=0,j=4;
		while(a[j]!='_' && h<4){
			c[h]=a[j] ;
			h++; j++;
		}
		c[h]='\0';
		k= atoi(c);
		if(k<=1023){
			converter(k);
			fprintf(f,"%s\n",R);
			printf("Operand Added.\n");
			return;
		}
		else{
			printf("Large operand.\n");
		}	
	}
	else if(i>35 && i<41){
		int fg = (int)a[4];
		int gf = (int)a[6];
		if(fg >64 && fg < 81 && gf>64 && gf<81 ){
			//printf("--\n");
			converter(fg-64);
			fprintf(f,"-%s-%d\n",R,i);
			//printf("-%s-\n",R);
			converter(gf);
			fprintf(f,"%s\n",R);
		}
		else{
			printf("Wrong operands.\n");
			return;
		}
	}
	else if(i==2 || i==7){
		printf("--%d\n",i);
		int fg = (int)a[4];
		int gf = (int)a[6];
		if(fg >64 && fg < 81 && gf >64 && gf<81 ){
			printf("--\n");
			converter(fg-64);
			fprintf(f,"-%s\n",R);
			printf("-%s-\n",R);
			converter(gf-64);
			fprintf(f,"%s\n",R);
		}
		else{
			printf("Wrong operands.\n");
			return;
		}
	}
	else if(i==33 || i==34 || i==35){
		int fg = (int)a[4];
		if(fg >64 || fg < 81 ){
			converter(fg-64);
			fprintf(f,"%s\n",R);
			printf("%s\n",R);
			int h=0,j=8;
			while(a[j]!='_' && h<2){
			 c[h]=a[j];
			h++; j++;
			}
			c[h]='\0';
			k= atoi(c);
			if(k<=63){
			converter(k);
			fprintf(f,"%s\n",R);
			printf("Operand Added.\n");
			return;
			}
			else{
				printf("Large operand.\n");
			}		
		}
	}
	else if(i==1 || i==5|| i==6){
		int fg = (int)a[8];
		if(fg >64 && fg < 81 ){
			converter(fg-64);
			fprintf(f,"%s\n",R);
			int h=0,j=4;
			while(a[j]!='_' && h<3){
			 c[h]=a[j] ;
			h++; j++;
			}
			c[h]='\0';
			k= atoi(c);
			if(k<=127){
			converter(k);
			fprintf(f,"%s\n",R);
			//printf("-%s-\n",R);
			printf("Operand Added.\n");
			return;
			}
			else{
				printf("Large operand.\n");
				return;
			}
		}
	}
}
void converter (float a){
	int b = (int)a;
	if(b==a){
		bin_conv((int)a);
	}
	else{
		bin_conv((int)a);
		a = a - b;
		a=a*100;
		bin_convf((int)a);
	}
}
void bin_conv(int a){
	int i=7;
	while(i>=0){
		if(a%2 ==0){
			R[i] = '0';
		}
		else{
			R[i] = '1';
		}
		a=a/2;
		i--;
	}
}
void bin_convf(int a){
	int i=8;
	while(i>0){
		if(a%2 ==0){
			F[i] = '0';
		}
		else{
			F[i] = '1';
		}
		a=a/2;
		i--;
	}
}
void label_assm(int a, FILE *f){
	int i=0;
	if(a==flg1[i]){
		converter(a);
		fprintf(f,"%s",R);
		return;
	}
	else{
		printf("No such Label.\n");
		return;
	}
}
