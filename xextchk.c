/*
   based on the execlent answer by deamentiaemundi
   http://stackoverflow.com/a/40116696?noredirect=1
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *a, const void *b)
{
  return strcmp(*(char **) a, *(char **) b);
}

static void print_extension_info(Display * dpy)
{
  int n = 0, i;
  char **extlist = XListExtensions(dpy, &n);


  printf("number of extensions:    %d\n", n);
  if (extlist) {
    qsort(extlist, n, sizeof(char *), compare);
    for (i = 0; i < n; i++) {

      printf("    %s\n", extlist[i]);

    }
  }
  // TODO: it might not be a good idea to free extlist, check
}

int main()
{
  Display *dpy;
  char *displayname = NULL;

  dpy = XOpenDisplay(displayname);
  if (!dpy) {
    fprintf(stderr, "Unable to open display \"%s\".\n",
            XDisplayName(displayname));
    exit(EXIT_FAILURE);
  }

  print_extension_info(dpy);

  XCloseDisplay(dpy);
  exit(EXIT_SUCCESS);
}
