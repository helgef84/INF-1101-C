#include <stdio.h>

int fibonacci(int i);

int fibonacci(int i){

    if(i == 0){
        return 0;
    }
    if( i == 1){
        return 1;
    }

    return fibonacci(i - 1) + fibonacci(i - 2);

}


unsigned long int factorial(unsigned int i);

unsigned long int factorial(unsigned int i){
    if(i <= 1){
        return 1;
    }
    return i * factorial(i - 1);
}

int sumDigits(int num);


int sumDigits(int num){
    static int sum = 0;
    if(num > 0){
        sum += (num % 10);
        sumDigits(num / 10);
    }
    return sum;
}

int productDigits(int num);

int productDigits(int num){
    static int sum = 1;

    if(num > 0){
        sum *= (num % 10);
        productDigits(num / 10);
    }
    return sum;
}








int main(){
    int i;
    int j = 25;
    int num = 125235;
    int num2 = 6243;

    for(i = 0; i < 10; i ++){
        printf("%d\n", fibonacci(i));
    }
    printf("Factorial of %d : %d\n", j, factorial(j));  
    printf("Summen av %d = %d\n", num, sumDigits(num));
    printf("Produktet av %d = %d\n", num2, productDigits(num2));

    return 0;
}