#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>



int main(int argc, char ** argv)
{
	DIR *dp;
	struct dirent *dirp;
	struct passwd *p;
	struct group *g;
	struct tm *time;
	struct stat sb;
	char buf[128];
	char permissions[11];

	if(argc != 3)
	{
		perror(" Not enough arguments\n");
		exit(-1);
	}// end if

	if (stat(argv[2], &sb) == -1) {
		perror("stat");
		exit(-1);
    	}
	if( (dp = opendir(argv[2])) == NULL && !S_ISREG(sb.st_mode))
	{
		perror("Could not open directory\n");
	}	
	if(S_ISREG(sb.st_mode))
	{
		permissions[0] = '-';
		permissions[1] = ((sb.st_mode & S_IRUSR)? 'r' : '-');
		permissions[2] = ((sb.st_mode & S_IWUSR)? 'w' : '-');
		permissions[3] = ((sb.st_mode & S_IXUSR)? 'x' : '-');
		permissions[4] = ((sb.st_mode & S_IRGRP)? 'r' : '-');
		permissions[5] = ((sb.st_mode & S_IWGRP)? 'w' : '-');
		permissions[6] = ((sb.st_mode & S_IXGRP)? 'x' : '-');
		permissions[7] = ((sb.st_mode & S_IROTH)? 'r' : '-');
		permissions[8] = ((sb.st_mode & S_IWOTH)? 'w' : '-');
		permissions[9] = ((sb.st_mode & S_IXOTH)? 'x' : '-');
		permissions[10] = '\0';
		fprintf(stdout, "%s ", permissions);
		if((p = getpwuid(sb.st_uid)) != NULL)
		{
			fprintf(stdout, "%s ", p->pw_name);
		}
		else
		{
			fprintf(stdout, "%d ", (int)sb.st_uid);
		}
		if((g = getgrgid(sb.st_gid)) != NULL)
		{
			fprintf(stdout, "%s ", g->gr_name);
		}
		else
		{
			fprintf(stdout, "%d ", (int)sb.st_gid);
		}
		fprintf(stdout, "%d ", (int)sb.st_size);
		if((time = localtime(&sb.st_mtime))!= NULL)
		{
			if(strftime(buf, 128, "%b  %d  %H:%M", time) == 0)
			{
				perror("strftime");
				exit(-1);
			}
			fprintf(stdout, "%s", buf);
		}
	
		fprintf(stdout, "\t%s\n", argv[2]);
	}
	else
	{
		while( (dirp = readdir(dp)) != NULL)
		{	
			if(strcmp(dirp->d_name, ".")!=0 && strcmp(dirp->d_name, "..")!=0)
			{
				permissions[0] = ((S_ISDIR(sb.st_mode))? 'd' : '-');
				permissions[1] = ((sb.st_mode & S_IRUSR)? 'r' : '-');
				permissions[2] = ((sb.st_mode & S_IWUSR)? 'w' : '-');
				permissions[3] = ((sb.st_mode & S_IXUSR)? 'x' : '-');
				permissions[4] = ((sb.st_mode & S_IRGRP)? 'r' : '-');
				permissions[5] = ((sb.st_mode & S_IWGRP)? 'w' : '-');
				permissions[6] = ((sb.st_mode & S_IXGRP)? 'x' : '-');
				permissions[7] = ((sb.st_mode & S_IROTH)? 'r' : '-');
				permissions[8] = ((sb.st_mode & S_IWOTH)? 'w' : '-');
				permissions[9] = ((sb.st_mode & S_IXOTH)? 'x' : '-');
				permissions[10] = '\0';
				fprintf(stdout, "%s ", permissions);
				if((p = getpwuid(sb.st_uid)) != NULL)
				{
					fprintf(stdout, "%s ", p->pw_name);
				}
				else
				{
					fprintf(stdout, "%d ", (int)sb.st_uid);
				}
				if((g = getgrgid(sb.st_gid)) != NULL)
				{
					fprintf(stdout, "%s ", g->gr_name);
				}
				else
				{
					fprintf(stdout, "%d ", (int)sb.st_gid);
				}
				fprintf(stdout, "%d ", (int)sb.st_size);
				if((time = localtime(&sb.st_mtime))!= NULL)
				{
					if(strftime(buf, 128, "%b  %d  %H:%M", time) == 0)
					{
						perror("strftime");
						exit(-1);
					}
					fprintf(stdout, "%s", buf);
				}
		
				fprintf(stdout, "\t%s\n", dirp->d_name);
			}
		
		}
	}
	
	return 0;
}// end main
