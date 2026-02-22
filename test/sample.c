int add(int a, int b) {
    return a + b;
}

int square(int x) {
    return x * x;
}

int main() {
    return square(add(2, 3));
}
