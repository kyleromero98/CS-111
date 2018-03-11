#!/usr/bin/python
import sys
import csv

# sublists
group_list = []    
bfree_list = []
ifree_list = []
inode_list = []
dirent_list = []
indirect_list = []
reserved_blocks = []
block_refs = []
inode_refs = []
# other structures
bres_list = []
bdup_dict = {}
ilnk_dict = {}
# superblock info
total_blocks = 0
total_inodes = 0
s_blks_per_group = 0
s_inodes_per_group = 0

def init_sublists(csv_file):
    # Build lists for every type of entry
    for row in csv_file:
        if row[0] == "SUPERBLOCK":
            global total_blocks, total_inodes
            total_blocks = int(row[1])
            total_inodes = int(row[2])
            block_size = int(row[3])
            s_inodes_per_group = int(row[6])
            first_v_inode = row[7]
        if row[0] == "GROUP":
            group_list.append(row[1:])
        elif row[0] == "BFREE":
            bfree_list.append(row[1])
        elif row[0] == "IFREE":
            ifree_list.append(row[1])
        elif row[0] == "INODE":
            inode_list.append(row[1:])
        elif row[0] == "DIRENT":
            dirent_list.append(row[1:])
        elif row[0] == "INDIRECT":
            indirect_list.append(row[1:])

    # Build list for reserved block
    size_of_inode = 128
    inodes_per_block = block_size / size_of_inode
    itable_blocks = s_inodes_per_group / inodes_per_block
    for group in group_list:
        first_v_block = int(group[7]) + itable_blocks
        for i in range(1, first_v_block):
            bres_list.append(str(i)) # append all reserved blocks
    
    # Initialize list of block references
    block_list = []
    for group in group_list:
        for block_num in range(0, int(group[1])):
            if str(block_num) in bfree_list or str(block_num) in bres_list:
                block_list.append(1)
            else:
                block_list.append(0)
        block_refs.append(block_list)
        block_list = []
    # Initialize list of inode references
    for i in range(0, total_inodes):
        if i < int(first_v_inode) or str(i) in ifree_list:
            inode_refs.append(1)
        else:
            inode_refs.append(0)

    # Initialize list of allocated inode link count
    for cur_inode in inode_list:
        index = cur_inode[0]
        link_count = cur_inode[5]
        ilnk_dict[index] = link_count
    
    
