#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <gtest/gtest.h>
#include <CL/cl.hpp>
#include <vector>

void matrices_sum(const std::vector<int> & a, const std::vector<int> & b, std::vector<int> & c, int m, int n){
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < m; ++j){
      c[i*m + j] = a[i * m + j] + b[i * m + j];
    }
  }
}

TEST(matricesSumTest, Basic){
  const int n = 3;
  const int m = 3;
  std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> b = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> c(n * m);

  matrices_sum(a, b, c, m, n);
  std::vector<int> ans = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  ASSERT_EQ(c, ans);
}

TEST(matricesSumTest, Zero){
  const int n = 2;
  const int m = 2;
  std::vector<int> a = {0, 0, 0, 0};
  std::vector<int> b = {0, 0, 0, 0};
  std::vector<int> c(n * m);

  matrices_sum(a, b, c, m, n);
  std::vector<int> ans = {0, 0, 0, 0};
  ASSERT_EQ(c, ans);
}

TEST(matricesSumTest, Negative){
  const int n = 3;
  const int m = 4;
  std::vector<int> a = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};
  std::vector<int> b = {-13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2};
  std::vector<int> c (n * m);

  matrices_sum(a, b, c, m, n);
  std::vector<int> ans(n*m, -14);
  ASSERT_EQ(c, ans);
}

TEST(matricesSumTest, Negative1){
  const int n = 3;
  const int m = 4;
  std::vector<int> a = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};
  std::vector<int> b = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
  std::vector<int> c (n * m);

  matrices_sum(a, b, c, m, n);
  std::vector<int> ans = {12, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10};
  ASSERT_EQ(c, ans);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
