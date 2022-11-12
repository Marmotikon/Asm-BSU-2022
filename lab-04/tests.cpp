#include <random>
#include <vector>
#include <iostream>

#include "gtest/gtest.h"

extern "C" int32_t AsmProduct(
    const int32_t* array, int32_t size, int32_t module);
extern "C" int64_t AsmSpecialSum(
    const int64_t* array, int64_t size, int64_t module);
extern "C" int64_t AsmArrayFormula(
    const int32_t* array, int32_t size);
extern "C" int64_t AsmCompare(
    const int64_t* array1, int64_t size1,
    const int64_t* array2, int64_t size2);
extern "C" void AsmSimpleModify(int32_t* array, int32_t size);
extern "C" void AsmSetToSequence(int64_t* array, int32_t size);
extern "C" void AsmRotateInGroups(
    int64_t* array, int32_t size, int32_t k);
extern "C" int32_t AsmRemoveIfSimilar(
    int64_t* array, int32_t size, int64_t x, int64_t d);
extern "C" void AsmReplaceWithGroup(
    int64_t* array, int32_t* size, int32_t k);
extern "C" void AsmMerge(
    const int64_t* array1, int64_t size1,
    const int64_t* array2, int64_t size2,
    int64_t* result);
extern "C" void AsmModify2D(
    int64_t** array, int64_t n, int64_t m);
extern "C" int32_t AsmFindSorted(
    int32_t** array, int32_t n, int32_t m);
// ---------------------------------------------------------

TEST(AsmProduct, Simple) {
  // int a[5] = {-3, 2, 1, 4, 3};
  // ASSERT_EQ(AsmProduct(a, 5, 5), -3);
  // a[0] = -8;
  // ASSERT_EQ(AsmProduct(a, 5, 5), -3);
  {
    int a[5] = {-3, 2, 1, 1, 1};
    ASSERT_EQ(AsmProduct(a, 5, 5), 4);
  }
  {
    int a[5] = {-3, 2,
                1, 4, 3};
    ASSERT_EQ(AsmProduct(a, 5, 5), 3);
  }
  {
    int a[5] = {-8, 7, 1, -1, 3};
    ASSERT_EQ(AsmProduct(a, 5, 5), 3);
  }
  {
    int a[5] = {-8, 7, 1, 300, 3};
    ASSERT_EQ(AsmProduct(a, 5, 5), 0);
  }
}

TEST(AsmSpecialSum, Simple) {
  // {
  //   int64_t a[5] = {1, 2, 1, 4, 3};
  //   ASSERT_EQ(AsmSpecialSum(a, 1, 5), 1);
  //   ASSERT_EQ(AsmSpecialSum(a, 2, 5), 3);
  //   ASSERT_EQ(AsmSpecialSum(a, 3, 5), 4);
  //   ASSERT_EQ(AsmSpecialSum(a, 4, 5), 3);
  //   ASSERT_EQ(AsmSpecialSum(a, 5, 5), 1);
  // }
  {
    int64_t a[5] = {1, 2, 1, 4, 3};
    ASSERT_EQ(AsmSpecialSum(a, 1, 5), 1);
  }
  {
    int64_t a[5] = {4, 4, 4, 4, 4};
    ASSERT_EQ(AsmSpecialSum(a, 1, 5), 0);
    ASSERT_EQ(AsmSpecialSum(a, 5, 5), 0);
  }
  {
    int64_t a[5] = {2, 1, 1, 4, 3};
    ASSERT_EQ(AsmSpecialSum(a, 2, 5), 1);
    ASSERT_EQ(AsmSpecialSum(a, 3, 5), 2);
    ASSERT_EQ(AsmSpecialSum(a, 4, 5), 2);
    ASSERT_EQ(AsmSpecialSum(a, 5, 5), 2);
  }
  {
    int64_t a[5] = {2, 2, 1, 4, 3};
    // ASSERT_EQ(AsmSpecialSum(a, 5, 5), 1);
    ASSERT_EQ(AsmSpecialSum(a, 1, 5), 0);
    ASSERT_EQ(AsmSpecialSum(a, 2, 5), 0);
    ASSERT_EQ(AsmSpecialSum(a, 3, 5), 1);
  }
}

TEST(AsmArrayFormula, Simple) {
  {
    int32_t a[6] = {2, -8, 1, 14, 3, 9};
    int ans = 0;
    for (int i = 0; i < 6; i += 2) {
      if (i & 2) {
        ans -= (i + 1) * a[i] * (i + 2) * a[i + 1];
      } else {
        ans += (i + 1) * a[i] * (i + 2) * a[i + 1];
      }

      ASSERT_EQ(AsmArrayFormula(a, i + 2), ans);
    }
  }
}

