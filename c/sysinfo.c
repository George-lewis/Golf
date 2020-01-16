#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <errno.h>

int main(int argc, char** argv) {

	struct sysinfo info = {};

	int status = sysinfo(&info);

	if (status != 0) {
		printf("SYSTEM ERROR: SYSINFO() RETURNED %i\nERRNO: %i", status, errno);
	}

	printf("Status code: %i\n", status);

	printf("Errno: %i\n", errno);

	printf(" 					\n\
Uptime: %li minutes 			\n\
loads (1, 5, 15): %ld, %lu, %lu \n\
total ram: %lu 					\n\
freeram: %lu					\n\
sharedram: %lu					\n\
bufferram: %lu					\n\
totalswap: %lu					\n\
freeswap: %lu					\n\
procs: %hu						\n\
total high: %lu					\n\
free high: %lu					\n\
mem unit: %i					\n\
			", info.uptime/60, info.loads[0]/1000000, info.loads[1], info.loads[2], \
			info.totalram, info.freeram, info.sharedram, info.bufferram, \
			info.totalswap, info.freeswap, info.procs, info.totalhigh,   \
			info.freehigh, info.mem_unit);

	return 0;

}
