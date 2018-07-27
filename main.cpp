#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

struct input_event {
      struct timeval time;
      unsigned short type;
      unsigned short code;
      unsigned int value; };

int main()
{
    int fd = open("/dev/input/by-path/pci-0000:02:00.0-usb-0:1:1.0-event-kbd", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cout << "Failed to open\n";
        return -1;
    }

    fcntl(fd, F_SETFL, 0);

    for (;;)
    {
        input_event event;
        auto const n = read(fd, &event, sizeof(event));
        if (n < 0) {
            std::cout << "Failed to read:" << n << "\n";
            return -1;
        }

        if (event.type == 1)
        {
            if (event.value == 1)
            {
                std::cout << event.code << " Key down\n";
            }
            else if (event.value == 0)
            {
                std::cout << event.code << " Key up\n";
            }
            else if (event.value == 2)
            {
                std::cout << event.code << " Key is down\n";
            }
        }
    }
}
