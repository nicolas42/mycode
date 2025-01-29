#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846
#define SIZEOF_MVEC 4

static const char* basis[] = { "1","e1","e2","e12" };

typedef struct {
  float mvec[SIZEOF_MVEC];
} R2;

// Constructor-like function for R2
void R2_init(R2 *r2, float f, int idx) {
  memset(r2->mvec, 0, sizeof(r2->mvec));
  if (idx >= 0 && idx < SIZEOF_MVEC) {
    r2->mvec[idx] = f;
  }
}

// Array subscript operator simulation
float R2_get(const R2 *r2, size_t idx) {
  return r2->mvec[idx];
}

void R2_set(R2 *r2, size_t idx, float value) {
  r2->mvec[idx] = value;
}

// log function for R2
void R2_log(const R2 *r2) {
  int n = 0;
  for (int i = 0; i < SIZEOF_MVEC; i++) {
    if (r2->mvec[i] != 0.0f) {
      if (n > 0) printf(" + ");
      printf("%0.7g%s", r2->mvec[i], (i == 0) ? "" : basis[i]);
      n++;
    }
  }
  if (n == 0) printf("0");
  printf("\n");
}

// Implementations of operators and functions

R2 R2_reverse(const R2 *a) {
  R2 res;
  R2_init(&res, 0, -1);  // Initialize with zeros
  res.mvec[0] = a->mvec[0];
  res.mvec[1] = a->mvec[1];
  res.mvec[2] = a->mvec[2];
  res.mvec[3] = -a->mvec[3];
  return res;
}

R2 R2_dual(const R2 *a) {
  R2 res;
  R2_init(&res, 0, -1);
  res.mvec[0] = -a->mvec[3];
  res.mvec[1] = a->mvec[2];
  res.mvec[2] = -a->mvec[1];
  res.mvec[3] = a->mvec[0];
  return res;
}

R2 R2_conjugate(const R2 *a) {
  R2 res;
  R2_init(&res, 0, -1);
  res.mvec[0] = a->mvec[0];
  res.mvec[1] = -a->mvec[1];
  res.mvec[2] = -a->mvec[2];
  res.mvec[3] = -a->mvec[3];
  return res;
}

R2 R2_involute(const R2 *a) {
  R2 res;
  R2_init(&res, 0, -1);
  res.mvec[0] = a->mvec[0];
  res.mvec[1] = -a->mvec[1];
  res.mvec[2] = -a->mvec[2];
  res.mvec[3] = a->mvec[3];
  return res;
}

R2 R2_multiply(const R2 *a, const R2 *b) {
  R2 res;
  R2_init(&res, 0, -1);
  res.mvec[0] = b->mvec[0] * a->mvec[0] + b->mvec[1] * a->mvec[1] + b->mvec[2] * a->mvec[2] - b->mvec[3] * a->mvec[3];
  res.mvec[1] = b->mvec[1] * a->mvec[0] + b->mvec[0] * a->mvec[1] - b->mvec[3] * a->mvec[2] + b->mvec[2] * a->mvec[3];
  res.mvec[2] = b->mvec[2] * a->mvec[0] + b->mvec[3] * a->mvec[1] + b->mvec[0] * a->mvec[2] - b->mvec[1] * a->mvec[3];
  res.mvec[3] = b->mvec[3] * a->mvec[0] + b->mvec[2] * a->mvec[1] - b->mvec[1] * a->mvec[2] + b->mvec[0] * a->mvec[3];
  return res;
}

// ... (Continue with other operations like R2_wedge, R2_vee, etc., similar to how R2_multiply is handled)

// Scalar operations
R2 R2_scalar_multiply(float scalar, const R2 *b) {
  R2 res;
  R2_init(&res, 0, -1);
  for (int i = 0; i < SIZEOF_MVEC; i++) {
    res.mvec[i] = scalar * b->mvec[i];
  }
  return res;
}

// norm, inorm, and normalized functions
float R2_norm(const R2 *a) {
  R2 r2_conjugate = R2_conjugate(a);
  R2 temp = R2_multiply(a, &r2_conjugate);
  return sqrt(fabs(temp.mvec[0]));
}

float R2_inorm(const R2 *a) {
  R2 dual = R2_dual(a);
  return R2_norm(&dual);
}

R2 R2_normalized(const R2 *a) {
  float norm = R2_norm(a);
  return R2_scalar_multiply(1.0f / norm, a);
}

int main(int argc, char **argv) {

  // Global R2 instances
  R2 e1 = { .mvec = {0, 1, 0, 0} };
  R2 e2 = { .mvec = {0, 0, 1, 0} };
  R2 e12 = { .mvec = {0, 0, 0, 1} };


  R2 result1 = R2_multiply(&e1, &e1);
  printf("e1*e1         : "); R2_log(&result1);
    
  printf("pss           : "); R2_log(&e12);
    
  R2 result2 = R2_multiply(&e12, &e12);
  printf("pss*pss       : "); R2_log(&result2);

  return 0;
}
