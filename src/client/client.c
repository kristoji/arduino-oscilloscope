#include "client.h"

ui_t options = 
{
    .channel_msk = 1,
    .frequency = 1,
    .mode = 0
};

int main(int argc, const char** argv) {

  if (argc<3) 
  {
    printf("client.elf <serial_file> <baudrate>\n");
    exit(EXIT_FAILURE);
  }

  const char* serial_device=argv[1];
  int baudrate=atoi(argv[2]);

  options.fd = serial_open(serial_device);
  serial_set_interface_attribs(options.fd, baudrate, 0);
  serial_set_blocking(options.fd, 1);

  uint8_t run = 1;
  do
  {
    run = ui_menu(&options);
  } while (run);

  return 0;






  // printf("in place\n");
  // while(1) {
  //   char buf[1024];
  //   memset(buf, 0, 1024);
  //   if (read_or_write) {
  //     int nchars=read(fd, buf,1024);
  //     printf("%s", buf);
  //   } else {
  //     // cin.getline(buf, 1024);
  //     fgets(buf, 1024, stdin);
  //     int l=strlen(buf);
  //     buf[l]='\n';
  //     ++l;
  //     write(fd, buf, l);
  //   }
  // }
}