TEST(AsmCompare, Simple) {
  {
    int64_t a[6] = {2, -8, 1, 4, 5, 6};
    int64_t b[6] = {2, -8, 1, 4, 5, 6};
    ASSERT_EQ(AsmCompare(a, 6, b, 6), 0);
    ASSERT_EQ(AsmCompare(a, 6, b, 1), 5);
    ASSERT_EQ(AsmCompare(a, 6, b, 3), 3);
  }
  {
    int64_t a[6] = {2, -8, 1, 4, 5, 6};
    int64_t b[6] = {6, 5, 4, 1, -8, 2};
    ASSERT_EQ(AsmCompare(a, 6, b, 6), 0);
    ASSERT_EQ(AsmCompare(a, 6, b, 1), 5);
    ASSERT_EQ(AsmCompare(a, 6, b, 3), 3);
  }
}

TEST(AsmSimpleModify, Simple) {
  {
    int32_t a[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int32_t b[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 11; i++) {
      if (b[i] % 5 == 0) {
        b[i] = 0;
      } else if ((b[i] % 5) % 2 == 0) {
        b[i] = 1;
      } else {
        b[i] = -1;
      }
    }
    AsmSimpleModify(a, 11);
    for (int i = 0; i < 11; i++) {
      // std::cerr << i << " " << a[i] << " " << b[i] << '\n';
      ASSERT_EQ(a[i], b[i]);
    }
  }
}

TEST(AsmSetToSequence, Simple) {
  {
    int64_t a[5] = {1, 5, 2, 4, 3};
    int64_t b[5] = {1, 2, 2, 4, 3};
    AsmSetToSequence(a, 5);

    for (int i = 0; i < 5; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[5] = {5, 1, 2, 4, 3};
    int64_t b[5] = {1, 2, 2, 4, 3};
    AsmSetToSequence(a, 5);

    for (int i = 0; i < 5; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[5] = {2, 1, 3, 4, 5};
    int64_t b[5] = {2, 1, 2, 3, 4};
    AsmSetToSequence(a, 5);

    for (int i = 0; i < 5; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[5] = {2, 5, 3, 4, 1};
    int64_t b[5] = {2, 1, 2, 3, 4};
    AsmSetToSequence(a, 5);

    for (int i = 0; i < 5; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
}

// // test last group size eq_1
TEST(AsmRotateInGroups, Simple) {
  {
    int k = 2;
    int64_t a[5] = {1, 2, 3, 4, 5};
    int64_t b[5] = {2, 1, 4, 3, 5};

    AsmRotateInGroups(a, 5, k);

    for (int i = 0; i < 5; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int k = 3;
    int64_t a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int64_t b[8] = {2, 3, 1, 5, 6, 4, 8, 7};

    AsmRotateInGroups(a, 8, k);

    // for (int i = 0; i < 8; i++) {
    //   std::cout << a[i] << ' ';
    // }
    for (int i = 0; i < 8; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int k = 3;
    int64_t a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int64_t b[8] = {2, 3, 1, 5, 6, 4, 8, 7};

    AsmRotateInGroups(a, 6, k);

    for (int i = 0; i < 6; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
}

TEST(AsmRemoveIfSimilar, Simple) {
  {
    int64_t a[1] = {1};
    int64_t b[1] = {1};
    int x = 1, d = 2;
    int new_size = AsmRemoveIfSimilar(a, 1, x, d);
    ASSERT_EQ(new_size, 0);
    for (int i = 0; i < new_size; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    int64_t b[9] = {-5, -4, -3, -2, -1, 0,  2,  4, 5};
    int x = 1, d = 2;
    int new_size = AsmRemoveIfSimilar(a, 11, x, d);
    ASSERT_EQ(new_size, 9);
    for (int i = 0; i < new_size; i++) {
      std::cout << a[i] << ' ';
    }
    for (int i = 0; i < new_size; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
}

TEST(AsmReplaceWithGroup, Simple) {
  {
    int64_t a[1] = {2};
    int64_t b[1] = {2};
    int siz = 1;
    int k = 2;
    AsmReplaceWithGroup(a, &siz, k);

    ASSERT_EQ(siz, 1);
    for (int i = 0; i < siz; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[2] = {3, 0};
    int64_t b[2] = {3, 3};
    int siz = 1;
    int k = 2;
    AsmReplaceWithGroup(a, &siz, k);

    ASSERT_EQ(siz, 2);
    for (int i = 0; i < siz; i++) {
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[7] = {3, 2, 1, 2, 1, 2, 0};
    int64_t b[7] = {3, 3, 2, 1, 2, 1, 2};
    int siz = 6;
    int k = 2;
    AsmReplaceWithGroup(a, &siz, k);

    ASSERT_EQ(siz, 7);
    for (int i = 0; i < siz; i++) {
      // std::cerr << i << " " << a[i] << " " << b[i] << '\n';
      ASSERT_EQ(a[i], b[i]);
    }
  }
  {
    int64_t a[9] = {1, 2, 3, 2, 4, 4, 0, 0, 0};
    int64_t b[9] = {1, 2, 3, 3, 2, 4, 4, 4, 4};
    int siz = 6;
    int k = 2;
    AsmReplaceWithGroup(a, &siz, k);

    ASSERT_EQ(siz, 9);
    for (int i = 0; i < siz; i++) {
      // std::cerr << i << " " << a[i] << " " << b[i] << '\n';
      ASSERT_EQ(a[i], b[i]);
    }
  }
}

TEST(AsmMerge, Simple) {
  {
    int64_t a[5] = {1, 2, 6, 7, 8};
    int64_t b[5] = {3, 4, 5, 9, 10};
    int64_t c[10];
    int64_t d[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    AsmMerge(a, 5, b, 5, c);

    for (int i = 0; i < 10; i++) {
      ASSERT_EQ(c[i], d[i]);
    }
  }
  {
    int64_t b[5] = {1, 2, 6, 7, 8};
    int64_t a[5] = {3, 4, 5, 9, 10};
    int64_t c[10];
    int64_t d[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    AsmMerge(a, 5, b, 5, c);

    for (int i = 0; i < 10; i++) {
      ASSERT_EQ(c[i], d[i]);
    }
  }
}

TEST(AsmModify2, Simple) {
  {
    int n = 4, m = 2;
    // swapped n, m
    int64_t** a = new int64_t*[2] {
        new int64_t[4] {0, 2, -4, 3},
        new int64_t[4] {1, -2, -3, -4}};
    int64_t** b = new int64_t*[2] {
        new int64_t[4] {0, 4, -3, 6},
        new int64_t[4] {2, -1, -2, -3}};
    AsmModify2D(a, n, m);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        // std::cerr << i << " " << j << " " << a[i][j] << " " << b[i][j] << '\n';
        ASSERT_EQ(a[i][j], b[i][j]);
      }
    }
  }
}

TEST(AsmFindSorted, Simple) {
  {
    int n = 4, m = 5;
    // swapped n, m
    int32_t** a = new int32_t*[5] {
        new int32_t[4] {1, 2, 4, 3},
        new int32_t[4] {1, 2, 3, 4},
        new int32_t[4] {5, 2, 3, 4},
        new int32_t[4] {5, 6, 8, 7},
        new int32_t[4] {5, 6, 7, 8}};

    // ok 1, 4 rows
    ASSERT_EQ(AsmFindSorted(a, n, m), 5);
  }
  {
    int n = 4, m = 5;
    // swapped n, m
    int32_t** a = new int32_t*[5] {
        new int32_t[4] {1, 2, 4, 3},
        new int32_t[4] {5, 2, 3, 4},
        new int32_t[4] {5, 6, 8, 7},
        new int32_t[4] {1, 2, 3, 4},
        new int32_t[4] {5, 6, 7, 8}};

    // ok 3, 4 rows
    ASSERT_EQ(AsmFindSorted(a, n, m), 7);
  }
}
// ---------------------------------------------------------
// TEST(AsmProduct, AsmProduct) {
//   for (int n = 1; n <= 10000; n++) {
//     int module = random()%(1ll << 30);
//     if (random()%2 == 1) {
//       module *= -1;
//     }
//     // std::cout << "n = " << n << ", module = " << module << '\n';
//     std::vector<int> numbers(n);
//     long long mult = 1;
//     for (int& number : numbers) {
//       number = random()%(1ll << 32);
//       if (random()%2 == 1) {
//         number *= -1;
//       }
//       mult *= number;
//       mult %= module;
//       if (mult < 0) {
//         mult += module;
//       }
//     }
//     int asm_mult = AsmProduct(numbers.data(), n, module);
//     ASSERT_EQ(mult, asm_mult);
//   }
// }
// ---------------------------------------------------------
// TEST(AsmSpecialSum, AsmSpecialSum) {
//   for (int64_t n = 100000; n <= 1; n++) {
//     int64_t x = 2;
//     x <<= 50;
//     x++;
//     int64_t module = random()%x;
//     // std::cout << "n = " << n << ", module = " << module << '\n';
//     std::vector<int64_t> numbers(n);
//     int64_t sum = 0;
//     for (int64_t& number : numbers) {
//       number = random()%(1ll << 63);
//       if ((number % 3 == 1) && ((number % 5) % 2 == 1)) {
//         sum += number;
//         sum %= module;
//       }
//     }
//     int asm_sum = AsmSpecialSum(numbers.data(), n, module);
//     ASSERT_EQ(sum, asm_sum);
//   }
// }
// ---------------------------------------------------------
// TEST(AsmArrayFormula, AsmArrayFormula) {
//   for (int64_t n = 100000; n <= 1; n++) {
//     int64_t x = 2;
//     x <<= 50;
//     x++;
//     int64_t module = random()%x;
//     // std::cout << "n = " << n << ", module = " << module << '\n';
//     std::vector<int64_t> numbers(n);
//     int64_t sum = 0;
//     for (int64_t& number : numbers) {
//       number = random()%(1ll << 63);
//       if ((number % 3 == 1) && ((number % 5) % 2 == 1)) {
//         sum += number;
//         sum %= module;
//       }
//     }
//     int asm_sum = AsmArrayFormula(numbers.data(), n);
//     ASSERT_EQ(sum, asm_sum);
//   }
// }
// ---------------------------------------------------------