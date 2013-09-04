void InsertSort() {
    int x = 0;
    for(int i=1; i<size; i++) {
        if(a[i] < a[i-1]) {
            x = a[i];
            a[i] = a[i-1];
            if(i == 1) {
                a[0] = x;   
            } else {
                int j = i -2;
                for(; x < a[j] && j>= 0; j--) {
                    a[j+1] = a[j];   
                }
                a[j+1] = x;
            }
        }
    }
}