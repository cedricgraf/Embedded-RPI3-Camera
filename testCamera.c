<<<<<<< HEAD


#include<stdio.h>
#define VIDEO_DEV "/dev/video0"

/* Set brightness from 0 to 100 */
int bright_set (int fd, unsigned int newbright)
{
    struct video_picture vpic;

    if (ioctl (fd, VIDIOCGPICT, &vpic) < 0) {
        perror ("grab_bright_set");
        return -1;
    }

    vpic.brightness = newbright * 65536 / 100;
    return ioctl (fd, VIDIOCSPICT, &vpic);
}

int main(){

int fdv;
fdv = open (VIDEO_DEV, O_RDWR);
if (fdv <= 0) {
  perror (VIDEO_DEV);
  exit (1);
}

struct video_capability vcap;

if (ioctl (fdv, VIDIOCGCAP, &vcap) < 0) {
  perror ("VIDIOCGCAP");
  exit (1);
}

printf ("Video Capture Device Name : %s\n", vcap.name);

struct video_channel vc;

for (i = 0 ; i < vcap.channels ; i++){
  vc.channel = i;
  if(ioctl (fdv, VIDIOCGCHAN, &vc) < 0) {
    perror ("VIDIOCGCHAN");
    exit (1);
  }
  printf("Video Source (%d) Name : %s\n", i, vc.name);
}

struct video_mmap mm;
/* Set brightness */
bright_set (fdv, b);
b += 10;
/* Set frame size and format */
mm.frame = 0;
mm.height = height;
mm.width = width;
mm.format = VIDEO_PALETTE_RGB24;
/* Get frame */
if (ioctl(fdv, VIDIOCMCAPTURE, &mm) < 0) {
  perror ("VIDIOCMCAPTURE");
  exit (1);
}
/* Wait frame to be completed */
if (ioctl(fdv, VIDIOCSYNC, &mm.frame) < 0) {
  perror ("VIDIOCSYNC");
  exit (1);
}
/* Save to PPM file */
if (swap)
rgb_swap (framebuf, width * height);
sprintf (buf, "img_%02d.ppm", i);
write_ppm (buf, framebuf, width, height);


close (fdv);

=======
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <jpeglib.h>
#include <libv4l2.h>
#include <signal.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>


int main(void){
    int fd;
    if((fd = open("/dev/video0", O_RDWR)) < 0){
        perror("open");
        exit(1);
    }

    struct v4l2_capability cap;
    if(ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0){
        perror("VIDIOC_QUERYCAP");
        exit(1);
    }

    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
    fprintf(stderr, "The device does not handle single-planar video capture.\n");
    exit(1);
    }

    struct v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    format.fmt.pix.width = 800;
    format.fmt.pix.height = 600;

    if(ioctl(fd, VIDIOC_S_FMT, &format) < 0){
        perror("VIDIOC_S_FMT");
        exit(1);
    }

    struct v4l2_requestbuffers bufrequest;
    bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufrequest.memory = V4L2_MEMORY_MMAP;
    bufrequest.count = 1;

    if(ioctl(fd, VIDIOC_REQBUFS, &bufrequest) < 0){
      perror("VIDIOC_REQBUFS");
      exit(1);
    }

    struct v4l2_buffer bufferinfo;
    memset(&bufferinfo, 0, sizeof(bufferinfo));

    bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufferinfo.memory = V4L2_MEMORY_MMAP;
    bufferinfo.index = 0;

    if(ioctl(fd, VIDIOC_QUERYBUF, &bufferinfo) < 0){
        perror("VIDIOC_QUERYBUF");
        exit(1);
    }

    void* buffer_start = mmap(
    NULL,
    bufferinfo.length,
    PROT_READ | PROT_WRITE,
    MAP_SHARED,
    fd,
    bufferinfo.m.offset
    );

    if(buffer_start == MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    memset(buffer_start, 0, bufferinfo.length);



memset(&bufferinfo, 0, sizeof(bufferinfo));
bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
bufferinfo.memory = V4L2_MEMORY_MMAP;
bufferinfo.index = 0; /* Queueing buffer index 0. */

// Put the buffer in the incoming queue.
if(ioctl(fd, VIDIOC_QBUF, &bufferinfo) < 0){
    perror("VIDIOC_QBUF");
    exit(1);
}

// Activate streaming
int type = bufferinfo.type;
if(ioctl(fd, VIDIOC_STREAMON, &type) < 0){
    perror("VIDIOC_STREAMON");
    exit(1);
}

int k =0;
//clock_t temps;

while(k<2){
    // Dequeue the buffer.
    if(ioctl(fd, VIDIOC_DQBUF, &bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }

    bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufferinfo.memory = V4L2_MEMORY_MMAP;
    /* Set the index if using several buffers */

    // Queue the next one.
    if(ioctl(fd, VIDIOC_QBUF, &bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }
    i++;
}


int jpgfile;
if((jpgfile = open("myimage.jpeg", O_WRONLY | O_CREAT, 0660)) < 0){
    perror("open");
    exit(1);
}

write(jpgfile, buffer_start, bufferinfo.length);
close(jpgfile);


    printf("everything went okay\n");

    close(fd);
    return EXIT_SUCCESS;
>>>>>>> 4b551a7b22862dae4c7d81450b6b635385c67a86
}
