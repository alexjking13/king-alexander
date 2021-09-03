#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>


int fd;
char buf[512];
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct partition
{
  u8 drive;
  u8 head;
  u8 sector;
  u8 cylinder;
  u8 sys_type;
  u8 end_head;
  u8 end_sector;
  u8 end_cylinder;
  u32 start_sector;
  u32 nr_sectors;
}Partition;

char *dev = "vdisk";
int read_sector(int fd, int sector, char *buf)
{
  lseek(fd,sector*512,SEEK_SET);
  read(fd,buf,512);
}
int main()
{
  struct partition *p;
  char buf[512];
  fd = open(dev,O_RDONLY);
  read_sector(fd,0,buf);
  p=(struct partition *)(&buf[0x1be]);
  for(int i =0;i<4;i++)
    {
      partitionPrint(p);
      if(p->sys_type==5)
	{
	  recursionPartitionPrint(p,p->start_sector);
	}
      p++;
      
    }
  return 0;


}
void partitionPrint(Partition *p)
{
  printf("sys_type = %d\n",p->sys_type);
  printf("start_sector = %u\n",p->start_sector);
  printf("end_sector %u\n",(p->start_sector + p->nr_sectors-1));
  printf("nr_sectors = %u\n\n",p->nr_sectors);
}
void recursionPartitionPrint(Partition *p, u32 base_sector)
{
  u32 abs_sector;

  if(p->start_sector==0)
    {
      return;
    }
  if(base_sector == p->start_sector)
    {
      abs_sector=p->start_sector;
    }
  else
    {
      abs_sector = base_sector + p->start_sector;
    }
  

}
