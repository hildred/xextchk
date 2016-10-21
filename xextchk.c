/*
	based on the execlent answer by deamentiaemundi
	http://stackoverflow.com/a/40116696?noredirect=1
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <libintl.h>
#include <locale.h>
#define _(string) gettext (string)

bool verbose	= false;
bool quiet	= false;
bool list	= false;

static int compare(const void *a, const void *b)
{
	return strcmp(*(char **) a, *(char **) b);
}

int extension_info(Display * dpy, char* feature)
{
	int n = 0, i;
	char **extlist = XListExtensions(dpy, &n);
	int result=EXIT_FAILURE;

	if (verbose) printf(_("number of extensions: %d\n"), n);
	if (extlist) {
		if (list) qsort(extlist, n, sizeof(char *), compare);
		for (i = 0; i < n; i++) {
			if (list) printf("%s\n", extlist[i]);
			if (feature && 0==strcmp(feature, extlist[i])) {
				if (!quiet) printf(_("Extension '%s' found.\n"), feature);
				if (list) {
					result=EXIT_SUCCESS;
				} else {
					return EXIT_SUCCESS;
				}
			}
		}
		if ((!quiet) && feature && (EXIT_FAILURE==result)) printf(_("Extension '%s' not found.\n"), feature);
	} else {
		if (!quiet) printf(_("No extensions found.\n"));
	}
	// TODO: it might not be a good idea to free extlist, check
	return result;
}

int main(int argc, char **argv)
{
	Display *dpy;
	char *displayname = NULL;
	int opt, result;
	char *name = NULL;

	while ((opt = getopt(argc, argv, "vql")) != -1) {
		switch (opt) {
			case 'v':	verbose=true;	break;
			case 'q':	quiet=true;	break;
			case 'l':	list=true;	break;
			default: /* '?' */
				fprintf(stderr, _("Usage: %s [-vql] name\n"), argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if (optind < argc) {
		name=argv[optind];
	}else if(list){
	}else{
		fprintf(stderr, _("%s: Insuficent arguments\n"), argv[0]);
		exit(EXIT_FAILURE);
	}
	dpy = XOpenDisplay(displayname);
	if (!dpy) {
		if (!quiet) fprintf(stderr, _("%s: Unable to open display \"%s\".\n"), argv[0], XDisplayName(displayname));
		exit(EXIT_FAILURE);
	}

	result=extension_info(dpy,name);

	XCloseDisplay(dpy);
	exit(result);
}
