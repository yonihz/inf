#ifndef _WD_THREAD_H_
#define _WD_THREAD_H_

void *WDThread(void *uargv);

int CreateWD(void *uargv);

int ReviveWDIfDead(void *uargv);

#endif /* _WD_THREAD_H_ */