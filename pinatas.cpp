#include <iostream>
#include <vector>
#include <algorithm>

class Pinata{
public:
    int value;
    int sum;
    Pinata *left;
    Pinata *right;

    void update_sum() {
        sum = 0;
        if (left) sum += left->value;
        else sum += 1;
        if (right) sum += right->value;
        else sum += 1;
    }
};

bool compare(Pinata *a, Pinata *b) {
    return a->sum > b->sum;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Pinata> pinatas(n);
    std::vector<Pinata*> pinata_ptrs(n);

    // filling
    for (int i = 0; i < n; ++i) {
        std::cin >> pinatas[i].value;
        pinata_ptrs[i] = &pinatas[i];
    }

    // setting neighbors
    for (int i = 0; i < n; ++i) {
        pinatas[i].left = (i != 0) ? &pinatas[i - 1] : nullptr;
        pinatas[i].right = (i != n - 1) ? &pinatas[i + 1] : nullptr;
        pinatas[i].update_sum();
    }

    std::sort(pinata_ptrs.begin(), pinata_ptrs.end(), compare);

    int result = 0;

    while (!pinata_ptrs.empty()){
        // adding value to the result
        Pinata *best_pinata = pinata_ptrs[0];
        int candies = best_pinata->value;
        if (best_pinata->left) candies *= best_pinata->left->value;
        if (best_pinata->right) candies *= best_pinata->right->value;
        result += candies;

        // correcting sums of neighbors
        if (best_pinata->left) best_pinata->left->sum -= best_pinata->value;
        if (best_pinata->right) best_pinata->right->sum -= best_pinata->value;

        // correcting neighbors
        if (best_pinata->left) best_pinata->left->right = best_pinata->right;
        if (best_pinata->right) best_pinata->right->left = best_pinata->left;

        // updating sums of neighbors
        if (best_pinata->left) best_pinata->left->update_sum();
        if (best_pinata->right) best_pinata->right->update_sum();

        // deleting pinata
        pinata_ptrs.erase(pinata_ptrs.begin());

        // sorting vector
        std::sort(pinata_ptrs.begin(), pinata_ptrs.end(), compare);
    }

    std::cout << result;
    return 0;
}
