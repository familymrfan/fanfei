void SelectSort() {
    for(int i = 0; i < size - 1; i++) {
        int min = a[i];
        int min_index = i;
        for(int j = i+1; j < size; j++) {
            if(min > a[j]) {
                min = a[j];
                min_index = j;
            }
        }
        
        if(i == min_index) 
            continue ;
        int temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}