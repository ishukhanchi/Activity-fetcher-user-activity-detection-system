#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<locale.h>
#include<stdarg.h>
#include<time.h>
#include<dirent.h>
#include<unistd.h>
#include<utmp.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/param.h>
#include<linux/major.h>
#include<ctype.h>

#define BUF_SIZE 1000



	char decide,c[70],proc[70],progchoice =NULL,file1[80],file2[80];
	FILE *fp;
	time_t real_time;
	struct tm *tmp;
	time_t real_time;
	char out_buf[128];
	int pos = 0, updays = 0, uphours = 0, upminutes = 0, num_users = 0,i;
	double uptime_secs, idle_secs, av1, av5, av15;
	struct utmp * utmpp;
	
int main(int ac, char* av[]) 
{
	char* comm = (char*)malloc(sizeof("ps aux > "));
	char* comm1 = (char*)malloc(sizeof("ps aux | grep "));
	printf("Enter your choice to choose from the available modules\n 1.Process List(p) \n 2.timespot(c) \n 3.File List(l) \n 4.Running time(u)\n 5.log records(o)\n ");
	scanf(" %c", &progchoice);

	if(progchoice == 'p')	{ // 1st choice
		printf("If you want to save the process list then press s(save)\nor if the file already exists you can display it by pressing d(display)\n");
	scanf(" %c", &decide);

	if(decide == 's')
	{
		printf("Give the complete Directory you want to save the process list log file in \n");
		scanf("%s", c);
		
		fp = fopen(c , "r");
		if(fp == NULL)
		{
		*comm = *(char*)"p";
		strcat(comm,(char*)"s aux > ");
		strcat(comm,c);
		system(comm);
		printf("File is created\n");
		}
		else
			printf("The file already exists \n");
	}

	else if(decide == 'd')
	{
		printf("Choose to display for a specific  active process(p) or the whole file(f) of active processess\n");
		scanf(" %c", &decide);
		
		if(decide == 'f')
			{
			*comm = *(char*)"p";
			strcat(comm,(char*)"s aux");
			system(comm);
			}
		else if(decide == 'p')
			{
				printf("Enter the process name \n");
				scanf("%s" , proc);
				*comm = *(char*)"p"; //two processes come instead of one(redundancy)
				strcat(comm,(char*)"s aux | grep ");
				strcat(comm,proc);
				system(comm);
			}
	}

	}
	
	else if(progchoice == 'c') { // 2nd choice

		char* my_strftime(const char *format, struct tm *tmp) {
  			static char buf[BUF_SIZE];
			size_t s;
		
  			if(tmp == NULL) 
    			return NULL;
		
			s = strftime(buf, BUF_SIZE, (format != NULL) ? format: "%A %B %d %I:%M:%S %p %Y %Z", tmp);

			return (s == 0) ? NULL : buf;
		}
	
		void err_exit(const char *format, ...) {
			va_list args;
			va_start(args, format);
			vfprintf(stderr, format, args);
			va_end(args);
		
			exit(EXIT_FAILURE);
		}	
	
			/*if(setlocale(LC_ALL, "") == NULL) {
				err_exit("Error on setlocale %s\n", strerror(errno));
				}
	
				real_time = time(NULL);
			if((tmp = localtime(&real_time)) == NULL) {
				err_exit("Error on localtime, %s\n", strerror(errno));
				}*/
			real_time = time(NULL);
			tmp = localtime(&real_time);
	
			printf("ctime() is %s\nasctime() is %s\n", ctime(&real_time), asctime(tmp));
			printf("strftime() is %s\n", my_strftime(NULL, tmp));
			exit(EXIT_SUCCESS);
		}
	
	else if(progchoice == 'l') { // 3rd choice
	
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				printf("%s\n", dir->d_name);
			}
		closedir(d);
		}
	}
	
	else if(progchoice == 'u') { // 4th choice
		void err_exit(const char *format, ...) {
			va_list args;
			va_start(args, format);
			vfprintf(stderr, format, args);
			va_end(args);

			exit(EXIT_FAILURE);
		}

		void uptime(double *uptime_secs, double *idle_secs) {
			size_t num_bytes_read;
			int fd;
			char read_buf[128];

			fd = open("/proc/uptime", O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);

			if(fd != -1) {
				if((num_bytes_read = read(fd, read_buf, 128)) != -1) {
					if(sscanf(read_buf, "%lf %lf", &(*uptime_secs), &(*idle_secs)) == 2) {
						close(fd);
					} 
					else {
						err_exit("Erron on sscanf, %s, line no %d\n", strerror(errno), __LINE__);
					}
				} 
				else {
					err_exit("Erron on read, %s %d\n", strerror(errno), __LINE__);
				}
			} 
			else {
				err_exit("Error on open, %s %d\n", strerror(errno), __LINE__);
			}
		}

		void loadavg(double *av1, double *av5, double *av15) {
			size_t num_bytes_read;
			int fd;
			char read_buf[128];

			fd = open("/proc/loadavg", O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
			if(fd != -1) {
				if((num_bytes_read = read(fd, read_buf, 128)) != -1) {
					if(sscanf(read_buf, "%lf %lf %lf", &(*av1), &(*av5), &(*av15)) == 3) {
					close(fd);
					} 
					else {
						err_exit("Erron on sscanf, %s %d\n", strerror(errno), __LINE__);
					}
				} 
				else {
					err_exit("Erron on read, %s %d\n", strerror(errno), __LINE__);
				}
			} 	
			else {
				err_exit("Error on open, %s %d\n", strerror(errno), __LINE__);
			}
		}

		/* print real time to out_buf */
			
		tmp = localtime(&real_time);
		pos = sprintf(out_buf, " %02d:%02d:%02d ", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
		strcat(out_buf, ";up time: ");
		pos += 3;
		
		/* print uptime, idle time to out_buf */
		uptime(&uptime_secs, &idle_secs);
		updays = (int) uptime_secs / (60 * 60 * 24);
		if(updays) {
			pos += sprintf(out_buf + pos, "%d day%s, ", updays, (updays != 1) ? "s" : "");
		}
	
		upminutes = (int) uptime_secs / 60;
		uphours = (int) upminutes/ 60;
		uphours = (int) uphours % 24;
		upminutes = upminutes % 60;
	
		if(uphours) {
			pos += sprintf(out_buf + pos, "%2d:%2d, ", uphours, upminutes);
		} 
		else {
			pos += sprintf(out_buf + pos, "%d min, ", upminutes);
		}
	
		 /*print load avg to out_buf */
		loadavg(&av1, &av5, &av15);
		sprintf(out_buf + pos, "load average: %0.2f, %0.2f, %0.2f", av1, av5, av15);
		printf("%s\n", out_buf);
	
		exit(EXIT_SUCCESS);		
	}

	else if(progchoice == 'o') { // 5th choice
		
		FILE *infile; 
		infile = fopen ("/var/log/apport.log", "r"); // Open log file for reading 
		fseek(infile,0L,SEEK_END); // find the file size
		int  sz=ftell(infile);
		char* buffer =(char *) malloc(sz* sizeof(char)); // dynamically allocates storage in a bufffer
		rewind(infile);
		if (infile == NULL) 
		{ 
			fprintf(stderr, "\nError opening file\n"); 
			exit (1); 
		} 
		fread(buffer,sz , 1, infile); // read file contents till end of file 
		for(i=0;i<sz;i++)
		{
			printf ("%c",buffer[i]); 
		}
  
		// close file 
		fclose (infile); 
	}
	
	return 0;	
}	