def check_block_consistency():
    # Invalid block is one whose number is <0 or greater than the highest block in the system
    # Reserved block is one that cannot be allocated to a file (eg. superblock, free block list)
    # Unreferenced block is one that is not referenced by any file and is not on the free list
    # Duplicate block is one that is allocated to multiple files
    global total_blocks
    for cur_inode in inode_list:
        offset = 0
        # get blocks for current inode
        blk_list = cur_inode[11:]
        # check for invalid blocks
        # Direct blocks
        #print blk_list[:12]
        for blk in blk_list[:12]:
            # check for valid offset
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
            # check if block is reserved
            elif blk in bres_list:
                print "RESERVED BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
            # check if the block is on the free list
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
            # add the block to the dict
            elif int(blk) != 0:
                block_refs[0][int(blk)] = 1
                if not bdup_dict.has_key(blk):
                    bdup_dict[blk] = []
                    bdup_dict[blk] = [(cur_inode[0], offset, 0)]
                else:
                    updated_list = bdup_dict[blk]
                    updated_list.append((cur_inode[0], offset, 0))
                    bdup_dict[blk] = updated_list
            offset += 1
        # Single indirect block
        blk = blk_list[12]
        offset = 12 # first indirect block
        if int(blk) < 0 or int(blk) > total_blocks - 1:
            print "INVALID INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bres_list:
            print "RESERVED INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bfree_list:
            print "ALLOCATED BLOCK", blk, "ON FREELIST"
        elif int(blk) != 0:
            block_refs[0][int(blk)] = 1
            if not bdup_dict.has_key(blk):
                bdup_dict[blk] = []
                bdup_dict[blk] = [(cur_inode[0], offset, 1)]
            else:
                updated_list = bdup_dict[blk]
                updated_list.append((cur_inode[0], offset, 1))
                bdup_dict[blk] = updated_list
        # Double indirect block
        blk = blk_list[13]
        offset = 268 # first double indirect block
        if int(blk) < 0 or int(blk) > total_blocks - 1:
            print "INVALID DOUBLE INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bres_list:
            print "RESERVED DOUBLE INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bfree_list:
            print "ALLOCATED BLOCK", blk, "ON FREELIST"
        elif int(blk) != 0:
            block_refs[0][int(blk)] = 1
            if not bdup_dict.has_key(blk):
                bdup_dict[blk] = []
                bdup_dict[blk] = [(cur_inode[0], offset, 2)]
            else:
                updated_list = bdup_dict[blk]
                updated_list.append((cur_inode[0], offset, 2))
                bdup_dict[blk] = updated_list
        # Triple indirect block
        blk = blk_list[14]
        offset = 65804
        if int(blk) < 0 or int(blk) > total_blocks - 1:
            print "INVALID TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bres_list:
            print "RESERVED TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode[0], "AT OFFSET", offset
        elif blk in bfree_list:
            print "ALLOCATED BLOCK", blk, "ON FREELIST"
        elif int(blk) != 0:
            block_refs[0][int(blk)] = 1
            if not bdup_dict.has_key(blk):
                bdup_dict[blk] = []
                bdup_dict[blk] = [(cur_inode[0], offset, 3)]
            else:
                updated_list = bdup_dict[blk]
                updated_list.append((cur_inode[0], offset, 3))
                bdup_dict[blk] = updated_list

    # check indirect entries
    for row in indirect_list:
        level = row[1]
        cur_inode = row[0]
        # check the block being scanned
        blk = row[3]
        if int(level) == 1:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
        if int(level) == 2:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
        if int(level) == 3:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED TRIPLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
        # check the block being referenced
        blk = int(row[4])
        ref_level = int(level) - 1
        if ref_level == 0:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
            elif blk != 0:
                block_refs[0][blk] = 1
                str_blk = str(blk)
                if not bdup_dict.has_key(str_blk):
                    bdup_dict[str_blk] = []
                    bdup_dict[str_blk] = [(cur_inode, offset, 0)]
                else:
                    updated_list = bdup_dict[str_blk]
                    updated_list.append((cur_inode, offset, 0))
                    bdup_dict[str_blk] = updated_list
        if ref_level == 1:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
            elif blk != 0:
                block_refs[0][blk] = 1
                str_blk = str(blk)
                if not bdup_dict.has_key(str_blk):
                    bdup_dict[str_blk] = []
                    bdup_dict[str_blk] = [(cur_inode, offset, 1)]
                else:
                    updated_list = bdup_dict[str_blk]
                    updated_list.append((cur_inode, offset, 1))
                    bdup_dict[str_blk] = updated_list
        if ref_level == 2:
            if int(blk) < 0 or int(blk) > total_blocks - 1:
                print "INVALID DOUBLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bres_list:
                print "RESERVED DOUBLE INDIRECT BLOCK", blk, "IN INODE", cur_inode, "AT OFFSET", row[2]
            elif blk in bfree_list:
                print "ALLOCATED BLOCK", blk, "ON FREELIST"
            elif blk != 0:
                block_refs[0][blk] = 1
                str_blk = str(blk)
                if not bdup_dict.has_key(str_blk):
                    bdup_dict[str_blk] = []
                    bdup_dict[str_blk] = [(cur_inode, offset, 2)]
                else:
                    updated_list = bdup_dict[str_blk]
                    updated_list.append((cur_inode, offset, 2))
                    bdup_dict[str_blk] = updated_list

    # check for duplicate blocks
    for blk in bdup_dict:
        ref_list = bdup_dict[blk]
        #print ref_list
        if len(ref_list) > 1:
            for ref in ref_list:
                # Check the level of every reference to the blk
                if ref[2] == 0:
                    print "DUPLICATE BLOCK", blk, "IN INODE", ref[0], "AT OFFSET", ref[1]
                elif ref[2] == 1:
                    print "DUPLICATE INDIRECT BLOCK", blk, "IN INODE", ref[0], "AT OFFSET", ref[1]
                elif ref[2] == 2:
                    print "DUPLICATE DOUBLE INDIRECT BLOCK", blk, "IN INODE", ref[0], "AT OFFSET", ref[1]
                elif ref[2] == 3:
                    print "DUPLICATE TRIPLE INDIRECT BLOCK", blk, "IN INODE", ref[0], "AT OFFSET", ref[1]

    # check unreferenced blocks
    block_list = []
    for group in group_list:
        group_num = int(group[0])
        block_list = block_refs[group_num];
        for i in range(0, len(block_list)):
            if i != 0 and block_list[i] < 1:
                print "UNREFERENCED BLOCK", i
