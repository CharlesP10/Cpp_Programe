#include <bits/stdc++.h>
using namespace std;

char arr[10010], _stack[50], _math[10010];
int i = 0, top = -1, j = -1;

double num1 = 0, num2 = 0;
int _sum[100];
double _count[10010];
int l = -1, n = -1;


//入栈
void _push(int i){
    top++;
    _stack[top] = arr[i];
}

//出栈（至组中）
void _pop(int* pj){
    (*pj)++;
    _math[(*pj)] = _stack[top];
    _stack[top] = 0;
    top--; 
}

//存入组
void _save(int i){
    j++;
    _math[j] = arr[i];
}

//遍历栈（寻找更高级运算符）
int _h_high(int top){
    int ans = -1;
    for(int r = top; r >= 0; r--){
        if(_stack[r] == 42 || _stack[r] == 47){
            ans = r; break;
        }
    }
    return ans;
}

//遍历栈（寻找左括号）
int _h_bra(int top){
    int ans = -1;
    for(int r = top; r >= 0; r--){
        if(_stack[r] == 40){
            ans = r; break;
        }
    }
    return ans;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void _in(double sum){
    n++;
    _count[n] = sum;
}

void _out(){
    _count[n] = 0;
    n--; 
}

void _in_sum(int k){
    l++;
    _sum[l] = _math[k]-48;
}

double _cal(){
    double ans = 0;
    for(int k = 0; k <= l; k++){
        ans += _sum[k] * pow(10, l-k);
    }
    for(int k = 0; k <= l; k++) _sum[k] = 0;
    return ans;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
//表达式输入
    string a; cin >> a; int len = a.length();
//原始表达式初始化，添加分隔符（逗号）
    int r;
    for(r = 0, i = 0; r < len; r++){
        if((a[r] >= 40 && a[r] <= 43) || a[r] == 45 || a[r] == 47){
            if(a[r-1] >= 48 && a[r-1] <= 57){
                arr[i] = ','; i++;
            }
        }
        arr[i] = a[r]; i++;
    }
    if(arr[i-1] >= 48 && arr[i-1] <= 57){
        arr[i] = ','; i++;
    }
    len = i;
//show
    {
    cout << len << endl;
    for(int k = 0; k < len; k++) {cout << arr[k]; } cout << endl << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////

//表达式形式转换
    for(i = 0; i < len; i++){
        if((arr[i] >= 48 && arr[i] <= 57) || arr[i] == 44) _save(i);
        else if((arr[i] >= 40 && arr[i] <= 43) || arr[i] == 45 || arr[i] == 47){
            if(arr[i] == '*' || arr[i] == '/') _push(i);
            else if(arr[i] == '+' || arr[i] == '-'){
                int _h = _h_high(top), _b = _h_bra(top);
                if(_h != -1){
                    if(_b == -1){
                        while(_h_high(top) != -1) _pop(&j);
                    }
                    else{
                        while(_h_high(top) > _b) _pop(&j);
                        _stack[top] = 0; top--;
                    }
                }
                _push(i);
            }
            else if(arr[i] == '(') _push(i);
            else if(arr[i] == ')'){
                while(_stack[top] != '(') _pop(&j);
                _stack[top] = 0; top--;
            }
        }
    //show
        // {cout << "i=" << i << " top=" << top << " j=" << j << endl;
        // cout << "_h_high=" << _h_high(top) << " _h_bra=" << _h_bra(top) << endl << "arr = ";
        // for(int i = 0; i < len; i++) {cout << arr[i]; } cout << endl << "stack = ";
        // for(int i = 0; i < len; i++) {cout << _stack[i]; } cout << endl << "math = ";
        // for(int i = 0; i < len; i++) {cout << _math[i]; } cout << endl << endl;}
    }
    while(top >= 0) _pop(&j);

//show
    {
    cout << "top=" << top << " j=" << j << endl;
    cout << "_h_high=" << _h_high(top) << " _h_bra=" << _h_bra(top) << endl << "arr = ";
    for(int i = 0; i < len; i++) {cout << arr[i]; } cout << endl << "stack = ";
    for(int i = 0; i < len; i++) {cout << _stack[i]; } cout << endl << "math = ";
    for(int i = 0; i < len; i++) {cout << _math[i]; } cout << endl << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////

    len = 0;
    while(_math[len] != 0) len++;

    for(int k = 0;k < len; k++){
        if(_math[k] >= 48 && _math[k] <= 57) _in_sum(k);
        else if(_math[k] == ','){
            _in(_cal());
        }
        else if(_math[k] == '+' || _math[k] == '-' || _math[k] == '*' || _math[k] =='/'){
            num1 = _count[n-1]; num2 = _count[n];
            _out(); _out();
            if(_math[k] == '+') _in(num1 + num2);
            if(_math[k] == '-') _in(num1 - num2);
            if(_math[k] == '*') _in(num1 * num2);
            if(_math[k] == '/') _in(num1 / num2);
        }
        
    //show
        {
        cout << "k=" << k << " l=" << l << " n=" << n << endl << "sum=";
        for(int i = 0; i <= l; i++) {cout << _sum[i] << ','; } cout << endl << "count=";
        for(int i = 0; i <= n; i++) {cout << _count[i] << ','; } cout << endl << endl;
        }
    }
    // cout << "ans = " << _count[0];

//show
    {
    cout << "l=" << l << " n=" << n << endl << "sum=";
    for(int i = 0; i <= l; i++) {cout << _sum[i] << ","; } cout << endl << "count=";
    for(int i = 0; i <= n; i++) {cout << _count[i] << ','; } cout << endl;
    }
    
    return 0;
}