#ifndef _WD_THREAD_H_
#define _WD_THREAD_H_

int WDThread(const char **uargv);

int CreateWD(const char **uargv);

int ReviveWDIfDead(const char **uargv);

#endif /* _WD_THREAD_H_ */