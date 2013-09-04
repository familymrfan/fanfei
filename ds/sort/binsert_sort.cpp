void BInsertSort() {
    int x = 0;
    for(int i=1;i<size;i++) {
        if(a[i] >= a[i-1])
            continue ;
        int low = 0;
        int hign = i-1;
        while(low<=hign) {
            int m = (low + hign)/2;
            if(a[m] >= a[i]) {
                hign = m -1;   
            } else {
                low = m + 1;   
            }
        }
        x = a[i];
        int j = i - 1;
        for(;j>=hign+1 ;j--) {
            a[j+1] = a[j];   
        }
        a[hign+1] = x;
        
    }
    
}