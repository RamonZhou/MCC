// void printi(int v) {
//     printf(": %d\n", v);
// }

typedef struct {
    int a, b;
} point;

int gl = 2;

int main() {
    point k;
    k.a = 1;
    k.b = 2;
    printf("%d %d\n", k.b * k.a + (k.a = 2), k.a);
    const int p = 1;
    p = 2;
    // int array(12) array(3) arr;
    // int a = 5 + 5;
    // int b = a + 2;
    // scanf("%d", &a);
    // printf("A: %d\n", a);
    // double f = 0.1;
    // gl = 5;
    // printf("--Hello world! %.1lf!\n" + 2, a + 1 + b + f);
    // for (int i = 0; i <= 10.0; i = i + 1) {
    //     arr[1][i] = i;
    //     if (i == 5) {
    //         printi(arr[1][i] * gl + f);
    //     } else {
    //         printf("! i = %d\n", i);
    //     }
    // }
    return 0;
}