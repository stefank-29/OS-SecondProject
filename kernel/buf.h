struct buf { // predstavlja 1 blok na disku ucitan u memoriju
	int flags; // bitovi su zapravo flagovi
	uint dev; // koji je po redu harddisk (na xv6 uvek 1)
	uint blockno; // redni broj bloka (1 - 1000) => index bloka koji citamo ili pisemo
	struct sleeplock lock;
	uint refcnt; // koliko procesa koristi bafer
	struct buf *prev; // LRU cache list
	struct buf *next;
	struct buf *qnext; // disk queue
	uchar data[BSIZE]; // niz podataka od 512B
};
#define B_VALID 0x2  // buffer has been read from disk
#define B_DIRTY 0x4  // buffer needs to be written to disk

