#include <stdio.h>

int __cdecl func(int x);

int main() {
    int user_input;
    scanf_s("%d", &user_input);
    int result = func(user_input);
    printf("Num %d took total %d iterations\n", user_input, result);
    return 0;
}

int __cdecl func(int x) {
    int result = 0;
    while (x != 1) {
        if (x % 2 != 0)
            x = 3 * x + 1;
        else
            x = x / 2;
        result++;
    }
    return result;
}
