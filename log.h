#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/* __FUNCTION__ is a gcc extension */
#ifndef HAVE__FUNCTION__
# define __FUNCTION__ "UNKNOWN_FUNC"
#endif

#ifndef NDEBUG
# define logit(format, ...) \
	internal_logit (__FILE__, __LINE__, __FUNCTION__, format, \
	## __VA_ARGS__)
#else
# define logit fake_logit
#endif
void internal_logit (const char *file, const int line, const char *function,
		const char *format, ...)
	__attribute__ ((format (printf, 4, 5)));
void fake_logit (const char *format, ...);
void log_init_stream (FILE *f);
void log_close ();

#endif
