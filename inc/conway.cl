R"(int north(int p, int m, int n) {
  if (p - m < 0) {
    return (m * n) + p - m;
  }
  return p - m;
}

int east(int p, int m, int n) {
  if (p + 1 % m == 0) {
    return p + 1 - m;
  }
  return p + 1;
}

int south(int p, int m, int n) {
  if (p + m >= (m * n)) {
    return p + m - (m * n);
  }
  return p + m;
}

int west(int p, int m, int n) {
  if (p - 1 % m == m - 1) {
    return p - 1 + m;
  }
  return p - 1;
}

int northeast(int p, int m, int n) {
  return north(east(p, m, n), m, n);
}

int northwest(int p, int m, int n) {
  return north(west(p, m, n), m, n);
}

int southeast(int p, int m, int n) {
  return south(east(p, m, n), m, n);
}

int southwest(int p, int m, int n) {
  return south(west(p, m, n), m, n);
}

__kernel void process(__global const uchar *inputCells, __global const int *m, __global const int *n, __global uchar *outputCells) {
  int i = get_global_id(0);
  int neighbors = inputCells[north(i, m, n)] + inputCells[east(i, m, n)] + inputCells[south(i, m, n)] + inputCells[west(i, m, n)]
                + inputCells[northeast(i, m, n)] + inputCells[northwest(i, m, n)] + inputCells[southeast(i, m, n)]
                + inputCells[southwest(i, m, n)];

  if (inputCells[i] == 1) {
    if (neighbors < 2 || neighbors > 3) {
      outputCells[i] = 0;
    } else {
      outputCells[i] = 1;  
    }
  } else {
    if (neighbors == 3) {
      outputCells[i] = 1;
    } else {
      outputCells[i] = 0;
    }
  }
}
)"
