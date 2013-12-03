#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "v4l/video.h"
#include "encoding/jpeg.h"
#include "encoding/rtp.h"
#include "udp/socket.h"

#include "../cv/resize.h"

#define DOWNSIZE_FACTOR   8


int main(int argc,char ** argv)
{
  printf("Starting video test program!\n");

  // Video Input
  struct vid_struct vid;
  vid.device = (char*)"/dev/video1";
  vid.w=1280;
  vid.h=720;
  vid.n_buffers = 4;
  if (video_init(&vid)<0) {
    printf("Error initialising video\n");
    return 0;
  }

  // Video Grabbing
  struct img_struct* img_new = video_create_image(&vid);

  // Video Resizing
  struct img_struct small;
  small.w = vid.w / DOWNSIZE_FACTOR;
  small.h = vid.h / DOWNSIZE_FACTOR;
  small.buf = (uint8_t*)malloc(small.w*small.h*2);

  // Video Compression
  uint8_t* jpegbuf = (uint8_t*)malloc(vid.h*vid.w*2);


  // Network Transmit
  struct UdpSocket* sock;
  //#define FMS_UNICAST 0
  //#define FMS_BROADCAST 1
  sock = udp_socket("192.168.1.255", 5000, 5001, FMS_BROADCAST);

  while (1) {

    // Aquire image
    printf("Aquiring an image ...\n");
    video_grab_image(&vid, img_new);


    // Resize: device by 4
    resize_uyuv(img_new, &small, DOWNSIZE_FACTOR);

    // JPEG encode the image:
    uint32_t quality_factor = 4; // quality factor from 1 (high quality) to 8 (low quality)
    uint32_t image_format = FOUR_TWO_TWO;  // format (in jpeg.h)
    uint8_t* end = encode_image (small.buf, jpegbuf, quality_factor, image_format, small.w, small.h);
    uint32_t size = end-(jpegbuf);

    send_rtp_frame(sock, (char*)jpegbuf,size, small.w, small.h);
//    size = create_svs_jpeg_header(jpegbuf,size,small.w);
//    udp_write(sock,(char*)jpegbuf,size);
    printf("Sending an image ...%u\n",size);

    //send_rtp_frame(sock, (char*) jpegbuf, size, small.w, small.h);
  }

  video_close(&vid);

  return 0;
}
