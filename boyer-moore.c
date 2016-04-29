#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

#define BUFSIZE 4096

int main() {
  ssize_t len;
  ssize_t x = 0;
  ssize_t i = 10;

  char input[BUFSIZE];
  int file = open("m.txt", O_RDONLY);

  do {
    len = read(file, input, BUFSIZE);
    i  %= BUFSIZE;

    while (len == BUFSIZE && i < BUFSIZE) {
      //printf("%d\n", i);
      switch (input[i]) {
        case 'm': i += 10; continue;
        case 'i': switch (input[i-1]) {
          case 'm': i +=  9; continue;
          case 'i': i += 11; continue;
          case 's': switch (input[i+1]) {
            case 'm': i += 11; continue;
            case 's': i +=  6; continue;
            default:  i += 12; continue;
          }
          case 'p': switch (input[i-2]) {
            case 'p': switch (input[i-3]) {
              case 'i': switch (input[i-4]) {
                case 's': switch (input[i-5]) {
                  case 's': switch (input[i-6]) {
                    case 'i': switch (input[i-7]) {
                      case 's': switch (input[i-8]) {
                        case 's': switch (input[i-9]) {
                          case 'i': switch (input[i-10]) {
                            case 'm': x++;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          default: i += 11; continue;
        }
        case 's': switch (input[i+4]) {
          case 'm': i += 14; continue;
          case 'i': i +=  4; continue;
          case 's': i += 11; continue;
          case 'p': i +=  5; continue;
          default:  i += 15; continue;
        }
        case 'p': switch (input[i+1]) {
          case 'm': i += 11; continue;
          case 'i': i +=  1; continue;
          case 'p': i +=  2; continue;
          default:  i += 12; continue;
        }
        default: i += 11; continue;
      }
    }
  } while (len > 0);

  printf("%d\n", x);
}
