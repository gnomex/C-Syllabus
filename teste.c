#include <stdio.h>
//--------------------------
int main()
{
    char ch;
    do{
        ch=getchar();
         if(ch==65)
            printf("You pressed UP key\n");
         else if(ch==66)
            printf("You pressed DOWN key\n");
         else if(ch==67)
            printf("You pressed RIGHT key\n");
         else if(ch==68)
            printf("You pressed LEFT key\n");
    }while(ch!='e');
 return 0;
}
