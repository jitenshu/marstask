#include <stdio.h>
#include <stdlib.h>

#define MAX 1000 //max number of readings

//just a quick swap function, useful for sorting 3 values
void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

//returns the middle value (median) from 3 numbers
int median(int a, int b, int c) 
{
    if (a > b) swap(&a, &b);
    if (b > c) swap(&b, &c);
    if (a > b) swap(&a, &b);
    return b;
}

//sanchiko filter - uses median to smooth out sudden spikes
void apply_sanchiko(int *in, int *out, int n) 
{
    for (int i = 1; i < n - 1; i++) 
    {
        out[i] = median(in[i - 1], in[i], in[i + 1]);
    }
    //keep the first and last values as-is
    out[0] = in[0];
    out[n - 1] = in[n - 1];
}

//muchiko filter - simple moving average to smooth out noise
void apply_muchiko(int *in, int *out, int n) 
{
    for (int i = 1; i < n - 1; i++) 
    {
        out[i] = (in[i - 1] + in[i] + in[i + 1]) / 3;
    }
    //edge cases again, just leave them untouched
    out[0] = in[0];
    out[n - 1] = in[n - 1];
}

//loads sensor data from file (line-by-line integers)
int load_data(char *fname, int *arr) 
{
    FILE *f = fopen(fname, "r");
    if (f == NULL)
    {
        printf("file not found\n");
        return 0;
    }

    int count = 0;
    //read till file ends or max hits
    while (fscanf(f, "%d", &arr[count]) != EOF && count < MAX) 
    {
        count++;
    }

    fclose(f);
    return count;
}

//checks which value is the most stable (least variation with neighbors)
int get_most_stable(int *data, int n) 
{
    int best = data[0];
    int min_var = 999999;

    for (int i = 1; i < n - 1; i++) 
    {
        //variation = difference from left + right neighbors
        int diff = abs(data[i] - data[i - 1]) + abs(data[i] - data[i + 1]);
        if (diff < min_var) 
        {
            min_var = diff;
            best = data[i];
        }
    }

    return best;
}

int main() 
{
    int raw[MAX], san[MAX], much[MAX], hybrid[MAX];
    int n = load_data("log.txt", raw); // load file readings into array

    if (n == 0) return 1; // something went wrong loading

    // apply sanchiko filter (median)
    apply_sanchiko(raw, san, n);

    // apply muchiko filter (average)
    apply_muchiko(raw, much, n);

    // hybrid filter: first median, then average
    int temp[MAX];
    apply_sanchiko(raw, temp, n);
    apply_muchiko(temp, hybrid, n);

    // print final results from each filter
    printf("most stable (sanchiko): %d\n", get_most_stable(san, n));
    printf("most stable (muchiko): %d\n", get_most_stable(much, n));
    printf("most stable (hybrid): %d\n", get_most_stable(hybrid, n));

    return 0;
}