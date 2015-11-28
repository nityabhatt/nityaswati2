#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
 long long int to_dec(char pc[10])
{
    const int base = 16;
    int ln = 0;
    int i;
    long int num = 0;
    ln = strlen(pc);
    for(i = 0; i < ln; i++)
    {
        if(pc[i] >= 48 && pc[i] <= 57)
            num += (((int)(pc[i])) - 48) * pow(base, ln - i -1);
        else if(pc[i] >= 65 && pc[i] <= 70)
            num += (((int)(pc[i])) - 55) * pow(base, ln - i -1);

    }
    return num;
}

int t_record()
{
    FILE *f1, *f2, *f3;
    char Ad[10];
    char lb[20], mn[20];
    char opnd[20],obcd[10];
    char pc[10];
    char  size[10], rd[90];
    long int num1, num2;
    int lim, flag = 0, size2;
    f1 = fopen("file2.txt","r");
    fscanf(f1,"%s%s%s%s",opnd,lb,mn,Ad);
    f2 = fopen("len.txt","r");
    fscanf(f2,"%s",size);
    fclose(f2);
    f3 = fopen("t_record.txt","w");
    printf("TEXT RECORD: \n");
    if(strcmp(mn,"START")==0)
    {
        printf("H^%s^00%s^%s\n",lb,Ad,size);
        fprintf(f3,"H^%s^00%s^%s\n",lb,Ad,size);
        fscanf(f1,"%s%s%s%s%s",Ad,lb,mn,opnd,obcd);
        while(strcmp(mn,"END") !=0)
        {
            if(flag == 0)
            {
                printf("T^00%s",Ad);
                fprintf(f3,"T^00%s",Ad);
                flag = 1;
            }
            rd[0] = '\0';
            for(lim = 30, size2 = 0; (lim > 0) && (strcmp(mn,"END")) ; )
            {
                if(strcmp(mn,"BYTE") && strcmp(mn,"RESW") && strcmp(mn,"RESB") && strcmp(mn,"END"))
                {
                    lim = lim - 3;
                    if(lim >= 0)
                    {
                        size2 = lim;
                        strcat(rd,"^");
                        strcat(rd,obcd);
                        fscanf(f1,"%s%s%s%s%s",Ad,lb,mn,opnd,obcd);
                    }
                    else
                        break;
                }
                else if((strcmp(mn,"RESW")==0|| strcmp(mn,"RESB")==0) && strcmp(mn,"END"))
                {
                    fscanf(f1,"%s%s%s%s%s",Ad,lb,mn,opnd,obcd);
                    break;
                }
                else if(strcmp(mn,"END") && strcmp(mn,"BYTE")==0)
                {
                    if(opnd[0] == 'X')
                    {
                        lim = lim - 1;
                        if(lim >= 0)
                        {
                            size2 = lim;
                            strcat(rd,"^");
                            strcat(rd,obcd);
                            fscanf(f1,"%s%s%s%s%s",Ad,lb,mn,opnd,obcd);
                        }
                        else
                            break;
                    }
                    else if(opnd[0] == 'C')
                    {
                        lim = lim - (strlen(opnd) - 3);
                        if(lim >= 0)
                        {
                            size2 = lim;
                            strcat(rd,"^");
                            strcat(rd,obcd);
                            fscanf(f1,"%s%s%s%s%s",Ad,lb,mn,opnd,obcd);
                        }
                        else
                            break;
                    }
                }
            }
            if(lim < 30)
            {
                size2 = 30 - size2;
                if(size2 <= 9)
                {
                    printf("^0%d%s\n",size2,rd);
                    fprintf(f3,"^0%d%s\n",size2,rd);
                }
                else
                {
                    sprintf(size,"%X",size2);
                    strupr(size);
                    printf("^%s%s\n",size,rd);
                    fprintf(f3,"^%s%s\n",size,rd);
                }
                flag = 0;
            }
        }
    }
    fclose(f1);
    fclose(f3);
    return 0;
}


