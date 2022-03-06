#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
FILE *fis_ct,*fis_pt,*fis_dec;

int gcd(int a,int b);
int eea(int a,int b,int *x,int *y);
unsigned long long prime(unsigned long long x);
int int_length(int x);
unsigned long long exp_mod(unsigned long long x,unsigned long long n,unsigned long long md);
int public_key(int p,int q,int *e,int *phin,int *n);
void private_key(int e,int phin,int *d,int *n);
unsigned long long encryption(unsigned long long message,int e,int n);
unsigned long long decryption(unsigned long long cyphertext,int d,int n);
void general_crypt_decrypt_test(char message[],unsigned long long mess[],int *mess_length,unsigned long long cyt[],int d,int e,int n,unsigned long long dec[]);
void encrypt_string(char message,int e,int n,unsigned long long *cyt);
void decrypt_string(unsigned long long cyt,unsigned long long *dec,int d,int n);

int main()
{
    /*
        p,q 2 random prime numbers
        notations e-encryption, d-decryption, n-modulus, key: (e,n),(d,n)
        phin- phi(n) function
    */
    int p=373,q=953,n,phin,i,e,d=0,cnt=0;
    unsigned long long cyt=0,dec=0;
    char c='0';
    int opt=-1,generat_chei=0,e_flag=0,manual_key=0,pb_key=0,pv_key=0;
    int nr=0x0;
    while(opt!=9)
    {
        printf("----Program de criptare/decriptare----\n");
        printf("--------------------------------------\n");
        printf("1.Tutorial.\n");
        printf("2.Vizualizati valorile prime si cheile curente.\n");
        printf("3.Generare chei noi\n");
        printf("4.Generare chei cu valorile predefinite.\n");
        printf("5.Criptare fisier cu cheia curenta.\n");
        printf("6.Criptare fisier cu alta cheie.\n");
        printf("7.Decriptare fisier cu cheia curenta.\n");
        printf("8.Decriptare fisier cu alta cheie.\n");
        printf("9.Iesire din program.\n");
        printf("--------------------------------------\n\n");
        printf("Introduceti valoarea corespunzatoare optiunii:");
        scanf("%d",&opt);
        printf("\n");
        switch(opt)
        {
        case 1:
        {
            system("cls");
            printf("TUTORIAL PROGRAM CRIPTARE/DECRIPTARE BAZAT PE RSA\n");
            printf("-------------------------------------------------\n");
            printf(" -Pentru a cripta un fisier aveti nevoie de o cheie publica iar pentru a decripta un fisier aveti nevoie\n");
            printf("de o cheie privata\n");
            printf(" -Puteti selecta optiunea 4 pentru a genera cheile predefinite sau puteti selecta optiunea 3 pentru a genera\n");
            printf("o pereche de chei noua\n");
            printf(" -Puteti selecta optiunea 6 pentru a cripta un fisier folosind o cheie publica oarecare.\n");
            printf(" -Puteti selecta optiunea 8 pentru a decripta un fisier folosind cheia dvs. privata ,perechea celei publice.\n");
            printf(" -Pentru a cripta fisierul dvs. text puteti selecta optiunea 5 sau 6,acesta trebuie sa se regaseasca in \n");
            printf("folderul programului sub numele ""RSA_text.txt"", daca acest fisier exista deja in folder puteti sa\n");
            printf("copiati datele dvs. in acesta sau puteti sa il stergeti si adaugati fisierul dvs. cu acelasi nume.\n");
            printf(" -Pentru a decripta un fisier puteti selecta optiunea 7 sau 8, puteti sa criptati un fisier in\n");
            printf("interiorul programului sau sa adaugati in folder fisierul criptat cu numele ""RSA_text_crypted.txt"" .Daca\n");
            printf("exista in folder un fisier cu acest nume, trebuie sa il stergeti.\n");
            printf(" -Daca aveti nevoie sa vizualizati datele curente puteti face asta selectand optiunea 2.\n");
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
        }
        break;
        case 2:
        {
            if(!generat_chei)
            {
                printf("EROARE: Nu au fost generate chei, selectati optiunea corespunzatoare apoi reveniti.\n");
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }
            else
            {
                if(manual_key==0)
                    printf("Numerele prime: p=%d q=%d\n",p,q);
                else if(manual_key==1)
                {
                    printf("Cheile au fost introduse manual, numerele prime nu pot fi afisate.\n");
                }
                printf("Cheile sunt:\n");
                if(pb_key==1)
                    printf("Public key (%d,%d).\n",e,n);
                else if(pb_key==0)
                {
                    printf("Nu a fost generata o cheie publica inca.\n");
                    pb_key=1;
                }
                if(pv_key==1)
                    printf("Private key (%d,%d).\n",d,n);
                else if(pv_key==0)
                {
                    printf("Nu a fost generata o cheie privata inca.\n");
                    pv_key=1;
                }
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }

        }
        break;
        case 3:
        {
            generat_chei=1;
            printf("Intoduceti o valoare prima aleatoare p=");
            scanf("%d",&p);
            printf("\n");
            printf("Intoduceti o alta valoare prima aleatoare q=");
            scanf("%d",&q);
            printf("\n");
            printf("Ati introdus p=%d si q=%d.\n",p,q);
            if(prime(p)&&prime(q))
            {
                e_flag=public_key(p,q,&e,&phin,&n);
                if(e_flag!=-1)
                    private_key(e,phin,&d,&n);
            }
            else
                printf("EROARE: Ambele numere trebuie sa fie prime.\n");
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
        }
        break;
        case 4:
        {
            generat_chei=1;
            p=373;
            q=953;
            printf("Numerele prime sunt: p=%d q=%d\n",p,q);
            public_key(p,q,&e,&phin,&n);
            private_key(e,phin,&d,&n);
            manual_key=0;
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
        }
        break;
        case 5:
        {
            if(!generat_chei)
            {
                printf("EROARE: Nu au fost generata cheia publica, generati una apoi reveniti.\n");
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }
            else
            {
                if((fis_pt=fopen("RSA_text.txt","r"))==NULL)
                {
                    printf("eroare deschidere fisier\n");
                    exit(EXIT_FAILURE);
                }
                if((fis_ct=fopen("RSA_text_crypted.txt","w"))==NULL)
                {
                    printf("eroare deschidere fisier\n");
                    exit(EXIT_FAILURE);
                }
                while(fscanf(fis_pt,"%c",&c)==1)
                {
                    cnt++;
                    encrypt_string(c,e,n,&cyt);
                    fprintf(fis_ct,"%x\n",cyt);
                }
                fclose(fis_ct);
                fclose(fis_pt);
                printf("File encrypted succesfully.\n");
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }
        }
        break;
        case 6:
        {
            if((fis_pt=fopen("RSA_text.txt","r"))==NULL)
            {
                printf("eroare deschidere fisier\n");
                exit(EXIT_FAILURE);
            }
            if((fis_ct=fopen("RSA_text_crypted.txt","w"))==NULL)
            {
                printf("eroare deschidere fisier\n");
                exit(EXIT_FAILURE);
            }
            printf("Public key (e,n)\n");
            printf("Introduceti e=");
            scanf("%d",&e);
            printf("\n");
            printf("Introduceti n=");
            scanf("%d",&n);
            printf("\n");
            generat_chei=1;
            manual_key=1;
            pb_key=1;
            printf("Ati introdus Public key=(%d,%d)\n",e,n);
            while(fscanf(fis_pt,"%c",&c)==1)
            {
                cnt++;
                encrypt_string(c,e,n,&cyt);
                fprintf(fis_ct,"%x\n",cyt);
            }
            fclose(fis_ct);
            fclose(fis_pt);
            printf("File encrypted succesfully.\n");
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
        }
        break;
        case 7:
        {
            if(!generat_chei)
            {
                printf("EROARE: Nu au fost generata cheia privata, generati una apoi reveniti.\n");
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }
            else
            {
                if((fis_ct=fopen("RSA_text_crypted.txt","r"))==NULL)
                {
                    printf("eroare deschidere fisier\n");
                    exit(EXIT_FAILURE);
                }
                if((fis_dec=fopen("RSA_text_decrypted.txt","w"))==NULL)
                {
                    printf("eroare deschidere fisier\n");
                    exit(EXIT_FAILURE);
                }
                while(fscanf(fis_ct,"%x",&nr)==1)
                {
                    decrypt_string((unsigned long long)nr,&dec,d,n);
                    fprintf(fis_dec,"%c",dec);
                }
                fclose(fis_ct);
                fclose(fis_dec);
                printf("File decrypted succesfully.\n");
                printf("\nApasati orice buton pentru a reveni la meniu...\n");
                getch();
                system("cls");
            }
        }
        break;
        case 8:
        {
            if((fis_ct=fopen("RSA_text_crypted.txt","r"))==NULL)
            {
                printf("eroare deschidere fisier\n");
                exit(EXIT_FAILURE);
            }
            if((fis_dec=fopen("RSA_text_decrypted.txt","w"))==NULL)
            {
                printf("eroare deschidere fisier\n");
                exit(EXIT_FAILURE);
            }
            printf("Private key (d,n)\n");
            printf("Introduceti d=");
            scanf("%d",&d);
            printf("\n");
            printf("Introduceti n=");
            scanf("%d",&n);
            printf("\n");
            generat_chei=1;
            manual_key=1;
            pv_key=1;
            printf("Ati introdus Private key=(%d,%d)\n",d,n);
            while(fscanf(fis_ct,"%x",&nr)==1)
            {
                decrypt_string((unsigned long long)nr,&dec,d,n);
                fprintf(fis_dec,"%c",dec);
            }
            fclose(fis_ct);
            fclose(fis_dec);
            printf("File decrypted succesfully.\n");
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
        }
        break;

        case 9:
        {
            printf("Program inchis cu succes.\n");
            printf("\nApasati orice buton...\n");
            getch();
        }
        break;
        default:
            printf("EROARE: Ati selectat o optiune invalida.\n");
            printf("\nApasati orice buton pentru a reveni la meniu...\n");
            getch();
            system("cls");
            break;
        }
    }
    return 0;
}
int gcd(int a,int b)
{
    if(a==0)
        return b;
    return gcd(b%a,a);

}
int eea(int a,int b,int *x,int *y)
{
    int x1,y1,gcd;
    if(a==0)
    {
        *x=0;
        *y=1;
        return b;
    }
    gcd=eea(b%a,a,&x1,&y1);
    *x=y1-(b/a)*x1;
    *y=x1;
    return gcd;
}
unsigned long long prime(unsigned long long x)
{
    unsigned long long i;
    int k=0;
    for(i=1; i<=x; i++)
        if(x%i==0)
        {
            k++;
            if(k>2)
                return 0;
        }

    if(k==2)
        return 1;
    else
        return 0;
}
int int_length(int x)
{
    int k=0;
    while(x!=0)
    {
        x=x/10;
        k++;
    }
    return k;
}
unsigned long long exp_mod(unsigned long long x,unsigned long long n,unsigned long long md)
{
    x=x%md;
    if(n==0)
        return 1;
    if(n==1)
        return x;
    if(n%2==0)
        return (exp_mod((x*x)%md,n/2,md))%md;
    if(n%2==1)
        return (x*exp_mod((x*x)%md,(n-1)/2,md))%md;

}
int public_key(int p,int q,int *e,int *phin,int *n)
{
    int i,flag=0;
    *n=p*q;
    *phin=(p-1)*(q-1);
    for(i=2; i<*phin; i++)
        if(gcd(i,*phin)==1&&gcd(i,*n)==1)// e trebuie sa fie coprim cu phin si n
        {
            flag=1;
            *e=i;
            break;
        }
    if(!flag)
    {
        printf("EROARE: Nu exista valoare a lui E pentru aceste date de intrare.");
        return -1;
    }
    printf("Public key (%d,%d).\n",*e,*n);
}
void private_key(int e,int phin,int *d,int *n)
{
    int x,y,i,k=0;
    // metoda de a gasi cel mai mic d cu algoritmul lui euclid extins(foarte rapid)
    eea(e,phin,&x,&y);
    *d=x;
    if(*d<0)//lucram in modulo phin, deci daca d e negativ d se aduna la phin
        *d=phin+x;
    printf("Private key (%d,%d).\n",*d,*n);
}
unsigned long long encryption(unsigned long long message,int e,int n)
{
    unsigned long long cyphertext;
    cyphertext=exp_mod(message,e,n);
    while(cyphertext<0)
        cyphertext=n+cyphertext;
    return cyphertext;
}
unsigned long long decryption(unsigned long long cyphertext,int d,int n)
{
    unsigned long long plaintext;
    plaintext=exp_mod(cyphertext,d,n);
    while(plaintext<0)
        plaintext=n+plaintext;
    return plaintext;
}
void general_crypt_decrypt_test(char message[],unsigned long long mess[],int *mess_length,unsigned long long cyt[],int d,int e,int n,unsigned long long dec[])
{
    int i;
    for(i=0; i<strlen(message); i++)
    {
        mess[i]=message[i];
    }
    *mess_length=strlen(message);
    printf("Plain text:");
    for(i=0; i<*mess_length; i++)
        printf("%c",mess[i]);
    printf("\n");
    printf("Crypted text:");
    for(i=0; i<*mess_length; i++)
    {
        cyt[i]=encryption(mess[i],e,n);
        printf("%c",cyt[i]);
    }
    printf("\n");
    printf("Decrypted text:");
    for(i=0; i<*mess_length; i++)
    {
        dec[i]=decryption(cyt[i],d,n);
        printf("%c",dec[i]);
    }
    printf("\n");
}
void encrypt_string(char message,int e,int n,unsigned long long *cyt)
{
    unsigned long long temp;
    temp=message;
    *cyt=encryption(temp,e,n);
}
void decrypt_string(unsigned long long cyt,unsigned long long *dec,int d,int n)
{
    *dec=decryption(cyt,d,n);
}


