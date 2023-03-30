//1.三位数求和


/*#include <iostream>
using namespace std;
class geweihe{
public:
      geweihe(){}
	  int geweihe1(int num){
	  int sum=0;
	  int remainder=0;	    // 计算各位数字之和
    remainder = num % 10; // 获取个位数
    sum += remainder;
    num /= 10;

    remainder = num % 10; // 获取十位数
    sum += remainder;
    num /= 10;

    remainder = num % 10; // 获取百位数
    sum += remainder;

	 return sum; }	
};
int main() {
    int num;
    
    cout << "请输入一个3位十进制整数：";
    cin >> num;
    geweihe xx;
    xx.geweihe1(num);

    cout << "各位数字之和为：" << xx.geweihe1(num) << endl;

    return 0;
}
*/ 


/*#include <iostream>
using namespace std;

int main() {
    int num, sum = 0, remainder;

    cout << "请输入一个3位十进制整数：";
    cin >> num;

    // 计算各位数字之和
    remainder = num % 10; // 获取个位数
    sum += remainder;
    num /= 10;

    remainder = num % 10; // 获取十位数
    sum += remainder;
    num /= 10;

    remainder = num % 10; // 获取百位数
    sum += remainder;

    cout << "各位数字之和为：" << sum << endl;

    return 0;
}*/


//2.找出只出现两次的数字

//c语言版
 
/*#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int arr[MAX_SIZE];
    int n, i, j;
    int flag, count;
    int result[MAX_SIZE]; // 存储只出现两次的数
    int rsize = 0; // result 数组的大小

    printf("请输入整数的个数：");
    scanf("%d", &n);

    printf("请输入整数：");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 找出只出现两次的数
    for(i = 0; i < n; i++) {
        count = 0;
        for(j = i + 1; j < n; j++) { // 从 i+1 开始遍历，避免重复计算
            if(arr[i] == arr[j]) {
                count++;
                //arr[j] = -1; // 标记已经出现两次的数
            }
        }
        if(count >= 1) {
            result[rsize] = arr[i]; // 存储只出现两次的数
            rsize++;
        }
    }
    int cou = 0;
	int a = 0;
    for(i = 0; i < rsize; i++){
    	for(j = 0; j < rsize; j++){
    		if(i==j) continue;
    		if(result[i]==result[j]){
    			cou++;
    			break;
    		}
    	}
    	if(cou == 0){
       	printf("%d ",result[i]);
        a++;
		}
		else
    	cou=0;
    }
    	if(a == 0)
    	printf("error");
    
    return 0;
}*/


//c++版


/*#include <iostream>
using namespace std;

#define MAX_SIZE 100
class findtwo{
public:
	findtwo(){
	}
	int xx(){
	int arr[MAX_SIZE];
    int n, i, j;
    int flag, count;
    int result[MAX_SIZE]; // 存储只出现两次的数
    int rsize = 0; // result 数组的大小
	cout << "请输入整数的个数：";
    cin >> n;

    cout << "请输入整数：";
    for(i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // 找出只出现两次的数
    for(i = 0; i < n; i++) {
        count = 0;
        for(j = i + 1; j < n; j++) { // 从 i+1 开始遍历，避免重复计算
            if(arr[i] == arr[j]) {
                count++;
                //arr[j] = -1; // 标记已经出现两次的数
            }
        }
        if(count >= 1) {
            result[rsize] = arr[i]; // 存储只出现两次的数
            rsize++;
        }
    }
    int cou = 0;
    int a = 0;
    for(i = 0; i < rsize; i++){
        for(j = 0; j < rsize; j++){
            if(i==j) continue;
            if(result[i]==result[j]){
                cou++;
                break;
            }
        }
        if(cou == 0){
            cout << result[i] << " ";
            a++;
        }
        else
            cou=0;
    }
    if(a == 0)
        cout << "error";
        return 0;
	}
};
int main() {

    findtwo aa;
    aa.xx();

    return 0;
}*/ 