int pass2()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    char Ad[10], Add[10];
    char op[10], st[10];
    char  lb[50], mn[50], opnd[50], sym[50], op2[10];
    char ln[10], temp[50];
    int op1[10], i, j = 0, ln2;
    long int ln3;
    f1 = fopen("file1.txt","r");
    f2 = fopen("len.txt","r");
    f3 = fopen("optab.txt","r");
    f4 = fopen("symtab.txt","r");
    f5 = fopen("file2.txt","w");
   fscanf(f1,"%s%s%s%s",Ad,lb,mn,opnd);
    printf("%s\t%s\t%s\t%s\n",Ad,lb,mn,opnd);
    fprintf(f5,"%s\t%s\t%s\t%s\n",Ad,lb,mn,opnd);
    if(strcmp(mn,"START")==0)
    {
        strcpy(st,opnd);
        fscanf(f2,"%s",&ln);
    }
    fscanf(f1,"%s%s%s%s",Ad,lb,mn,opnd);
    while(strcmp(mn,"END"))
    {
        fscanf(f3,"%s %s",op2,op);
        if(strcmp(opnd,"-") && strcmp(mn,"BYTE") && strcmp(mn,"WORD") && strcmp(mn,"RSUB") && strcmp(mn,"RESW") && strcmp(mn,"RESB"))
        while(!feof(f3))
        {
            if(strcmp(mn,op2)==0)
            {
                fscanf(f4,"%s %s",Add,sym);
                while(!feof(f4))
                {
                    if(strcmp(opnd,sym)==0)
                    {
                        printf("%s\t%s\t%s\t%s\t\t%s%s\n",Ad,lb,mn,opnd,op,Add);
                        fprintf(f5,"%s\t%s\t%s\t%s\t\t%s%s\n",Ad,lb,mn,opnd,op,Add);
                        break;
                    }
                    else
                    {
                        ln3 = strlen(opnd);
                        if(opnd[ln3-1] == 'X')
                        {
                            strcpy(temp,opnd);
                            temp[ln3-2] = '\0';
                            if(strcmp(temp,sym)==0)
                            {
                                ln3 = to_dec(Add);
                                ln3 = ln3 + 32768;
                                itoa(ln3,Add,16);
                                strupr(Add);
                                printf("%s\t%s\t%s\t%s\t%s%s\n",Ad,lb,mn,opnd,op,Add);
                                fprintf(f5,"%s\t%s\t%s\t%s\t%s%s\n",Ad,lb,mn,opnd,op,Add);
                                break;
                            }
                        }
                    }
                    fscanf(f4,"%s %s",Add,sym);
                }
                break;
            }
            else
                fscanf(f3,"%s%s",op2,op);
        }
        if(strcmp(mn,"BYTE")==0 || strcmp(mn,"WORD")==0 || strcmp(mn,"RSUB")==0)
        {
            if(strcmp(mn,"WORD")==0)
            {
                printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                itoa(atoi(opnd),opnd,16);
                strupr(opnd);
                ln2 = strlen(opnd);
                for(i = 0; i < (6 - ln2); i++)
                {
                    printf("0");
                    fprintf(f5,"0");
                }
                printf("%s\n",opnd);
                fprintf(f5,"%s\n",opnd);
            }
            else if(!strcmp(mn,"RSUB"))
            {
                printf("%s\t%s\t%s\t%s\t\t4C0000\n",Ad,lb,mn,opnd);
                fprintf(f5,"%s\t%s\t%s\t%s\t\t4C0000\n",Ad,lb,mn,opnd);
            }
            else
            {
                ln2 = strlen(opnd);
                if(opnd[0] == 'X')
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                    fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                    for(i = 2; i < (ln2 - 1); i++)
                    {
                        printf("%c",opnd[i]);
                        fprintf(f5,"%c",opnd[i]);
                    }
                }
                else if((opnd[0] == 'C'))
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                    fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opnd);
                    ln2 = strlen(opnd);
                    for(i = 2; i < (ln2 - 1); i++)
                    {
                        printf("%X",opnd[i]);
                        fprintf(f5,"%X",opnd[i]);
                    }
                }
                printf("\n");
                fprintf(f5,"\n");
            }
        }
        if((strcmp(mn,"RESW")==0) || (strcmp(mn,"RESB")==0))
        {
            printf("%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mn,opnd);
            fprintf(f5,"%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mn,opnd);
        }
        fscanf(f1,"%s%s%s%s",Ad,lb,mn,opnd);
        fclose(f3);
        fclose(f4);
        f3 = fopen("optab.txt","r");
        f4 = fopen("symtab.txt","r");
    }
    if(strcmp(mn,"END")==0)
    {
        printf("%s\t-\tEND\t-\n",Ad);
        fprintf(f5,"%s\t-\tEND\t-\n",Ad);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    return 0;
}


int pass1()
{
    FILE *f1, *f2, *f3, *f4;
    char nam[30], opc[20];
    char lb[50], otp[20], opnd[50];
    char Ad[10], pc[10], o[10];
    int flag, ln, ln2;
    long long int num;
    printf("Please Enter the file name: ");
    gets(nam);
    f1 = fopen(nam,"r");
    fscanf(f1,"%s %s %s",lb,opc,Ad);
    if(strcmp(opc,"START")==0)
    {
        strcpy(pc,Ad);
        f2 = fopen("file1.txt","w");
        fprintf(f2,"-\t%s\t%s\t%s\n",lb,opc,pc);
        printf("\n\n\t%s\t%s\t%s\n",lb,opc,pc);
        fscanf(f1,"%s %s %s",lb,opc,opnd);
    }
    else
    {
        pc[0] = '0';
        pc[1] = '\0';
    }
    f3 = fopen("symtab.txt","w");
    while(!feof(f1))
    {
        fprintf(f2,"%s\t%s\t%s\t%s\n",pc,lb,opc,opnd);
        printf("%s\t%s\t%s\t%s\n",pc,lb,opc,opnd);
        if(strcmp(lb,"-"))
        {
            fprintf(f3,"%s\t%s\n",pc,lb);
        }
        f4 = fopen("optab.txt","r");
        fscanf(f4,"%s %S",otp,o);
        while(!feof(f4))
        {
            if(strcmp(opc,otp)==0)
            {
                num = to_dec(pc);
                num = num + 3;
                itoa(num,pc,16);
                strupr(pc);

                break;
            }
            fscanf(f4,"%s %S",otp,o);
        }
        fclose(f4);
        if(strcmp(opc,"WORD")==0)
        {
            num = to_dec(pc);
            num = num + 3;
            itoa(num,pc,16);
                strupr(pc);


        }
        else if(strcmp(opc,"RESW")==0)
        {
            num = to_dec(pc);
            num = num + (3 * atoi(opnd));
             itoa(num,pc,16);
                strupr(pc);

        }
        else if(strcmp(opc,"BYTE")==0)
        {
            if(opnd[0] == 'X')
            {
                num = to_dec(pc);
                num = num + 1;
                 itoa(num,pc,16);
                strupr(pc);

            }
            else
            {
                num = to_dec(pc);
                num = num + (strlen(opnd) - 3);
                  itoa(num,pc,16);
                strupr(pc);

            }
        }
        else if(strcmp(opc,"RESB")==0)
        {
            num = to_dec(pc);
            num = num + atoi(opnd);
             itoa(num,pc,16);
                strupr(pc);

        }
        fscanf(f1,"%s %s %s",lb,opc,opnd);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    if(strcmp(opc,"END")==0)
    {
        num = to_dec(pc);
        itoa((num - to_dec(Ad)),pc,16);
        strupr(pc);
        printf("\nProgram size= %s\n",pc);
        f1 = fopen("len.txt","w");
        fprintf(f1,"%s",pc);
        fclose(f1);
    }
    return 0;
}

int main()
{
    pass1();                  //addressing
    printf("\n\n");
    pass2();                  //obj code
    printf("\n\n");
    t_record();                  //record
    return 0;
}
