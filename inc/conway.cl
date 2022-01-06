int n(int p, int m, int n) {
  if (p - m < 0) {
    return (m * n) + p - m - 1;
  }
  return p - m;
}

int e(int p, int m, int n) {
  if (p + 1 >= m * n) {
    return 0;
  }

  return p + 1;
}

int s(int p, int m, int n) {
  if (p + m > (m * n)) {
    return p + m - (m * n) - 1;
  }
  return p + m;
}

int m(int p, int m, int n) {
  if (p - 1 < 0) {
    return m * n - 1;
  }
  return p - 1;
}

int ne(int p, int m, int n) {
  if (p - m + 1 < 0) {
    return (m * n) + p - m;
  }

  return p - m + 1;
}

int nw(int p, int m, int n) {
  if (p - m - 1 < 0) {
    return (m * n) + p - m - 2;
  }

  return p - m - 1;
}

int se(int p, int m, int n) {
  if (p + m + 1 > m * n) {
    return p + m + 1 - (m * n);
  }
  return p + m + 1;
}

int sw(int p, int m, int n) {
  if (p + m - 1 > m * n) {
    return p + m - 1 - (m * n);
  }

  return p + m - 1;
}

__kernel void conway(__global const uchar *inputCells, __global const int *m, __global const int *n, __global uchar *outputCells) {
  int i = get_global_id(0);
  int neighbors = inputCells[n(i, m, n)] + inputCells[e(i, m, n)] + inputCells[s(i, m, n)] + inputCells[w(i, m, n)]
                + inputCells[ne(i, m, n)] + inputCells[nw(i, m, n)] + inputCells[se(i, m, n)] + inputCells[sw(i, m, n)];

  if (inputCells[i] == 1) {
    if (neighbors < 2 || neighbors > 3) {
      outputCells[i] = 0;
    }
  } else {
    if (neighbors == 3) {
      outputCells[i] = 1;
    }
  }
}