//3.电子邮件地址判断
 
 
//c语言版 
/*#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidEmail(char email[]) {
    int len = strlen(email);
    int atPos = -1, dotPos = -1;

    // 扫描字符串，判断@和.的位置
    for (int i = 0; i < len; i++) {
        char c = email[i];
        if (c == '@') {
            if (atPos != -1) {
                return 0; // 多个@，非法
            }
            atPos = i;
        } else if (c == '.') {
            if (dotPos != -1) {
                return 0; // 多个.，非法
            }
            if (i == atPos + 1 || i == len - 1) {
                return 0; // .紧挨@后，或在最末位，非法
            }
            dotPos = i;
        } else if (!isalnum(c) && c != '_' && c != '-') {
            return 0; // 非法字符，非法
        }
    }

    // 检查@和.的位置
    if (atPos == -1 || dotPos == -1 || atPos > dotPos) {
        return 0; // 缺少@或.，或它们的位置不对，非法
    }

    return 1; // 合法
}

int main() {
    char input[100];
    printf("请输入电子邮件地址：");
    fgets(input, 100, stdin);
    // 去掉字符串中的换行符
    input[strcspn(input, "\n")] = 0;

    if (isValidEmail(input)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}*/


//c++版
 
/*#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class EmailValidator {
public:
    EmailValidator() {}

    bool isValidEmail(const string& email) {
        int len = email.length();
        int atPos = -1, dotPos = -1;

        // 扫描字符串，判断@和.的位置
        for (int i = 0; i < len; i++) {
            char c = email[i];
            if (c == '@') {
                if (atPos != -1) {
                    return false; // 多个@，非法
                }
                atPos = i;
            } else if (c == '.') {
                if (dotPos != -1) {
                    return false; // 多个.，非法
                }
                if (i == atPos + 1 || i == len - 1) {
                    return false; // .紧挨@后，或在最末位，非法
                }
                dotPos = i;
            } else if (!isalnum(c) && c != '_' && c != '-') {
                return false; // 非法字符，非法
            }
        }

        // 检查@和.的位置
        if (atPos == -1 || dotPos == -1 || atPos > dotPos) {
            return false; // 缺少@或.，或它们的位置不对，非法
        }

        return true; // 合法
    }
};

int main() {
    EmailValidator validator;
    string input;

    cout << "请输入电子邮件地址：";
    getline(cin, input);

    if (validator.isValidEmail(input)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}*/


//4.n个分数相加化简


/*#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int gcd(int a, int b){   // 求最大公约数
    if(b == 0) return a;
    return gcd(b, a % b);
}
class fenshu{
public:
	fenshu(){
	}
	int he(){
		    int n;
    cout<<"输入分数个数："; 
    cin>>n;
    int fz[n], fm[n];
    for(int i=0;i<n;i++){
        scanf("%d/%d",&fz[i],&fm[i]);
        if(fm[i] == 0){  // 判断分母是否为0
            cout<<"error"<<endl;
            return 0;
        }
    }
    int sum_fz = fz[0], sum_fm = fm[0];
    for(int i=1;i<n;i++){
        int tmp_fm = fm[i] * sum_fm / gcd(fm[i], sum_fm);
        int tmp_fz1 = (tmp_fm * fz[i] )/ fm[i] ;
        int tmp_fz2 = (tmp_fm *sum_fz)/ sum_fm;
        sum_fz = tmp_fz1 + tmp_fz2;
        sum_fm = tmp_fm;
        int tmp_gcd = abs(gcd(sum_fz, sum_fm));  // 求最大公约数
        sum_fz /= tmp_gcd;
        sum_fm /= tmp_gcd;
    }
    if(sum_fm == 1){
        cout<<sum_fz<<endl;  // 分母为1，直接输出分子
    }else if(sum_fz == 0){
        cout<<"0"<<endl;  // 分子为0，输出0
    }else{
        cout<<sum_fz<<"/"<<sum_fm<<endl;  // 输出分数
    }
    return 0;
	}
};
int main(){
    fenshu aa;
    aa.he();
    return 0;
}*/



//5.加权求和

 
/*#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    int cnt[26] = {0}; // 记录每个字母出现的次数
    int n = s.length();

    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    sort(cnt, cnt + 26, greater<int>()); // 将次数从大到小排序

    int ans = 0;
    int weight = 26;

    for (int i = 0; i < 26 && cnt[i]; i++) {
        ans += cnt[i] * weight--;
    }

    cout << ans << endl;

    return 0;
}*/


#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
class jiaquan{
public:
	jiaquan(){
	}
	int he(){
		string s;
    cin >> s;

    int cnt[26] = {0}; // 记录每个字母出现的次数
    int n = s.length();

    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    sort(cnt, cnt + 26, greater<int>()); // 将次数从大到小排序

    int ans = 0;
    int weight = 26;

    for (int i = 0; i < 26 && cnt[i]; i++) {
        ans += cnt[i] * weight--;
    }

    cout << ans << endl;
    return 0;
	}
};

int main() {
    jiaquan aa;
    aa.he() ;
    return 0;
}






