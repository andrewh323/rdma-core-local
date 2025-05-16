

// ================= Functions I may need =========================

// RDMA or RVMA sockets take on the form of File Descriptors
// Therefore, sockets must read, write, open, and close
// Socket Operations: rread, rwrite, rsend, rrecv, rconnect, raccept, rbind, rlisten, and rsocket


// Calls write from preload.c, which performs preload initialization and calls rwrite (from rsocket.c),
// which performs rsend
static void write_all(int fd, const void *msg, size_t len)
{
	// FIXME: if fd is a socket this really needs to handle EINTR and other conditions.
	ssize_t __attribute__((unused)) rc = write(fd, msg, len);
	assert(rc == len);
}

// Follows similar structure as write_all, calling read from preload.c and rrecv from rsocket.c
static void read_all(int fd, void *msg, size_t len)
{
	// FIXME: if fd is a socket this really needs to handle EINTR and other conditions.
	ssize_t __attribute__((unused)) rc = read(fd, msg, len);
	assert(rc == len);
}

// Inserts a queue pair into an rsocket linked list
static void ds_insert_qp(struct rsocket *rs, struct ds_qp *qp)
{
	if (!rs->qp_list)
		dlist_init(&qp->list);
	else
		dlist_insert_head(&qp->list, &rs->qp_list->list);
	rs->qp_list = qp;
}

// Removes a queue pair from an rsocket linked list
static void ds_remove_qp(struct rsocket *rs, struct ds_qp *qp)
{
	if (qp->list.next != &qp->list) {
		rs->qp_list = ds_next_qp(qp);
		dlist_remove(&qp->list);
	} else {
		rs->qp_list = NULL;
	}
}

// Binds the socket to the address specified by addr
int rbind(int socket, const struct sockaddr *addr, socklen_t addrlen)

// Listens for incoming connection requests on the socket
int rlisten(int socket, int backlog)

// This is for accepting connection requests, which may not apply for RVMA?
static void rs_accept(struct rsocket *rs)

// Same as above
int raccept(int socket, struct sockaddr *addr, socklen_t *addrlen)

// Same as above
int rconnect(int socket, const struct sockaddr *addr, socklen_t addrlen)

static int rs_post_write(struct rsocket *rs,
			 struct ibv_sge *sgl, int nsge,
			 uint32_t wr_data, int flags,
			 uint64_t addr, uint32_t rkey)

static int rs_post_write_msg(struct rsocket *rs,
			 struct ibv_sge *sgl, int nsge,
			 uint32_t msg, int flags,
			 uint64_t addr, uint32_t rkey)

static int ds_post_send(struct rsocket *rs, struct ibv_sge *sge,
			uint32_t wr_data)

static int rs_write_data(struct rsocket *rs,
			 struct ibv_sge *sgl, int nsge,
			 uint32_t length, int flags)

static int rs_write_direct(struct rsocket *rs, struct rs_iomap *iom, uint64_t offset,
			   struct ibv_sge *sgl, int nsge, uint32_t length, int flags)

static int rs_write_iomap(struct rsocket *rs, struct rs_iomap_mr *iomr,
			  struct ibv_sge *sgl, int nsge, int flags)

ssize_t rrecv(int socket, void *buf, size_t len, int flags)

ssize_t rrecvfrom(int socket, void *buf, size_t len, int flags,
		  struct sockaddr *src_addr, socklen_t *addrlen)

ssize_t rsend(int socket, const void *buf, size_t len, int flags)

ssize_t rsendto(int socket, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen)

static ssize_t rsendv(int socket, const struct iovec *iov, int iovcnt, int flags)