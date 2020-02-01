

void InitAddrinfo(const char *node, const char *service, int ai_family, int ai_socktype, int ai_flags, struct addrinfo **serv_info);

/* frees serv_info, returns -1 or error */
int TCPServerBindSocket(struct addrinfo **serv_info);

/* frees serv_info, returns -1 or error */
int TCPClientConnectSocket(struct addrinfo **serv_info);

void *GetAddr(struct sockaddr *sa);