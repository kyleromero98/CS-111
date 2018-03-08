#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <time.h>
#include "ext2_fs.h"

#define BASE_OFFSET 1024
#define SUPERBLOCK_SIZE 1024
#define GROUP_DESCRIPTOR_TABLE_SIZE 32
#define LVL1_BLOCK_START 12
#define LVL2_BLOCK_START 268
#define LVL3_BLOCK_START 65804

int fs_fd;
int log_fd;
struct ext2_super_block* super = NULL;
struct ext2_group_desc* group_desc = NULL;
struct ext2_inode* a_inodes = NULL;
unsigned int* group_bsizes = NULL;
unsigned int* group_isizes = NULL;
unsigned int group_count = 0;
int** a_inodes_bits = NULL;
int block_size = 0;

void input_handler (int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error: Invalid Input\n");
    exit(1);
  }
  fs_fd = open(argv[1], O_RDONLY);
  if (fs_fd < 0) {
    fprintf(stderr, "Erron: Invalid Input\n"); 
    exit(1);
  } 
}

void read_superblock () {
  //log_fd = creat("", S_IRWXU);
  super = (struct ext2_super_block*) malloc(sizeof(struct ext2_super_block));
  lseek(fs_fd, BASE_OFFSET, SEEK_SET);
  read(fs_fd, super, sizeof(struct ext2_super_block));
  if (super->s_magic != EXT2_SUPER_MAGIC) {
    fprintf(stderr, "File system not valid\n");
    exit(2);
  }
  block_size = 1024 << super->s_log_block_size;
  // 1024 << super.s_log_block_size calculate block size in bytes
  fprintf(stdout, "SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n",
	  super->s_blocks_count, super->s_inodes_count, block_size,
	  super->s_inode_size, super->s_blocks_per_group, super->s_inodes_per_group,
	  super->s_first_ino);  
}

void read_blockgroups () {
  // Calculating block size
  group_count = 1 + (super->s_blocks_count - 1) / (super->s_blocks_per_group);
  group_bsizes = (unsigned int*) malloc(sizeof(unsigned int) * group_count);
  group_isizes = (unsigned int*) malloc(sizeof(unsigned int) * group_count);
  int spare_blocks = super->s_blocks_count % super->s_blocks_per_group;
  int spare_inodes = super->s_inodes_count % super->s_inodes_per_group;
  // Allocating group space for group descriptors
  group_desc = (struct ext2_group_desc*) malloc(sizeof(struct ext2_group_desc) * group_count);  
  // Seek to the start of the group descriptor table
  unsigned int group_num = 0;
  int num_blocks = 0;
  int num_inodes = 0;
  while (group_num < group_count) {
    lseek(fs_fd, BASE_OFFSET + SUPERBLOCK_SIZE + (group_num * sizeof(struct ext2_group_desc)), SEEK_SET);
    read(fs_fd, &group_desc[group_num], sizeof(struct ext2_group_desc));
    if (group_num == group_count - 1 && spare_blocks != 0) num_blocks = spare_blocks;
    else num_blocks = super->s_blocks_per_group;
    if (group_num == group_count - 1 && spare_inodes != 0) num_inodes = spare_inodes;
    else num_inodes = super->s_inodes_per_group;
    group_bsizes[group_num] = num_blocks;
    group_isizes[group_num] = num_inodes;
    fprintf(stdout, "GROUP,%d,%d,%d,%d,%d,%d,%d,%d\n",
	    group_num, num_blocks, super->s_inodes_per_group,
	    group_desc[group_num].bg_free_blocks_count, group_desc[group_num].bg_free_inodes_count,
	    group_desc[group_num].bg_block_bitmap, group_desc[group_num].bg_inode_bitmap,
	    group_desc[group_num].bg_inode_table);
    
    group_num++;
  }
}

