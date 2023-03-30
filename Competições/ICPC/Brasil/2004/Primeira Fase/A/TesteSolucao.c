/*******************************************
 *  check solution for the problem         *
 *  Crossword with no words                *
 *  ICPC South American Regional 2004      *
 *  R. Anido                               *
 *                                         *
 * usage:                                  *
 *   ./check_crossword compet_sol cross.in *
 *                                         *
 *******************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAXLINE 2000
#define MAXCOL 2000
#define odd(x) (x & 1)

int i, j, n_middle, n_first,
  n_lin, n_col, n_words,
  words[MAXCOL],
  w, nw, half, up,
  test, possible;
int num_words, col, lin, black_col[MAXCOL+1], cols_used[MAXCOL+1], countsize[MAXCOL+1];
FILE *compet_sol;


void error (char *msg)
{
  printf ("%s\n", msg);
  exit (-1);
}

int main(int argc, char * argv[])
{
  int c_test, n_read;
  char c;

  test = 0;
  compet_sol = fopen(argv[1],"rt");
  freopen(argv[2], "rt", stdin);
  if (argc != 3) {
    printf("usage:\n%s compet_sol_file problem_input_file\n", argv[0]);
    exit(-1);
  }
  while (scanf("%d %d %d", &n_lin, &n_col, &n_words)==3 && n_lin != 0) {
    printf ("Test %d: ", ++test);
    memset(words, 0, sizeof(words));
    memset (countsize, 0, sizeof (countsize));
    memset (black_col, 0, sizeof (black_col));
    memset (cols_used, 0, sizeof (cols_used));
    n_read = fscanf(compet_sol, "%c%d", &c, &c_test);
    if (n_read != 2 || c != '#' || c_test != test)
      error("wrong test number");
    n_middle = 0; n_first = 0; up = 1;
    if (odd(n_lin))
      half = (n_lin+1) / 2;
    else
      half = 0;
    nw = 0;
    for (i=0; i<n_words; i++) {
      scanf("%d", &w);
      words[w]++;
      countsize[w]++;
      if (w == n_lin-1)
	n_first++;
      else if (w + 1 == half)
	n_middle++; /* black square is in the middle of column, n_col is odd */
      else
	nw++;
    }
    if (odd(nw) || odd(n_middle) ||
	(nw/2 + n_middle/2 + n_first) != n_col ||
	n_middle/2 > (n_col+1)/2) {
      goto impossible;
    }
    words[0] = n_first; /* black square will be on line 1 or n_col */
    possible = TRUE;
    for (i=0; i<n_lin/2; i++) {
      if (words[i] != words[n_lin-i-1]) {
	possible = FALSE; /* words do not fit puzzle N x M */
	break;
      }
    }
    if (!possible) {
impossible:
      n_read = fscanf(compet_sol, "%d\n", &i);
      if (n_read != 1 || i != 0)
	error("should be impossible");
      else
	printf("OK\n");
    }
    else {
      num_words = 0;
      for (i=0; i < n_col; i++) {
	n_read = fscanf(compet_sol, "%d %d\n", &lin, &col);
	if (n_read != 2 || lin < 1 || lin > n_lin || col < 1 || col > n_col)
	  error("wrong values for column/line number");
	if (cols_used[col] != 0)
	  error("wrong value for column number");
	cols_used[col]++;
	black_col[col] = lin;
	if (lin == 1 || lin == n_lin) {
	  countsize[n_lin-1]--;
	  num_words++;
	}
	else {
	  countsize[lin-1]--;
	  countsize[n_lin-lin]--;
	  num_words += 2;
	}
      }
      if (num_words != n_words)
	error("wrong number of words");
      for (i = 1; i <= n_col; i++)
	if (countsize[i] != 0) {
	  printf("countsize[i]=%d, i=%d\n", countsize[i], i);
	  error("wrong word sizes");
	}
      for (i = 1; i < n_col; i++)
	if (black_col[i] != 0 && black_col[i] == black_col[i+1])
	  error("black squares are neighbors");
      for (i = 1; i <= n_col; i++)
	if (cols_used[i] != 1)
	  error("missing column");
      printf("OK\n");
    }
  }        
  return 0;
}