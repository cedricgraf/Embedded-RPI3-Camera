

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

}