void read_freeblocks() {
  unsigned int i, j;
  uint8_t byte;
  int bit_c = 1;
  int lsb_mask = 0x01;
  i = 0;
  while (i < group_count) {
    j = 0;
    while (j < group_bsizes[i]) {
      pread(fs_fd, &byte, 1, (group_desc[i].bg_block_bitmap * block_size) + j);
      int k = 0;
      while (k < 8) {
	int bit = byte & lsb_mask;
	if (!bit) {
	  fprintf(stdout, "BFREE,%d\n", bit_c);
	}
	byte = byte >> 1;
	bit_c++;
	k++;
      }
      j++;
    }
    i++;
  }
}

void read_freeinodes() {
  unsigned int i, j;
  uint8_t byte;
  int bit_c = 1;
  int a_inode_count = 0;
  int lsb_mask = 0x01;
  a_inodes_bits = (int**) malloc(sizeof(int*) * group_count);
  i = 0;
  while (i < group_count) {
    fprintf(stderr, "group_isizes[i]: %d\n", group_isizes[i]);
    a_inodes_bits[i] = (int*) malloc(sizeof(int) * group_isizes[i]);
    j = 0;
    while (j < group_isizes[i]) {
      pread(fs_fd, &byte, 1, (group_desc[i].bg_inode_bitmap * block_size) + j);
      int k = 0;
      while (k < 8) {
     	int bit = byte & lsb_mask;
     	a_inodes_bits[i][bit_c - 1] = bit;
     	if (!bit) {
     	  // Log free inodes
     	  fprintf(stdout, "IFREE,%d\n", bit_c);
	}
	else {
	  // Count valid inodes
	  a_inode_count++;
	}
       	byte = byte >> 1;
	bit_c++;
	k++;
      }
      if ((unsigned int) bit_c - 1 > group_isizes[i])
	break;
      j++;
    }
    i++;
  }
  // Allocate all the valid inodes for saving later
  a_inodes = (struct ext2_inode*) malloc(sizeof(struct ext2_inode) * a_inode_count);
}

void read_direntries(int parent_inode, struct ext2_inode dir_inode) {
  struct ext2_dir_entry dir;
  int blocks_used = dir_inode.i_blocks/(2<<super->s_log_block_size);
  int offset = 0;
  int i = 0;
  while (i < blocks_used) {
    while (offset < 1024) {
      lseek(fs_fd, block_size * dir_inode.i_block[i] + offset, SEEK_SET);
      read (fs_fd, &dir, sizeof(struct ext2_dir_entry));
      if (dir.inode)
	fprintf(stdout, "DIRENT,%d,%d,%d,%d,%d,'%s'\n", parent_inode, offset, dir.inode, dir.rec_len, dir.name_len, dir.name);
      offset += dir.rec_len;
    }
    offset = 0;
    i++;
  }
}

void read_indirect(int parent_inode, int block_start, int block_id, int level) {
  if (block_id == 0) {
    return;
  }
  if (level < 1) {
     return;
  }
  else {
    int start_bool = 0;
    int block_index = 0;
    int log_block_offset = 0;
    unsigned int block_buf;
    int blk_start = block_id * block_size;
    int blk_offset = 0;
    while (blk_offset < block_size) {
      lseek(fs_fd, blk_start + blk_offset, SEEK_SET);
      read(fs_fd, &block_buf, sizeof(unsigned int));
      if (block_buf != 0) {
	switch (level) {
	case 1:
	  log_block_offset = block_start + block_index;
	  break;
	case 2:
	  log_block_offset = block_start + block_index;
	  break;
	case 3:
	  log_block_offset = block_start + block_index;
	  break;
	}
	start_bool = 1;
	fprintf(stdout, "INDIRECT,%d,%d,%d,%d,%d\n",
		  parent_inode, level, log_block_offset, block_id, block_buf);
	read_indirect(parent_inode, log_block_offset, block_buf, level - 1);
      }
      else {
	if (start_bool)
	  return;
      }
      block_index++;
      blk_offset += sizeof(unsigned int);
    }
  }
}

