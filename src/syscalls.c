/* To get syscall() we need to define _GNU_SOURCE
 * in modern glibc versions.
 */

/* imported from the kernel source tree */
#include "asm/unistd.h"

/* for syscall() */
#include <unistd.h>

#include "litmus.h"
#include "internal.h"

/*	Syscall stub for setting RT mode and scheduling options */

pid_t gettid(void)
{
	return syscall(__NR_gettid);
}

int set_rt_task_param(pid_t pid, struct rt_task *param)
{
	return syscall(__NR_set_rt_task_param, pid, param);
}

int get_rt_task_param(pid_t pid, struct rt_task *param)
{
	return syscall(__NR_get_rt_task_param, pid, param);
}

int sleep_next_period(void)
{
	return syscall(__NR_complete_job);
}

int od_openx(int fd, obj_type_t type, int obj_id, void *config)
{
	return syscall(__NR_od_open, fd, type, obj_id, config);
}

int od_close(int od)
{
	return syscall(__NR_od_close, od);
}

int litmus_lock(int od)
{
	return syscall(__NR_litmus_lock, od);
}

int litmus_unlock(int od)
{
	return syscall(__NR_litmus_unlock, od);
}

int get_job_no(unsigned int *job_no)
{
	struct control_page* cp = get_ctrl_page();
	if (likely(cp != NULL)) {
		*job_no = cp->job_index;
		return 0;
	} else {
		return -1;
	}
}

int wait_for_job_release(unsigned int job_no)
{
	return syscall(__NR_wait_for_job_release, job_no);
}

int wait_for_ts_release(void)
{
	return syscall(__NR_wait_for_ts_release);
}

int release_ts(lt_t *delay)
{
	return syscall(__NR_release_ts, delay);
}

int null_call(cycles_t *timestamp)
{
	return syscall(__NR_null_call, timestamp);
}

int get_current_budget(
	lt_t *expended,
	lt_t *remaining)
{
	return syscall(__NR_get_current_budget, expended, remaining);
}