def inode_audit() :
    for cur_inode in inode_list:
        inum = cur_inode[0]
        type = cur_inode[1]
        if type != 0:
            if inum in ifree_list:
                print "ALLOCATED INODE", inum, "ON FREELIST"
            else:
                inode_refs[int(inum)] = 1
    #print inode_refs
    for i in range(0, len(inode_refs)):
        if inode_refs[i] < 1:
            print "UNALLOCATED INODE", i, "NOT ON FREELIST"

def check_dir_consistency():
    global total_inodes
    # initialize the calc_lnk_list with every link stated in the csv
    calc_lnk_list = {}
    for entry in ilnk_dict:
        inum = entry
        calc_lnk_list[inum] = 0
    # Calculate the link count for every inode    
    #print dirent_list
    for entry in dirent_list:
        p_inum = entry[0]
        inum = entry[2]
        name = entry[5]
        if calc_lnk_list.has_key(inum):
            new_count = calc_lnk_list.get(inum)
            new_count = str(int(new_count) + 1)
            calc_lnk_list[inum] = new_count
        # if it does not have the key, then the direntry is referencing a unallocated/invalid inode
        else:
            if int(inum) < 1 or int(inum) > total_inodes - 1:
                print "DIRECTORY INODE", p_inum, "NAME", name, "INVALID INODE", inum
            elif inum in ifree_list:
                print "DIRECTORY INODE", p_inum, "NAME", name, "UNALLOCATED INODE", inum
        # Check the '.' link
        if name == "'.'" and inum != p_inum:
            print "DIRECTORY INODE", p_inum, "NAME", name, "LINK TO INODE", inum, "SHOULD BE", p_inum
        # To check '..' link, look at the parent dirent and see if it includes this dirent
        if name == "'..'":
            if int(p_inum) == 2 and int(inum) != 2:
                print "DIRECTORY INODE", p_inum, "NAME", name, "LINK TO INODE", inum, "SHOULD BE", 2
            for check in dirent_list:
                check_p_inum = check[0]
                check_inum = check[2]
                check_name = check[5]
                if p_inum == check_inum and check_p_inum != inum and check_name != "'.'" and check_name != "'..'":
                    print "DIRECTORY INODE", p_inum, "NAME", name, "LINK TO INODE", inum, "SHOULD BE", check_p_inum
    #print calc_lnk_list
    #print ilnk_dict
    # Compare the given link count and calculated link count
    for entry in ilnk_dict:
        inum = entry
        lnk_cnt = ilnk_dict[entry]
        calc_lnk_cnt = calc_lnk_list[entry]
        if lnk_cnt != calc_lnk_cnt:
            print "INODE", inum, "HAS", calc_lnk_cnt, "LINKS BUT LINKCOUNT IS", lnk_cnt
        

def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Incorrect Number of arguments\n")
        exit(1)
    input = open(sys.argv[1], "rb")
    csv_file = csv.reader(input)
    init_sublists(csv_file)
    check_block_consistency()
    inode_audit()
    check_dir_consistency()
    #for row in csv_read:
    #    print row
    
if __name__ == "__main__":
    main()

