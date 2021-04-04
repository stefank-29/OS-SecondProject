// Buffer cache.
//
// The buffer cache is a linked list of buf structures holding
// cached copies of disk block contents.  Caching disk blocks
// in memory reduces the number of disk reads and also provides
// a synchronization point for disk blocks used by multiple processes.
//
// Interface:
// * To get a buffer for a particular disk block, call bread.
// * After changing buffer data, call bwrite to write it to disk.
// * When done with the buffer, call brelse.
// * Do not use the buffer after calling brelse.
// * Only one process at a time can use a buffer,
//     so do not keep them longer than necessary.
//
// The implementation uses two state flags internally:
// * B_VALID: the buffer data has been read from the disk.
// * B_DIRTY: the buffer data has been modified
//     and needs to be written to disk.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"

struct {
	struct spinlock lock;
	struct buf buf[NBUF]; // niz bafera (30)

	// Linked list of all buffers, through prev/next.
	// head.next is most recently used.
	struct buf head; // pocetak liste (head.next pokazuje na najskorije koriscen bafer)
} bcache;

void
binit(void) // pravi uvezanu listu praznih elemenata
{
	struct buf *b;

	initlock(&bcache.lock, "bcache");

	// Create linked list of buffers
	bcache.head.prev = &bcache.head;
	bcache.head.next = &bcache.head;
	for(b = bcache.buf; b < bcache.buf+NBUF; b++){
		b->next = bcache.head.next;
		b->prev = &bcache.head;
		initsleeplock(&b->lock, "buffer");
		bcache.head.next->prev = b;
		bcache.head.next = b;
	}
}

// Look through buffer cache for block on device dev.
// If not found, allocate a buffer.
// In either case, return locked buffer.
static struct buf*
bget(uint dev, uint blockno)
{
	struct buf *b;

	acquire(&bcache.lock);

	//* Is the block already cached?
	// prolazim kroz listu od prvog elem i trazim da l se poklapaju dev i blockno
	for(b = bcache.head.next; b != &bcache.head; b = b->next){
		if(b->dev == dev && b->blockno == blockno){
			b->refcnt++; // jos jedan proces koristi blok
			release(&bcache.lock);
			acquiresleep(&b->lock);
			return b; // vrati se buf
		}
	}

	//* Ako ga nema u kesu krenem od kraja liste
	// Not cached; recycle an unused buffer.
	// Even if refcnt==0, B_DIRTY indicates a buffer is in use
	// because log.c has modified it but not yet committed it.
	for(b = bcache.head.prev; b != &bcache.head; b = b->prev){
		if(b->refcnt == 0 && (b->flags & B_DIRTY) == 0) { // da li ga neki program koristi i B_DIRTY == 0
			b->dev = dev;
			b->blockno = blockno;
			b->flags = 0; // citanje
			b->refcnt = 1; // koristi ga proces koji poziva bget
			release(&bcache.lock);
			acquiresleep(&b->lock);
			return b;
		}
	}
	panic("bget: no buffers");
}

// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno) // vraca buf strukturu koja predstavlja taj blok
{
	struct buf *b;

	b = bget(dev, blockno);
	if((b->flags & B_VALID) == 0) { // ako je VALID == 0 -> treba da se cita sa diska (ubacena nova stavka u cache)
		iderw(b);					// ako je VALID == 1 -> dobio sam kesiranu kopiju i samo vratim buf (ne citam sa diska)
	}
	return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
	if(!holdingsleep(&b->lock))
		panic("bwrite");
	b->flags |= B_DIRTY; // setuje se DIRTY bit i upise bafer na disk
	iderw(b);
}

// Release a locked buffer.
// Move to the head of the MRU list.
void
brelse(struct buf *b)
{
	if(!holdingsleep(&b->lock))
		panic("brelse");

	releasesleep(&b->lock);

	acquire(&bcache.lock);
	b->refcnt--;
	if (b->refcnt == 0) { // postavi se na pocetak liste (da moze opet da se koristi)
		// no one is waiting for it.
		b->next->prev = b->prev;
		b->prev->next = b->next;
		b->next = bcache.head.next;
		b->prev = &bcache.head;
		bcache.head.next->prev = b;
		bcache.head.next = b;
	}

	release(&bcache.lock);
}

