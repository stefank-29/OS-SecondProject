// On-disk file system format.
// Both the kernel and user programs use this header file.


#define ROOTINO 1  // root i-number
#define BSIZE 512  // block size

// Disk layout:
// [ boot block | super block | log | inode blocks |
//                                          free bit map | data blocks]
//
// mkfs computes the super block and builds an initial file system. The
// super block describes the disk layout:
struct superblock {
	uint size;         // Size of file system image (blocks)
	uint nblocks;      // Number of data blocks
	uint ninodes;      // Number of inodes.
	uint nlog;         // Number of log blocks
	uint logstart;     // Block number of first log block
	uint inodestart;   // Block number of first inode block
	uint bmapstart;    // Block number of first free map block
};

#define NDIRECT 11
#define NINDIRECT (BSIZE / sizeof(uint)) // 512B/4B = 128
#define MAXFILE (NDIRECT + NINDIRECT + NINDIRECT*NINDIRECT)

// On-disk inode structure
struct dinode { //* inode kad je na disku
	short type;           // File type //* uredjaj ili obican file
	short major;          // Major device number (T_DEV only)
	short minor;          // Minor device number (T_DEV only)
	short nlink;          // Number of links to inode in file system //* precice ka fajlu
	uint size;            // Size of file (bytes) //* velicina file-a na disku
	uint addrs[NDIRECT+2];   // Data block addresses //* niz pokazivaca na blokove (13)
};
// velicina: 8 + 4 + 13*4 = 64B

// 512 / 64 = 8 //* 8 inode struktura u jedan blok na disku

// Inodes per block.
#define IPB           (BSIZE / sizeof(struct dinode))

// Block containing inode i
#define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)

// Bitmap bits per block
#define BPB           (BSIZE*8)

// Block of free map containing bit for block b
#define BBLOCK(b, sb) (b/BPB + sb.bmapstart)

// Directory is a file containing a sequence of dirent structures.
#define DIRSIZ 14

struct dirent {
	ushort inum; // redni broj inode-a koji opisuje file
	char name[DIRSIZ]; // naziv za file
};

