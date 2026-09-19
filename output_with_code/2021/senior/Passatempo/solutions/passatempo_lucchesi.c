#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELL (100)
#define MAX_C (100)

typedef struct {
  char name[3];
  int value;
} Dict;

int compar(const void *d1, const void *d2) {
  return strcmp(&(((Dict *)d1)->name[0]), &(((Dict *)d2)->name[0]));
}

int ell, c;
char A[MAX_ELL][MAX_C][3];
int s[MAX_ELL];
int t[MAX_C];

Dict dict[MAX_ELL * MAX_C];
int n_dict = 0;

int indice(char *s) {
  int k;
  for (k = 0; k < n_dict; ++k) 
    if (strcmp(s, &dict[k].name[0]) == 0) return k;
  return -1;
}

char *find_lines() {
  char new_var[3];
  int sum, n_occur, i, j, k;
  char *res = "done";
  for (i = 0; i < ell; ++i) {
      sum = 0;
      strcpy(new_var, "");
      for (j = 0; j < c; ++j) {
	k = indice(&A[i][j][0]);
	if (k >= 0) sum += dict[k].value;
	else {
	  res = "";
	  if (strcmp(new_var, "") == 0) {
	  strcpy(new_var, &A[i][j][0]);
	  n_occur = 1;
	  }
	  else if (strcmp(new_var, &A[i][j][0]) == 0)
	    ++n_occur;
	  else {
	    strcpy(new_var, "");
	    break;
	  }
	}
      }
      if (strcmp(new_var, "") != 0) break;
  }
  if (strcmp(res, "done") == 0) return res;
  if (strcmp(new_var, "") == 0) return res;
  strcpy(&dict[n_dict].name[0], new_var);
  dict[n_dict].value = (s[i] - sum) / n_occur;
  ++n_dict;
  return res;
}
  
char *find_columns() {
  char new_var[3];
  int sum, n_occur, i, j, k;
  char *res = "done";
  for (j = 0; j < c; ++j) {
      sum = 0;
      strcpy(new_var, "");
      for (i = 0; i < ell; ++i) {
	k = indice(&A[i][j][0]);
	if (k >= 0) sum += dict[k].value;
	else {
	  res = "";
	  if (strcmp(new_var, "") == 0) {
	  strcpy(new_var, &A[i][j][0]);
	  n_occur = 1;
	  }
	  else if (strcmp(new_var, &A[i][j][0]) == 0)
	    ++n_occur;
	  else {
	    strcpy(new_var, "");
	    break;
	  }
	}
      }
      if (strcmp(new_var, "") != 0) break;
  }
  if (strcmp(res, "done") == 0) return res;
  if (strcmp(new_var, "") == 0) return res;
  strcpy(&dict[n_dict].name[0], new_var);
  dict[n_dict].value = (t[j] - sum) / n_occur;
  ++n_dict;
  /* for (i = 0; i < n_dict; ++i) */
  /*   fprintf(stderr, "%s %d\n", &dict[i].name[0], dict[i].value); */
  return res;
}


int main(int argc, char *noargs[]) {
  int i, j;
  char *res;
  scanf("%d %d", &ell, &c);
  for (i = 0; i < ell; ++i) {
    for (j = 0; j < c; ++j)
      scanf("%s", &A[i][j][0]);
    scanf("%d", &s[i]);
  }
  for (j = 0; j < c; ++j)
    scanf ("%d", &t[j]);
  /* for (i = 0; i < ell; ++i) { */
  /*   for (j = 0; j < c; ++j) */
  /*     fprintf(stderr, " %s", A[i][j]); */
  /*   fprintf (stderr, " %d\n", s[i]); */
  /* } */
  /* for (j = 0; j < c; ++j) */
  /*   fprintf(stderr, " %d", t[j]); */
  /* fprintf(stderr, "\n"); */
  for (;;) {
    res = find_lines();
    res = find_columns();
    if (strcmp(res, "done") == 0) break;
  }

  qsort(dict, n_dict, sizeof(Dict), compar);

  for (i = 0; i < n_dict; ++i)
    printf("%s %d\n", &dict[i].name[0], dict[i].value);
  return 0;
}
