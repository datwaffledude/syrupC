#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define size 2048

// This is syrup, made by datwaffledude for my distro wafflenux based on the LFS books.
// No generative AI was used in the making of this program.
// Without further ado:

// This is the function for handling installing.
struct Package {
	char name[size];
	char desc[size];
	char version[size];
	char architecture[size];
	char website[size];
	char install[size];
	char remove[size];
};

struct Package pkg;

// This function, like the name may suggest, prepares the package. It decompresses it, gets each line from the info, separates it, and stores the result in the pkg struct. Is also the longest function in syrup, and it took genuinely an entire day :/ I'm probably just stupid but this was hard.
int preparePackage(char *pkgname) {

	// Checking if package exists.
	char testIfPackageExistsString[size];
	snprintf(testIfPackageExistsString, sizeof(testIfPackageExistsString), "%s.tar.xz", pkgname);
	FILE *testIfPackageExists = fopen(testIfPackageExistsString, "r");
	if (testIfPackageExists == NULL) {
		printf("The package %s doesn't exist.\n", pkgname);
		return 0;
	};

	// Extracting the package
	char untarcmd[size];
	snprintf(untarcmd, sizeof(untarcmd), "tar -xf ./%s.tar.xz", pkgname);
	system(untarcmd);
	// Variables for getting the lines out of the package file
	char line1[size];
	char line2[size];
	char line3[size];
	char line4[size];
	char line5[size];
	char line6[size];
	char line7[size];
	
	// Opening the file
	char openRightFile[size];
	snprintf(openRightFile, sizeof(openRightFile), "%s/info", pkgname);
	FILE *pkgfile = fopen(openRightFile, "r");

	if (pkgfile == NULL) {
		perror("fopen");
	};
	
	// Extracting the lines to each variable and closing the file
	fgets(line1, sizeof(line1), pkgfile);
	fgets(line2, sizeof(line2), pkgfile);
	fgets(line3, sizeof(line3), pkgfile);
	fgets(line4, sizeof(line4), pkgfile);
	fgets(line5, sizeof(line5), pkgfile);
	fgets(line6, sizeof(line6), pkgfile);
	fgets(line7, sizeof(line7), pkgfile);
	fclose(pkgfile);
	
	// Defining delimiter and making new variables to separate (strsep uses pointer to a pointer)
	char *delimiter = "=";
	char *line1sep = line1;
	char *line2sep = line2;
	char *line3sep = line3;
	char *line4sep = line4;
	char *line5sep = line5;
	char *line6sep = line6;
	char *line7sep = line7;

	// Variables for separated strings
	char *line1token;
	char *line2token;
	char *line3token;
	char *line4token;
	char *line5token;
	char *line6token;
	char *line7token;

	// These while loops separate the string, leaving lineXtoken with the part after the "=" (the delimiter)
	while (line1sep != NULL) {
		line1token = strsep(&line1sep, delimiter);
	}

	while (line2sep != NULL) {
		line2token = strsep(&line2sep, delimiter);
	}

	while (line3sep != NULL) {
		line3token = strsep(&line3sep, delimiter);
	}

	while (line4sep != NULL) {
		line4token = strsep(&line4sep, delimiter);
	}

	while (line5sep != NULL) {
		line5token = strsep(&line5sep, delimiter);
	}

	while (line6sep != NULL) {
		line6token = strsep(&line6sep, delimiter);
	};

	while (line7sep != NULL) {
		line7token = strsep(&line7sep, delimiter);
	};
	
	// Filling out struct for organization.
	strcpy(pkg.name, line1token);
	strcpy(pkg.desc, line2token);
	strcpy(pkg.version, line3token);
	strcpy(pkg.architecture, line4token);
	strcpy(pkg.website, line5token);
	strcpy(pkg.install, line6token);
	strcpy(pkg.remove, line7token);

};

// This installs the package using the file defined in the pkg info in install=. Installing works by having the package info point to a shell script, and the location of that shell script gets passed to system, which then runs it and installs the package.
void installPkg(char *installPackageName) {
	char packageInstallLine[size];
	snprintf(packageInstallLine, sizeof(packageInstallLine), "./%s/%s", installPackageName, pkg.install);
	system(packageInstallLine);
};

// This removes the package, works similarly to installing a package.
void removePkg(char *removePackageName) {
	char packageRemoveLine[size];
	snprintf(packageRemoveLine, sizeof(packageRemoveLine), "./%s/%s", removePackageName, pkg.remove);
	system(packageRemoveLine);
};

// Main function, argc is how many arguments the program took, and argv is an array containing the values of those arguments.
int main(int argc, char *argv[]) {
	
	// Makes it so there need to be at least 2 additional arguments to syrup (example: "syrup install firefox" is valid, "syrup install" isn't.)
	if (argc < 3) {
		printf("Usage: {install|remove|info}");
		return 0;
	};
	
	// Makes it so the value of the first argument after syrup (example: "install") is stored in a variable called action
	char *action = argv[1];
	// Makes it so the value of the second argument after syrup (example: "firefox") is stored in a variable called packag
	char *packag = argv[2];
	
	// This part matches the action to a valid action, if it can't, then it prints out an error, containg the usage.
	
	// Trying to match install
	if (strcmp(action, "install") == 0) {

		// Preparing package
		if (preparePackage(packag) == 0) {
			return 0;
		};

		// Giving package info before installing
		printf("Package information:\n");
		printf("Name: %s\n", pkg.name);
		printf("Description: %s\n", pkg.desc);
		printf("Version: %s\n", pkg.version);
		printf("Target architecture: %s\n", pkg.architecture);
		printf("Website: %s\n", pkg.website);

		// Asking! Consent is important :D
		char installAnswer[size] = "n";
		printf("Are you sure you want to install this package? [y/N] ");
		scanf("%s", &installAnswer);
		if (strcmp(installAnswer, "n") == 0) {
			printf("Cancelled package installation.\n");
			return 0;
		};

		// Finally, installing.
		installPkg(packag);
	
	// Trying to match remove
	} else if (strcmp(action, "remove") == 0) {
		// Preparing package
		if (preparePackage(packag) == 0) {
			return 0;
		};
		
		// Giving package info before removing, in case you find something interesting.
		printf("Package information:\n");
		printf("Name: %s\n", pkg.name);
		printf("Description: %s\n", pkg.desc);
		printf("Version: %s\n", pkg.version);
		printf("Target architecture: %s\n", pkg.architecture);
		printf("Website: %s\n", pkg.website);

		// Once again, consent is always important :-)
		char removeAnswer[size] = "n";
		printf("Are you sure you want to remove this package? [y/N] ");
		scanf("%s", &removeAnswer);
		if (strcmp(removeAnswer, "n") == 0) {
			printf("Cancelled package removal.\n");
			return 0;
		};

		// Actually removing the package
		removePkg(packag);

	// Trrying to match info
	} else if (strcmp(action, "info") == 0) {
		if (preparePackage(packag) == 0) {
			return 0;
		};
		printf("Name: %s\n", pkg.name);
		printf("Description: %s\n", pkg.desc);
		printf("Version: %s\n", pkg.version);
		printf("Target architecture: %s\n", pkg.architecture);
		printf("Website: %s\n", pkg.website);

	// Couldn't match to anything.
	} else {
		printf("Invalid argument. Valid arguments are: {install|remove}");
	};

};
