
int subarraySum(int* nums, int numsSize, int k) {
    //element by element parcours
        //we eat and advance, continue eating until we meet target or surpass target, or reach end of array

    int result = 0;

    for(int anchor = 0; anchor < numsSize; anchor++){
        int sum = nums[anchor];
        if(sum == k){result++;}       
        int eater = anchor + 1;
        while(eater < numsSize){
            sum += nums[eater];
            eater++;
            if(sum == k){
            result++;
            }
        }       
    }
    return result;
}

