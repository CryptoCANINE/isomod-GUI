/* You may freely use, distribute, and modify this file */
#include <ctype.h>
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t loc_t;
typedef uint8_t byte;
unsigned int sectorSize = 0x800;

#ifdef _WIN32
#define fseeko64 _fseeki64
#define PACK(__Declaration__) \
  __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#elif defined(__GNUC__)
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

#define ALIGN(x, y) (((x) + ((y)-1)) & (~((y)-1)))

int getfilesize(FILE* f) {
  int spos = ftell(f);
  fseek(f, 0, SEEK_END);
  int len = ftell(f);
  fseek(f, spos, SEEK_SET);
  return len;
}

void CdSetloc(FILE* f, loc_t newpos) {
  fseeko64(f, newpos * sectorSize, SEEK_SET);
}

int CdRead(void* buf, loc_t nsectors, FILE* f) {
  return fread(buf, nsectors, sectorSize, f);
}

void CdWrite(void* buf, loc_t nsectors, FILE* f) {
  fwrite(buf, nsectors, sectorSize, f);
}

struct iso_directory_t {
  uint8_t len;
  uint8_t ex_len;
  uint32_t lba;
  uint32_t big_lba;
  uint32_t file_len;
  uint32_t big_file_len;
  byte time_date[7];
  byte file_flags;
  byte file_unit_size;
  byte interleave_gap_size;
  uint16_t volseq_num;
  uint16_t big_volseq_num;
  uint8_t fileid_len;
  char fileid[0];
} __attribute__((packed));

bool ispvd(byte* sec) {
  return ((sec[0] == 1) && (memcmp(sec + 1, "CD001", 5) == 0));
}

bool scmplen(const char* s1, const char* s2, int len) {
  for (int i = 0; i < len; i += 1) {
    if (tolower(s1[i]) != tolower(s2[i])) {
      return false;
    }
  }
  return true;
}
bool streq(const char* s1, const char* s2) {
  // return (strcmp(s1, s2) == 0);
  return scmplen(s1, s2, strlen(s1));
}

loc_t CdTell(FILE* isofile) {
  loc_t s = ftell(isofile);
  return (s & (~(0x7FF))) / 0x800;
}

bool CdFindFileInDir(iso_directory_t*& out_dir, FILE* isofile,
                     const char* filename, int filename_len, loc_t& out_secnum,
                     loc_t& out_offset) {
  byte* sec = (byte*)malloc(sectorSize);
  iso_directory_t* dir = (iso_directory_t*)(sec);
  int slen = filename_len;
  int dirp = 0;

  CdRead(sec, 1, isofile);

  printf("Find %s %d\n", filename, slen);

  while (dir->len != 0) {
    int dlen = dir->fileid_len;
    if (!(dir->file_flags & 2)) {
      dlen -= 2;
    }
    int secloc = CdTell(isofile) - 1;
    if (dlen == slen) {
      if (scmplen(dir->fileid, filename, slen) == true) {
        out_dir = dir;
        if (NULL != out_secnum) {
          out_secnum = secloc;
        }
        if (NULL != out_offset) {
          out_offset = dirp;
        }
        return true;
      }
    }
    dirp += dir->len;
    if (dirp >= sectorSize) {
      CdRead(sec, 1, isofile);
      dirp %= sectorSize;
    }
    dir = (iso_directory_t*)(sec + dirp);
  }
  return false;
}

bool CdFindFile(iso_directory_t* outdir, FILE* isofile, const char* filename,
                loc_t& out_secnum, loc_t& out_offset) {
  const char* next;
  const char* cur = filename;
  int slen;
  do {
    next = strchr(cur, '/');
    if (next == NULL) {
      slen = strlen(cur);
    } else {
      slen = int(next - cur);
    }
    if (false ==
        CdFindFileInDir(outdir, isofile, cur, slen, out_secnum, out_offset)) {
      return false;
    }
    if (next != NULL) {
      CdSetloc(isofile, outdir->lba);
      next++;
      cur = next;
    } else
      break;
  } while (next != NULL);
  return true;
}

#define CMD(x) if (streq(#x, argv[1]))
void printhelp() { printf("isomod put [isofile] [targetfile] [hostfile]\n"); }

int main(int argc, char* argv[]) {
  if (sizeof(iso_directory_t) != 33) {
    fprintf(stderr, "Bad Install %lu\n", sizeof(iso_directory_t));
    return 1;
  }
  if (argc <= 1) {
    printhelp();
    return 0;
  } else
    CMD(put) {
      if (argc <= 4) {
        printf("isomod put [isofile] [targetfile] [hostfile]\n");
        return 0;
      }
      const char* isofilename = argv[2];
      const char* targetfilename = argv[3];
      const char* hostfilename = argv[4];
      bool length_override = true;
      FILE* isofile = fopen(isofilename, "rb+");
      if (NULL == isofile) {
        fprintf(stderr, "Couldn't open ISO %s\n", isofilename);
        return 1;
      }
      FILE* hostfile = fopen(hostfilename, "rb");
      if (NULL == hostfile) {
        fprintf(stderr, "Couldn't open host file %s\n", hostfilename);
        return 1;
      }
      byte* sec = (byte*)(malloc(sectorSize));
      iso_directory_t* dir = (iso_directory_t*)(sec);
      CdSetloc(isofile, 16);
      CdRead(sec, 1, isofile);
      if (ispvd(sec) == false) {
        fprintf(stderr, "%s is not an ISO file\n", isofilename);
        return 1;
      }
      loc_t root_lba = *(loc_t*)(sec + 158);
      printf("root lba = %x, %x\n", root_lba, root_lba * sectorSize);
      CdSetloc(isofile, root_lba);
      loc_t dir_lba, dir_offset;
      bool s = CdFindFile(dir, isofile, targetfilename, dir_lba, dir_offset);
      if (false == s) {
        fprintf(stderr, "Could not find target file %s on ISO file %s\n",
                targetfilename, isofilename);
        return 1;
      }
      CdSetloc(isofile, dir_lba);
      CdRead(sec, 1, isofile);
      dir = (iso_directory_t*)(sec + dir_offset);
      printf("File size on ISO is %d\n", dir->file_len);
      int maxsize = ALIGN(dir->file_len, sectorSize);
      int len = getfilesize(hostfile);
      int aligned_len = ALIGN(len, sectorSize);
      printf("File size on HOST is %d\n", len);
      byte* filedata = (byte*)(malloc(aligned_len));
      memset(filedata, 0, aligned_len);
      fread(filedata, 1, len, hostfile);
      fclose(hostfile);
      printf("Writing %d bytes to sector %u\n", len, dir->lba);
      CdSetloc(isofile, dir->lba);
      fwrite(filedata, 1, aligned_len, isofile);
      dir->file_len = len;
      printf("Writing new directory to %u\n", dir_lba);
      CdSetloc(isofile, dir_lba);
      CdWrite(sec, 1, isofile);
      printf("Done.\n");
      fclose(isofile);
      return 0;
    }
  else {
    fprintf(stderr, "isomod   Unknown command: %s\n", argv[1]);
    return 1;
  }
  return 0;
}
