#include<string.h>
#include<math.h>

int input(){
    fflush(stdin);
	char readstr[512];
    int  i, len, x;
    int input_int = 0, w;
    gets(readstr);

    len = strlen(readstr);
    x = len-1;

    for(i = 0; i < len; i++)
    {
        if(readstr[i] > 47 && readstr[i] < 58){
            w = readstr[i] - 48;
        }
        else if(readstr[i]==114||readstr[i]==82||readstr[i]==117||readstr[i]==85||readstr[i]==109||readstr[i]==77||readstr[i]==115||readstr[i]==83||readstr[i]==101||readstr[i]==69){
               if (len==1){return readstr[0];}                       //asci code for:r-R-u-U-m-M-s-S-e-E//
                else{return -1;}
        }
        else {
            return -1;
        }
        input_int += w*pow(10,x);
        x--;
    }
    if (input_int>12){
        return -1;
    }
	return input_int;
 }

