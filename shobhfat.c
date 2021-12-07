#include<stdio.h>
#include<stdlib.h>
void main(){
    int index=0,i,j,k,size1,size2;
    printf("Enter the number of pages:\n");
    scanf("%d",&size1);
    int page[50];
    printf("Enter the reference string:\n");
    for(i=0;i<size1;i++){
        // scanf("%d",&page[i]);
        page[i]=rand()%10+1;
    }
    printf("Enter the number of frames:\n");
    scanf("%d",&size2);
    int arr[10],used[10];
    for(i=0;i<size2;i++){
        arr[i]=-1;
    }
    int page_fault=0;
    printf("Ref. String\tFrames\n");
    for(i=0;i<size1;i++){
        int find=0;
        //page hit
        for(j=0;j<size2;j++){
            if(arr[j]==page[i]){
            find=1;
            break;
            }
        }
        //page miss
        if(find==0){
            page_fault++;
            int stop=0;
            int var=0;
            for(j=0;j<size2;j++){
                used[j]=0;
            }
            //traversing the pages which are ahead of the current page
            for(j=i+1;j<size1 && stop==0;j++){
                for(k=0;k<size2 && stop==0;k++){
                    //if we find any page in future from the page array as same in 
                    //the frame array and that element is not 
                    //repeated yet i.e. its used is 0s
                    if(page[j]==arr[k] && used[k]==0){
                        //that means that page will repeat shortly than others
                        used[k]=1;
                        var++;
                    }
                    //we have found that which element is not nearby then 
                    //other elements in the pages in the future or element
                    // in the frame is not repeated in the future in the pagez
                    if(var==size2-1 || j==size1-1){
                        int l;
                        //finding the index of the element by which we have to replace
                        for(l=0;l<size2;l++){
                            //finding the element by using used array for which 
                            //used is zero that is it is not in the future nearby 
                            //then other elements in the frame
                            if(used[l]==0){
                                index=l;
                                stop=1;
                                break;
                            }
                        }
                    }
                }
            }
            //if there is still an empty space in the frame then we find the index
            for(j=0;j<size2;j++){
                if(arr[j]==-1){
                    index=j;
                    break;
                }
            }
            //inserting in the frame the new page
            arr[index]=page[i];
        }
        printf("%d\t\t",page[i]);
        for(k=0;k<size2;k++){
            printf("%d\t",arr[k]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d",page_fault);
}