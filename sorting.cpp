#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>

#define DATA_SAMPLE 100

int cmp;
int swp;
int att;

void shuffleArray(std::vector<int>& array){
    auto seed = std::rand();
    auto rnd = std::default_random_engine(seed);
    std::shuffle(array.begin(), array.end(), rnd);
}

void bubbleSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    auto begin = std::chrono::steady_clock::now();
    for(int i=0; i<array.size()-1; ++i){
        for(int j=0; j<array.size()-1; ++j){
            if(array[j]>array[j+1]){
                std::swap(array[j], array[j+1]);
                ++swp;
            }
            ++cmp;
        }
    }
    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

void cocktailShakerSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    int n = array.size();
    auto begin = std::chrono::steady_clock::now();
    for(int i=0; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            if(array[j]<array[j-1]){
                std::swap(array[j], array[j-1]);
                ++swp;
            }
            ++cmp;
        }
        --n;
        for(int k=n-1; k>i; --k){
            if(array[k]<array[k-1]){
                std::swap(array[k], array[k-1]);
                ++swp;
            }
            ++cmp;
        }
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

int getNextGap(int gap){
    gap = (gap*10)/13;
  
    if (gap < 1)
        return 1;
    return gap;
}

void combSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    int gap = array.size();
    bool swapped = true;
    auto begin = std::chrono::steady_clock::now();
    while(gap!=1 || swapped == true){
        gap = getNextGap(gap);
        swapped = false;
        for(int i=0; i<array.size()-gap; ++i){
            if(array[i]>array[i+gap]){
                std::swap(array[i], array[i+gap]);
                swapped = true;
                ++swp;
            }
            ++cmp;
        }
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

void selectionSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    auto begin = std::chrono::steady_clock::now();
    for(int step=0; step<array.size()-1; ++step){
        int min_i = step;
        for(int i=step+1; i<array.size(); ++i){
            if(array[i]<array[min_i]){
                min_i = i;
            }
            ++cmp;
        }
        std::swap(array[min_i], array[step]);
        ++swp;
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

void insertionSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    auto begin = std::chrono::steady_clock::now();
    for(int step=1; step<array.size(); ++step){
        int key = array[step];
        int j=step-1;

        while(key<array[j] && j>=0){
            ++cmp;
            array[j+1] = array[j];
            ++att;
            --j;
        }
        array[j+1] = key;
        ++att;
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

void gnomeSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    auto begin = std::chrono::steady_clock::now();
    int index = 0;
    while(index<array.size()){
        if(index==0) ++index;
        ++cmp;
        if(array[index]>=array[index-1]){
            ++index;
        }
        else{
            std::swap(array[index], array[index-1]);
            --index;
            ++swp;
        }
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

void shellSort(std::vector<int>& array, std::chrono::nanoseconds& duration){
    auto begin = std::chrono::steady_clock::now();
    for(int gap=array.size()/2; gap>0; gap/=2){
        for(int i = gap; i<array.size(); ++i){
            int temp = array[i];
            ++att;
            int j;
            for(j=i; j>=gap && array[j-gap]>temp; j-=gap){
                array[j] = array[j-gap];
            }
            ++cmp;
            array[j] = temp;
            ++att;
        }
    }

    auto end = std::chrono::steady_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

int main(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> array;
    for(int i=1; i<DATA_SAMPLE; ++i) array.push_back(i);

    // Shuffle numbers
    shuffleArray(array);

    // BUBBLE SORT
    cmp = 0, swp = 0;
    std::chrono::nanoseconds bubbleDuration = std::chrono::nanoseconds(0);
    bubbleSort(array, bubbleDuration);
    shuffleArray(array);
    bubbleSort(array, bubbleDuration);
    shuffleArray(array);
    bubbleSort(array, bubbleDuration);
    shuffleArray(array);
    std::cout<<"BUBBLE SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<bubbleDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<swp<<std::endl;

    // SHAKER SORT
    cmp = 0, swp = 0;
    std::chrono::nanoseconds shakerDuration = std::chrono::nanoseconds(0);
    cocktailShakerSort(array, shakerDuration);
    shuffleArray(array);
    cocktailShakerSort(array, shakerDuration);
    shuffleArray(array);
    cocktailShakerSort(array, shakerDuration);
    shuffleArray(array);
    std::cout<<"SHAKER SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<shakerDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<swp<<std::endl;
    
    // COMB SORT
    cmp = 0, swp = 0;
    std::chrono::nanoseconds combDuration = std::chrono::nanoseconds(0);
    combSort(array, combDuration);
    shuffleArray(array);
    combSort(array, combDuration);
    shuffleArray(array);
    combSort(array, combDuration);
    shuffleArray(array);
    std::cout<<"COMB SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<combDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<swp<<std::endl;

    // SELECTION SORT
    cmp = 0, swp = 0;
    std::chrono::nanoseconds selectionDuration = std::chrono::nanoseconds(0);
    selectionSort(array, selectionDuration);
    shuffleArray(array);
    selectionSort(array, selectionDuration);
    shuffleArray(array);
    selectionSort(array, selectionDuration);
    shuffleArray(array);
    std::cout<<"SELECTION SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<selectionDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<swp<<std::endl;

    // INSERTION SORT
    cmp = 0, att = 0;
    std::chrono::nanoseconds insertionDuration = std::chrono::nanoseconds(0);
    insertionSort(array, insertionDuration);
    shuffleArray(array);
    insertionSort(array, insertionDuration);
    shuffleArray(array);
    insertionSort(array, insertionDuration);
    shuffleArray(array);
    std::cout<<"INSERTION SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<insertionDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<att/3<<std::endl;

    // GNOME SORT
    cmp = 0, swp = 0;
    std::chrono::nanoseconds gnomeDuration = std::chrono::nanoseconds(0);
    gnomeSort(array, gnomeDuration);
    shuffleArray(array);
    gnomeSort(array, gnomeDuration);
    shuffleArray(array);
    gnomeSort(array, gnomeDuration);
    shuffleArray(array);
    std::cout<<"GNOME SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<gnomeDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<swp<<std::endl;

    // SHELL SORT
    cmp = 0, att = 0;
    std::chrono::nanoseconds shellDuration = std::chrono::nanoseconds(0);
    shellSort(array, shellDuration);
    shuffleArray(array);
    shellSort(array, shellDuration);
    shuffleArray(array);
    shellSort(array, shellDuration);
    shuffleArray(array);
    std::cout<<"SHELL SORT:"<<std::endl;
    std::cout<<"Average exec. time - "<<shellDuration.count()*1e-9/3<<" seconds. Average comparisons - "<<cmp/3<<", average attributions - "<<att/3<<std::endl;


    return 0;
}