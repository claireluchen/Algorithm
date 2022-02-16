int n;
int a[1005], c[1005]; //a is original array, c is the tree's array

int lowbit(int x){ //returns the rightmost 1 and the 0s to the right of it, ex: 110100 would return 100
    return x&(-x);
}

void updata(int i,int k){ //add k to a[i], need to update all relevant c[] that contains a[i]
    while(i <= n){
        c[i] += k;
        i += lowbit(i);
    }
}

int getsum(int i){ //get sum of a[1] to a[i]
    int res = 0;
    while(i > 0){
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}