void read_inodes() {
  unsigned int i, j;
  int a_inode_counter = 0;
  i = 0;
  while (i < group_count) {
    j = 0;
    while (j < group_isizes[i]) {
      if (a_inodes_bits[i][j]) {
	int inode_offset =
	  block_size * group_desc[i].bg_inode_table + (j * super->s_inode_size);
	lseek(fs_fd, inode_offset, SEEK_SET);
	read(fs_fd, &a_inodes[a_inode_counter], super->s_inode_size);
	int bool =
	  a_inodes[a_inode_counter].i_mode && a_inodes[a_inode_counter].i_links_count;
	if (bool) {
	  char type;
	  struct tm* t_atime, *t_ctime, *t_mtime;
	  char s_atime[80], s_ctime[80], s_mtime[80];
	  long int l_atime, l_ctime, l_mtime;
	  int type_mask = 0xFFF;
	  // Get file type
	  if (S_ISREG(a_inodes[a_inode_counter].i_mode)) type = 'f';
	  else if (S_ISDIR(a_inodes[a_inode_counter].i_mode)) {
	    type = 'd';
	  }
	  else if (S_ISLNK(a_inodes[a_inode_counter].i_mode)) type = 's';
	  else type = '?';
	  // Get time stamps
	  // Cast times to time_t
	  l_atime = a_inodes[a_inode_counter].i_atime;
	  l_ctime = a_inodes[a_inode_counter].i_ctime;
	  l_mtime = a_inodes[a_inode_counter].i_mtime;
	  // Get gmtime
	  t_atime = gmtime(&l_atime);
	  strftime(s_atime, 80, "%x %X", t_atime);
	  t_ctime = gmtime(&l_ctime);
	  strftime(s_ctime, 80, "%x %X", t_ctime);
	  t_mtime = gmtime(&l_mtime);
	  strftime(s_mtime, 80, "%x %X", t_mtime);
	  // Print inode attributes
	  fprintf(stdout, "INODE,%d,%c,%o,%d,%d,%d,%s,%s,%s,%d,%d,",
		  j + 1, type, a_inodes[a_inode_counter].i_mode & type_mask,
		  a_inodes[a_inode_counter].i_uid, a_inodes[a_inode_counter].i_gid,
		  a_inodes[a_inode_counter].i_links_count, s_ctime, s_mtime, s_atime,
		  a_inodes[a_inode_counter].i_size, a_inodes[a_inode_counter].i_blocks);
	  // print inode block addresses
	  int block_num = 0;
	  while (block_num < EXT2_N_BLOCKS) {
	    if (block_num != EXT2_N_BLOCKS - 1)
	      fprintf(stdout,"%d,", a_inodes[a_inode_counter].i_block[block_num]);
	    else
	      fprintf(stdout,"%d\n", a_inodes[a_inode_counter].i_block[block_num]);
	    block_num++;
	  }
	  // read directories
	  if (type == 'd') {
	    read_direntries(j + 1, a_inodes[a_inode_counter]);
	  }
	  // read indirect blocks
	  if (type == 'f' || type == 'd') {
	    int block;
	    int i = EXT2_IND_BLOCK;
	    while (i < EXT2_N_BLOCKS) {
	      switch (i) {
	      case EXT2_IND_BLOCK:
		block = a_inodes[a_inode_counter].i_block[EXT2_IND_BLOCK];
		read_indirect(j + 1, LVL1_BLOCK_START, block, 1);
		break;
	      case EXT2_DIND_BLOCK:
		block = a_inodes[a_inode_counter].i_block[EXT2_DIND_BLOCK];
		read_indirect(j + 1, LVL2_BLOCK_START, block, 2);
		break;
	      case EXT2_TIND_BLOCK:
		block = a_inodes[a_inode_counter].i_block[EXT2_TIND_BLOCK];
		read_indirect(j + 1, LVL3_BLOCK_START, block, 3);
		break;
	      }
	      i++;
	    }
	  }
	}
	a_inode_counter++;
      }
      j++;
    }
    i++;
  }
}

int main (int argc, char** argv) {
  input_handler(argc, argv);
  read_superblock();
  read_blockgroups();
  read_freeblocks();
  read_freeinodes();
  read_inodes();
  printf("Done\n");
  return 0;
}
