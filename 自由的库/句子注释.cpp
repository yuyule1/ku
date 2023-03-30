/*#include<stdio.h>
int main()
{
	int N;
	scanf("%d",&N);
	int a[101];
	
	for(int i=0;i<N;i++){
		scanf("%d",&a[i]);
	}
	int j=0;
	for(int i=0;i<N-1;i++){
		for(int i=0;i<N-1-j;i++){
			if(a[i]>a[i+1])
			{int tem=a[i];
			a[i]=a[i+1];
			a[i+1]=tem;
			}
		}
		j++;
	}
	for(int i=0;i<N;i++){
		if(a[i]%3==0){
		
		printf("%d",a[i]);
	break;
	    }
		else if(a[N-1]%3!=0)
		{
		printf("Null");
		break;
	}
	}

	return 0;
}*/
/*#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);

	for(int i=0;i<n;i++){
	int a[100];
	int t; 
	int tmep=0;
	scanf("%d",&t);
	int x=t;
	int count=0;
	for(int k=0;x>0;k++,count++)
	{
		a[k]=x%10;
		x=x/10;
	}
	for(int i=0;i<(count/2);i++)
	{
		if(count==1){
			printf("no\n");
			break;
		}
		else if(a[i]==a[count-1-i])
		{
			tmep=tmep+0;
		}
		else if(a[i]!=a[count-1-i]){
			tmep=tmep+1;
		}
	}
	if(tmep==1)
	printf("yes\n");
	else
	printf("no\n");
}
	return 0;
}*/
/*#include<stdio.h>
#include<string.h>
int main()
{
	char str[101];char b[101];
	int i;
	for(i=0;str[i-1]!='\n';i++)
	{
	scanf("%c",&str[i]);
    }
    str[i]='\0'; 
    for(i=0;b[i-1]!='\n';i++)
    {
    scanf("%c",&b[i]);
    }
    b[i]='\0';
    int m=strlen(str);int n=strlen(b);int check=1;char c[101];strcpy(c,str);char d[101];strcpy(d,c);
    for(i=0;i<m-1;i++){
    	if(c[i]>='a'&&c[i]<='z')
    	c[i]=(c[i]>='a'&&c[i]<='z')?c[i]:c[i]+32;
    	if(c[i]>='A'&&c[i]<='Z')
    	c[i]=(c[i]>='a'&&c[i]<='z')?c[i]:c[i]+32;
    }
    for(i=0;i<n-1;i++){
    	if(b[i]>='a'&&b[i]<='z')
    	b[i]=(b[i]>='a'&&b[i]<='z')?b[i]:b[i]+32;
    	if(b[i]>='A'&&b[i]<='Z')
    	b[i]=(b[i]>='a'&&b[i]<='z')?b[i]:b[i]+32;
    }
    for(i=0;i<m-1;i++)
    {
       if(c[i]==b[0])
    	{  
    		for(int j=0;j<n-1;j++)
    		{	if(b[j]!=c[i+j])
    			{
    			check=0;break;}
    				else ;
    				check=1;
    				
            	}
            
    		
    		break;}
    	
    		else check=0;
    	}
    	(int)d; 
    	for(i=0;i<m-1;i++)
    	d[i]=0;
    	for(i=0;i<m-1;i++){
    		if(c[i]==b[0])
    		{
    		for(int j=0;j<n-1;j++){
    		 if(b[j]==c[i+j])
    			{d[i+j]=(i+j==0)?(d[i+j]=1):(d[i+j]=d[i+j-1]+1);
    			}
    		}
    		}
  }

 
    	if(check==0)
    	{
    		printf("%s",str);
    	}
    	if(check==1)
    	{
    	 		for(int kk=0;kk<m-1;kk++){
    			if((n-2==0)&&(d[kk]==1))
    			{printf("/*%c*//*",str[kk]);}
    //		else if((d[kk]==1)&&(d[kk+n-2]==n-1))
	//			{printf("/*%c",str[kk]);}
    //		else if(d[kk]==n-1&&d[kk-n+2]==1)
    //		    {printf("%c*//*",str[kk]);}
    	//	    else
    	//	    {printf("%c",str[kk]);}
    	//	} 
    	//}
    	//return 0;}
*/
#include<stdio.h>
#include<string.h>
int main()
{	char str[101];char b[101];int i;
	for(i=0;str[i-1]!='\n';i++)
	{
	scanf("%c",&str[i]);
	}
	 str[i]='\0'; 
    for(i=0;b[i-1]!='\n';i++)
    {
	scanf("%c",&b[i]);
	}
	b[i]='\0';
    int m=strlen(str);
	int n=strlen(b);
	int check=1;
	char c[101];
	strcpy(c,str);
	char d[101];
	strcpy(d,c);
    for(i=0;i<m-1;i++)
	{
	if(c[i]>='a'&&c[i]<='z')
	c[i]=(c[i]>='a'&&c[i]<='z')?c[i]:c[i]+32;
    if(c[i]>='A'&&c[i]<='Z')
	c[i]=(c[i]>='a'&&c[i]<='z')?c[i]:c[i]+32;
	}
    for(i=0;i<n-1;i++)
	{
	if(b[i]>='a'&&b[i]<='z')
	b[i]=(b[i]>='a'&&b[i]<='z')?b[i]:b[i]+32;
	if(b[i]>='A'&&b[i]<='Z')
    b[i]=(b[i]>='a'&&b[i]<='z')?b[i]:b[i]+32;}
    for(i=0;i<m-1;i++)
    {
	if(c[i]==b[0])
	{  for(int j=0;j<n-1;j++){if(b[j]!=c[i+j])
    	{
		check=0;
		}
		else ;
		check=1;
		}
		if(check==1)break;
		}
		else check=0;
    	}
		(int)d;
		for(i=0;i<m-1;i++)
    	d[i]=0;for(i=0;i<m-1;i++)
		{
		if(c[i]==b[0])
		{
		for(int j=0;j<n-1;j++)
		{
		if(b[j]==c[i+j])
    			{
				d[i+j]=(i+j==0)?(d[i+j]=1):(d[i+j]=d[i+j-1]+1);
				}
				}
				}
				}
		if(check==0)
    	{
		printf("%s",str);}if(check==1)
    	{
		for(int kk=0;kk<m-1;kk++)
		{
    			if((n-2==0)&&(d[kk]==1))
				{
				printf("/*%c*/",str[kk]);
				}
    		else if((d[kk]==1)&&(d[kk+n-2]==n-1))
			{
			printf("/*%c",str[kk]);
			}
    		else if(d[kk]==n-1&&d[kk-n+2]==1) 
			{
			printf("%c*/",str[kk]);
			}
    		else 
			{
			printf("%c",str[kk]);
			}
			}
			}
				return 0;
}





















































