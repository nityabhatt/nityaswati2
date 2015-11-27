#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

int pass2()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    char Ad[10], Add[10], op[10], st[10], lb[50], mn[50], opd[50], sym[50], op2[10], ln[10], temp[50];
    int op1[10], i, j = 0, ln2;
    long int ln3;
    f1 = fopen("intermediate.txt","r");
    f2 = fopen("len.txt","r");
    f3 = fopen("optab.txt","r");
    f4 = fopen("symtab.txt","r");
    f5 = fopen("intermediate2.txt","w");
   fscanf(f1,"%s%s%s%s",Ad,lb,mn,opd);
    printf("%s\t%s\t%s\t%s\n",Ad,lb,mn,opd);
    fprintf(f5,"%s\t%s\t%s\t%s\n",Ad,lb,mn,opd);
    if(strcmp(mn,"START")==0)
    {
        strcpy(st,opd);
        fscanf(f2,"%s",&ln);
    }
    fscanf(f1,"%s%s%s%s",Ad,lb,mn,opd);
    while(strcmp(mn,"END"))
    {
        fscanf(f3,"%s %s",op2,op);
        if(strcmp(opd,"-") && strcmp(mn,"BYTE") && strcmp(mn,"WORD") && strcmp(mn,"RSUB") && strcmp(mn,"RESW") && strcmp(mn,"RESB"))
        while(!feof(f3))
        {
            if(strcmp(mn,op2)==0)
            {
                fscanf(f4,"%s %s",Add,sym);
                while(!feof(f4))
                {
                    if(strcmp(opd,sym)==0)
                    {
                        printf("%s\t%s\t%s\t%s\t\t%s%s\n",Ad,lb,mn,opd,op,Add);
                        fprintf(f5,"%s\t%s\t%s\t%s\t\t%s%s\n",Ad,lb,mn,opd,op,Add);
                        break;
                    }
                    else
                    {
                        ln3 = strlen(opd);
                        if(opd[ln3-1] == 'X')
                        {
                            strcpy(temp,opd);
                            temp[ln3-2] = '\0';
                            if(strcmp(temp,sym)==0)
                            {
                                ln3 = to_dec(Add);
                                ln3 = ln3 + 32768;
                                itoa(ln3,Add,16);
                                strupr(Add);
                                printf("%s\t%s\t%s\t%s\t%s%s\n",Ad,lb,mn,opd,op,Add);
                                fprintf(f5,"%s\t%s\t%s\t%s\t%s%s\n",Ad,lb,mn,opd,op,Add);
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
                printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                itoa(atoi(opd),opd,16);
                strupr(opd);
                ln2 = strlen(opd);
                for(i = 0; i < (6 - ln2); i++)
                {
                    printf("0");
                    fprintf(f5,"0");
                }
                printf("%s\n",opd);
                fprintf(f5,"%s\n",opd);
            }
            else if(!strcmp(mn,"RSUB"))
            {
                printf("%s\t%s\t%s\t%s\t\t4C0000\n",Ad,lb,mn,opd);
                fprintf(f5,"%s\t%s\t%s\t%s\t\t4C0000\n",Ad,lb,mn,opd);
            }
            else
            {
                ln2 = strlen(opd);
                if(opd[0] == 'X')
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                    fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                    for(i = 2; i < (ln2 - 1); i++)
                    {
                        printf("%c",opd[i]);
                        fprintf(f5,"%c",opd[i]);
                    }
                }
                else if((opd[0] == 'C'))
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                    fprintf(f5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mn,opd);
                    ln2 = strlen(opd);
                    for(i = 2; i < (ln2 - 1); i++)
                    {
                        printf("%X",opd[i]);
                        fprintf(f5,"%X",opd[i]);
                    }
                }
                printf("\n");
                fprintf(f5,"\n");
            }
        }
        if((strcmp(mn,"RESW")==0) || (strcmp(mn,"RESB")==0))
        {
            printf("%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mn,opd);
            fprintf(f5,"%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mn,opd);
        }
        fscanf(f1,"%s%s%s%s",Ad,lb,mn,opd);
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
    char nam[30], opc[20], lb[50], otp[20], opd[50], Ad[10], pc[10], o[10];
    int flag, ln, ln2;
    long long int num;
    printf("Please Enter the file name: ");
    gets(nam);
    f1 = fopen(nam,"r");
    fscanf(f1,"%s %s %s",lb,opc,Ad);
    if(strcmp(opc,"START")==0)
    {
        strcpy(pc,Ad);
        f2 = fopen("intermediate.txt","w");
        fprintf(f2,"-\t%s\t%s\t%s\n",lb,opc,pc);
        printf("\n\n\t%s\t%s\t%s\n",lb,opc,pc);
        fscanf(f1,"%s %s %s",lb,opc,opd);
    }
    else
    {
        pc[0] = '0';
        pc[1] = '\0';
    }
    f3 = fopen("symtab.txt","w");
    while(!feof(f1))
    {
        fprintf(f2,"%s\t%s\t%s\t%s\n",pc,lb,opc,opd);
        printf("%s\t%s\t%s\t%s\n",pc,lb,opc,opd);
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
            num = num + (3 * atoi(opd));
             itoa(num,pc,16);
                strupr(pc);

        }
        else if(strcmp(opc,"BYTE")==0)
        {
            if(opd[0] == 'X')
            {
                num = to_dec(pc);
                num = num + 1;
                 itoa(num,pc,16);
                strupr(pc);

            }
            else
            {
                num = to_dec(pc);
                num = num + (strlen(opd) - 3);
                  itoa(num,pc,16);
                strupr(pc);

            }
        }
        else if(strcmp(opc,"RESB")==0)
        {
            num = to_dec(pc);
            num = num + atoi(opd);
             itoa(num,pc,16);
                strupr(pc);

        }
        fscanf(f1,"%s %s %s",lb,opc,opd);
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
